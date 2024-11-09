#include<iostream>
#include<atomic>

using namespace std;

int main(){
    int values[20];
    for(int i=0;i<20;i++){
        values[i] = i+1;
        cout<<values[i]<<" ";
    }
    cout<<endl;
    atomic<int*> x_pointer;
    x_pointer = values;
    cout<<"current val of x:"<<*(x_pointer.load())<<endl;
    int* y_pointer = values + 3;
    cout<<"y points to x_pointer+3:"<<*y_pointer<<endl;
    cout<<"compare exchange successful: "<<(x_pointer.compare_exchange_weak(y_pointer,values+10)?"Yes":"No")<<endl;
    x_pointer.exchange(y_pointer);
    cout<<"compare exchange successful: "<<(x_pointer.compare_exchange_weak(y_pointer,values+10)?"Yes":"No")<<endl;
    cout<<"x_pointer.compare_exchange_weak(y_pointer,values+10) -> "<<*(x_pointer.load())<<endl;
    return 0;
}