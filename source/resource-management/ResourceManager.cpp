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
        WorkerThread worker;
        worker.worker = std::thread(workerFunc, std::ref(worker.isBusy));

        LOG_INFO("Added a worker thread: {}", worker.worker.get_id());
        m_threadPool.emplace_back(std::move(worker));
    }
}

ResourceManager::~ResourceManager()
{
    m_terminate = true;
    m_isWorkAvailable.notify_all();
    for (WorkerThread &rWorker : m_threadPool)
    {
        rWorker.worker.join();
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

//void ResourceManager::loadShader(const std::string& strShaderName)
//{
//    auto workFunc = [=]() {
//        Shader shader{};
//        LOG_INFO("Loading shader {}", strShaderName);
//        if (shader.load(strShaderName + ".vert", strShaderName + ".frag"))
//        {
//            LOG_INFO("Loaded shader: {}", strShaderName);
//            std::unique_lock<std::mutex> lock(m_shaderMutex);
//            this->m_shaders[strShaderName] = shader;
//        }
//    };
//
//    // Queue the work
//    m_workQueue.push(workFunc);
//
//    // Notify to the thread pool that there is work available
//    m_isWorkAvailable.notify_one();
//}

bool ResourceManager::isBusy()
{
    bool threadIsActive = false;
    for (WorkerThread &rThread : m_threadPool)
    {
        if (rThread.isBusy)
        {
            threadIsActive = true;
            break;
        }
    }

    return !m_workQueue.empty() && !threadIsActive;
}

std::shared_ptr<Shader> ResourceManager::getShader(const std::string &rStrPath)
{
    auto shaderIt = m_shaders.find(rStrPath);
    return (shaderIt != m_shaders.end()) ? shaderIt->second : nullptr;
}
