#include<iostream>
#include<future>

using namespace std;

int find_future_answer(){
    return 1000;
}

void do_calculation(){
    cout<<"performing complex calculation\n";
}

int main(){
    future<int> future_answer = async(find_future_answer);
    do_calculation();
    cout<<future_answer.get();
}