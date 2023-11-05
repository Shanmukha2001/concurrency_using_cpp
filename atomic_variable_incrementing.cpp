#include<bits/stdc++.h>

using namespace std;

atomic<int> i = 0;
// thread_local atomic<int> i = 0; // each thread will have this i variable in its stack

void foo(){
    ++i;
    cout<<i;
}

int main(){
    thread t1(foo);
    thread t2(foo);
    thread t3(foo);
    t1.join();
    t2.join();
    t3.join();
    cout<<"\n";
    return 0;
}