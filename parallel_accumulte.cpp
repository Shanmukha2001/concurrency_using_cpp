#include<iostream>
#include<future>
#include<numeric>
#include<vector>

using namespace std;

int MIN_ELEMENT_COUNT = 1000;

template<typename iterator>
int parallel_accumulate(iterator begin,iterator end){
    int length = distance(begin,end);
    if(length <= MIN_ELEMENT_COUNT) return accumulate(begin,end,0);
    iterator mid = begin;
	advance(mid, (length + 1) / 2);
    future<int> f1 = async(launch::deferred | launch::async,parallel_accumulate<iterator>,mid,end);
    return accumulate(begin,mid,0)+f1.get();
}

int main(){
    std::vector<int> v(10000, 1);
	std::cout << "The sum is " << parallel_accumulate(v.begin(), v.end()) << '\n';
}