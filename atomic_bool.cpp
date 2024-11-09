#include<iostream>
#include<atomic>

using namespace std;

int main(){
    atomic<bool> x(false);
    cout<<"is lock free:" << (x.is_lock_free()?"yes":"no")<<endl;
    atomic<bool> y(true);
    x.store(false);
    x.store(y);

    cout<<"After store value x:"<<x.load()<<endl;
    cout<<"After store value y:"<<y.load()<<endl;
    bool prevVal = x.exchange(false);
    cout<< "exchanging x value with z and exchanging with false: x-> "<<x.load()<<" bool prevVal->"<<prevVal<<endl;
    return 0;
}