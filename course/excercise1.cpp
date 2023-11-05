#include<iostream>
#include<thread>

using namespace std;

void test(){
    cout<<"hello\n";
}

void funA(){
    thread threadC(test);
    threadC.join();
}

void funB(){
    cout<<"funB\n";
}

int main(){
    thread threadA(funA);
    threadA.join(); // first complete threadA exec then move to next line

    thread threadB(funB);
    threadB.join(); // complete threadb exec then move to next line
    
    cout<<"main thread executed after all the threads";
    return 0;
}