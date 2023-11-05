#include<iostream>
#include<thread>

int main(){
    int numberOfLogicalCpus = std::thread::hardware_concurrency();
    std::cout<<"we have "<<numberOfLogicalCpus<<"  logical cores\n";
}