#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void printNumbers(int start, int end) {
    for (int i = start; i < end; i++) {
        cout << " Number " << i << "\n"; // this output can 
        std::this_thread::sleep_for(chrono::milliseconds(100)); // Corrected sleep function
    }
}

int main() {
    thread thread1(printNumbers, 1, 5);  // Create first thread
    thread thread2(printNumbers, 5, 10); // Create second thread
    thread1.join(); // Wait for thread1 to finish
    thread2.join(); // Wait for thread2 to finish
    return 0;
}
