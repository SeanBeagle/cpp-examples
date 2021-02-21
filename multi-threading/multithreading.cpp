#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <array>

std::mutex mtx;

/** Callable function */
void callableFunction(int id) {
    mtx.lock();
    std::cout << "Running callableFunction " << id << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    mtx.unlock();
}

/** Callable class */
class CallableClass {
  private:
    static int _index;
  public:
    void operator()(int id) {
        mtx.lock();
        std::cout << "Running callableClass " << id << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        mtx.unlock();
    }
};

/** Callable lambda */
auto callableLambda = [](int id) {
    mtx.lock();
    std::cout << "Running callableLambda " << id << std::endl;
    mtx.unlock(); 
};

int main()
{
    std::cout << "Begin main()" << std::endl;
    std::array<std::thread, 10> thread_pool;
    
    for (size_t i = 0; i < thread_pool.size(); i++) {
        if (i % 2 == 0 || i == 0) {
            thread_pool[i] = std::thread(callableFunction, i);
        } else {
            thread_pool[i] = std::thread(CallableClass(), i);
        }
    }
 
    for (std::thread &t : thread_pool) {
        t.join();    
    }


    // std::thread t1(callableFunction, 3);
    // std::thread t2(CallableClass(), 4);
    // std::thread t3(callableLambda, 5);

    // t1.join();
    // t2.join();
    // t3.join();

    std::cout << "End main()" << std::endl;
   
    return 0;
}
