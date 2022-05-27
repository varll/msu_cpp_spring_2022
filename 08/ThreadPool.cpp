#include "ThreadPool.hpp"


ThreadPool::ThreadPool(size_t poolSize) : poolSize(poolSize), alive(true){
    for(size_t i = 0; i < poolSize; ++i){
        threads.emplace_back([this](){
            while (true){
                std::unique_lock<std::mutex> lock(mutex_var);
                if (!queue_.empty()){
                    auto problem = std::move(queue_.front());
                    queue_.pop();
                    lock.unlock();
                    problem();
                }
                else{
                    if (alive)
                        working.wait(lock);
                    else
                        return;
                }
            }
            
        }
        );
    }
}

ThreadPool::~ThreadPool(){
    alive = false;
    working.notify_all();
    for(size_t i = 0; i < poolSize; i++){
        threads[i].join();
    }
}