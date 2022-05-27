#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>


class ThreadPool
{
public:
    using Task = std::function<void()>;

    explicit ThreadPool(size_t poolSize);

     // pass arguments by value
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>{
        auto problem = std::make_shared<std::packaged_task<decltype(func(args...))()>> (std::bind(func, args...));
        auto ff = [problem](){ (*problem)();};
        std::unique_lock<std::mutex> lock(mutex_var);
        queue_.emplace(ff);
        working.notify_one();
        return problem->get_future();
    }

    ~ThreadPool();

private:
    size_t poolSize;
    std::condition_variable working;
    std::queue<Task> queue_;
    std::vector<std::thread> threads;
    std::mutex mutex_var;
    std::atomic<bool> alive;
};