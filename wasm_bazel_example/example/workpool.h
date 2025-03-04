#pragma once

#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

class ThreadPool {
public:
    ThreadPool(size_t num_threads);

    template <typename F>
    void enqueue(F&& f) {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        if (stop)
        {
            throw std::runtime_error("enqueue on stopped ThreadPool");
        }
        tasks.emplace(std::forward<F>(f));
    }
    condition.notify_one();
   }

    ~ThreadPool();

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

class WaitGroup {
public:
    WaitGroup() : count(0) {}

    void Add(int delta = 1);

    void Done();

    void Wait();

private:
    std::mutex mutex;
    std::condition_variable cv;
    int count;
};

