//
// Created by stefan on 4/9/22.
//

#ifndef DEBEER2D_RESOURCEMANAGER_H
#define DEBEER2D_RESOURCEMANAGER_H

#include <unordered_map>
#include <mutex>
#include <queue>
#include <functional>
#include <vector>
#include <thread>
#include <condition_variable>
#include <atomic>
#include <memory>

#include <Shader.h>

class ResourceManager
{
private:
    struct WorkerThread
    {
        WorkerThread() = default;
        WorkerThread(WorkerThread &&rOther) noexcept
            : worker{std::move(rOther.worker)}
            , isBusy{rOther.isBusy.load()}
        {}

        std::thread worker;
        std::atomic_bool isBusy = false;
    };

    std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders;
    std::mutex m_shaderMutex;

    std::mutex m_workQMutex;
    std::condition_variable m_isWorkAvailable;
    std::queue<std::function<void()>> m_workQueue;
    std::vector<WorkerThread> m_threadPool;
    std::atomic_bool m_terminate = false;

public:
    ResourceManager();
    virtual ~ResourceManager();
    void loadShader(const std::string& strShaderName);

    std::shared_ptr<Shader> getShader(const std::string &rStrPath);

    bool isBusy();

private:
    void workerFunction(std::atomic_bool &rIsBusy);
};


#endif//DEBEER2D_RESOURCEMANAGER_H
