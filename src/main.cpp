#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "Thread.h"

void exampleTask(int n) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Task " << n << " is completed" << std::endl;
}

int main() {
    // 创建一个具有4个工作线程的线程池
    ThreadPool pool(4);

    // 存储 future 对象的向量
    std::vector<std::future<void>> results;

    // 向线程池中添加8个任务
    for (int i = 0; i < 8; ++i) {
        results.emplace_back(
            pool.enqueue(exampleTask, i)
        );
    }

    // 等待所有任务完成
    for (auto && result: results) {
        result.get();
    }

    return 0;
}

