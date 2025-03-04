#include "workpool.h"

ThreadPool::ThreadPool(size_t num_threads) : stop(false)
{
    for (size_t i = 0; i < num_threads; ++i)
    {
        workers.emplace_back([this]
                             {
                while (true) {
                    std::function<void()> task;
                    
                    {
                        std::unique_lock<std::mutex> lock(queue_mutex);
                        condition.wait(lock, [this] {
                            return stop || !tasks.empty();
                        });
                        
                        if (stop && tasks.empty()) return;
                        
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    
                    task();
                } });
    }
}

ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();

    for (auto &worker : workers)
    {
        worker.join();
    }
}

// WaitCroup
void WaitGroup::Add(int delta)
{
    std::unique_lock<std::mutex> lock(mutex);
    count += delta;
}

void WaitGroup::Done()
{
    std::unique_lock<std::mutex> lock(mutex);
    --count;
    if (count == 0)
    {
        cv.notify_all();
    }
}

void WaitGroup::Wait()
{
    std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock, [this]
            { return count == 0; });
}
