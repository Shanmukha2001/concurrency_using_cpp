#include<iostream>
#include <thread>         
#include <future>         
#include <stdexcept>
#include<bits/stdc++.h>

using namespace std;

void throw_exception(){
    throw invalid_argument("input cannot be negative");
}

void calculate_val(promise<int>& prom){
    try{
        int x;
        cout<<"Enter x:";
        cin >>x;
        if (x <0)
            throw_exception();
        prom.set_value(sqrt(x));
    }catch(exception&){
		prom.set_exception(std::current_exception());
    }
}

void print_val(future<int> &fut){
    try{
        int x = fut.get();
        cout<<"val:"<<x<<endl;
    }catch(exception& e){
        std::cout << "[exception caught: " << e.what() << "]\n";
    }
}

int main(){
    promise<int> prom;
    future<int> future = prom.get_future();
    thread print_thread(print_val,ref(future));
    thread calculate_thread(calculate_val,ref(prom));
    print_thread.join();
    calculate_thread.join();
    return 0;
}