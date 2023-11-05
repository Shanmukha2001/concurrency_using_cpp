#include<iostream>
#include<thread>
#include<chrono>

using namespace std;

void printHello(){
    cout<<"hello"<<endl;
    // std::this_thread::sleep_for(chrono::milliseconds(100));
}

int main(){
    thread thread1(printHello);
    thread1.detach();

    cout<<"main here"<<endl;
    return 0;
}
// join(): Blocks the calling thread until the thread represented by the object has finished executing.
// detach(): Allows the thread to run independently. The calling thread will not wait for the detached thread to finish.