//
// Created by stefan on 4/9/22.
//

#include "ResourceManager.h"
#include <Logger.h>
#include <optional>

ResourceManager::ResourceManager()
{
    auto workerFunc = [&](std::atomic_bool &rIsBusy) {this->workerFunction(rIsBusy);};

    for (int i = 0; i < std::thread::hardware_concurrency(); i++)
    {
        auto worker = std::make_unique<WorkerThread>();
        worker->worker = std::thread(workerFunc, std::ref(worker->isBusy));

        LOG_INFO("Added a worker thread: {}", worker->worker.get_id());
        m_threadPool.emplace_back(std::move(worker));
    }
}

ResourceManager::~ResourceManager()
{
    m_terminate = true;
    m_isWorkAvailable.notify_all();
    for (auto &pWorker : m_threadPool)
    {
        pWorker->worker.join();
    }
}

void ResourceManager::workerFunction(std::atomic_bool &rIsBusy)
{
    while (!m_terminate)
    {
        rIsBusy = false;
        std::function<void()> work;
        {
            // Put the thread to sleep until there is work to do
            std::unique_lock<std::mutex> lock(m_workQMutex);
            m_isWorkAvailable.wait(lock, [&]() {
                return !m_workQueue.empty() || m_terminate;
            });
            rIsBusy = true;
            if (!m_terminate)
            {
                work = m_workQueue.front();
                m_workQueue.pop();
            }
        }
        if (!m_terminate)
        {
            work();
        }
    }
}

void ResourceManager::loadShader(const std::string& strShaderName)
{
    // Note we are not doing pShader compilation is a worker thread as this is only possible in the main thread (OpenGL context is thread bound)

    std::shared_ptr<Shader> pShader = std::make_shared<Shader>();
    if (pShader->load(strShaderName + ".vert", strShaderName + ".frag"))
    {
        m_shaders[strShaderName] = pShader;
    }
}

bool ResourceManager::isBusy()
{
    bool isActive = false;
    for (auto &pThread : m_threadPool)
    {
        if (pThread->isBusy)
        {
            isActive = true;
            break;
        }
    }

    return !m_workQueue.empty() || isActive;
}

std::shared_ptr<Shader> ResourceManager::getShader(const std::string &rStrPath) const
{
    auto shaderIt = m_shaders.find(rStrPath);
    return (shaderIt != m_shaders.end()) ? shaderIt->second : nullptr;
}

void ResourceManager::loadTexture(std::string_view strTexturePath)
{
    std::string strTexturePathCopy{strTexturePath};
        auto workFunc = [=]() {
            auto pTexture = std::make_shared<Texture>();
            LOG_INFO("Loading texture {}", strTexturePathCopy);
            if (pTexture->load(strTexturePathCopy))
            {
                LOG_INFO("Loaded texture: {}", strTexturePathCopy);
                std::unique_lock<std::mutex> lock(m_texturesMutex);
                this->m_textures[strTexturePathCopy] = pTexture;
            }
        };

        // Queue the work
        m_workQueue.push(workFunc);

        // Notify to the thread pool that there is work available
        m_isWorkAvailable.notify_one();
}

std::shared_ptr<Texture> ResourceManager::getTexture(const std::string &rStrPath) const
{
    auto textureIt = m_textures.find(rStrPath);
    return (textureIt != m_textures.end()) ? textureIt->second : nullptr;
}

void ResourceManager::initTextures()
{
    for (const auto& texture : m_textures)
    {
        texture.second->init();
    }
}
