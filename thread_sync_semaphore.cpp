// Unlike a mutex, semaphores allow multiple threads to access
// a resource concurrently (useful for resources that can support multiple threads).
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class Semaphore {
public:
    Semaphore(int count = 0) : count(count) {}

    void signal() {
        std::unique_lock<std::mutex> lock(mtx);
        ++count;
        cv.notify_one(); // notify the one thread which is waiting if any
    }

    void wait() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return count > 0; }); // wait the thread until count is not greater than 0
        --count;
    }

private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;
};

Semaphore sem(2);  // Initial count is 1, for a binary semaphore

void printWithSemaphore(int id) {
    sem.wait();  // Wait until semaphore is available
    std::cout << "Thread " << id << " is printing.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    sem.signal();  // Release semaphore
}

int main() {
    std::thread t1(printWithSemaphore, 1);
    std::thread t2(printWithSemaphore, 2);
    std::thread t3(printWithSemaphore, 3);
    std::thread t4(printWithSemaphore, 4);
    std::thread t5(printWithSemaphore, 5);
    std::thread t6(printWithSemaphore, 6);
    std::thread t7(printWithSemaphore, 7);
    std::thread t8(printWithSemaphore, 8);
    std::thread t9(printWithSemaphore, 9);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    t9.join();
    std::cout << "All threads have finished printing.\n";
    return 0;
}
