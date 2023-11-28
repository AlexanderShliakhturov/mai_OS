#include <vector>
#include <iostream>
#include <utility>
#include <math.h>
#include <string>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>

void print(int i)
{
    std::cout << "PRINT CREATED THREAD ID " << std::this_thread::get_id() << " AND I IS " << i << std::endl;
    //std::cout << i << std::endl;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    std::cout << "MAIN PRICESS ID " << std::this_thread::get_id() << std::endl;

    int k = 0;
    
    while (k < 2)
    {
        std::vector<std::thread> threads;
        for (int i = 0; i < 2; i++)
        {
            threads.emplace_back(std::thread(print, i));
        }

        
        for (auto &thread : threads)
        {
            std::cout << " CLOSE THREAD ID " << thread.get_id() << std::endl;
            thread.join();
        }
        k++;
    }

    std::cout << "MAIN PROCESS ID " << std::this_thread::get_id() << std::endl;


    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
}
