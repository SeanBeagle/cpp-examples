#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <array>

std::mutex mtx;

/** Callable function */
void callableFunction(int i) {
    mtx.lock();
    std::cout << i << ": Running callableFunction: threadID= " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    mtx.unlock();
}

/** Callable class */
class CallableClass {
  private:
    static int _index;
  public:
    void operator()(int i) {
        mtx.lock();
        std::cout << i << ": Running callableClass: threadID=" << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        mtx.unlock();
    }
};

/** Callable lambda */
auto callableLambda = [](int i) {
    mtx.lock();
    std::cout << i << ": Running callableLambda : threadID= " << std::this_thread::get_id() << std::endl;
    mtx.unlock(); 
};

int main()
{
    std::cout << "Begin main()" << std::endl;
    std::array<std::thread, 10> thread_pool;
    
    // 
    for (size_t i = 0; i < thread_pool.size(); i++) {
        if (i % 2 == 0 || i == 0) {
            thread_pool[i] = std::thread(callableFunction, i);
        } else {
            thread_pool[i] = std::thread(CallableClass(), i);
        }
    }

    // block current thread until threads in thread_pool finish execution 
    for (std::thread &t : thread_pool) {
        t.join();    
    }



    std::cout << "End main()" << std::endl;
   
    return 0;
}
