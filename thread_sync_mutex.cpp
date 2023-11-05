#include<thread>
#include<iostream>
#include<mutex>

using namespace std;

mutex mtx;
int count =0;

void incrementCounter(){
    for (int i = 0; i < 5; i++)
    {
        mtx.lock();
        count++;
        cout<<this_thread::get_id()<<" printed "<<count<<endl;
        mtx.unlock();
    }
        
}


int main(){
    thread thread1(incrementCounter);
    thread thread2(incrementCounter);
    thread1.join();
    thread2.join();
    return 0;
}