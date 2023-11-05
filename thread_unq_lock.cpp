#include<iostream>
#include<thread>
#include<mutex>
#include<vector>

using namespace std;
mutex mtx;
int sharedCounter;

// locks are used to avoid broken invairants(invariant: some condition or logic which has to be always true no matter what, ex doubly ll node.next = nexnode.prev)
// Use std::lock_guard for simpler, scope-based locking where the lock should not be released before the end of scope.
// Use std::unique_lock when more flexibility is needed, such as unlocking and relocking within the same scope or attempting conditional locking.

void incrementCounter(int threadId){
    for(int i=0;i<100;i++){
        unique_lock<mutex> lock(mtx);
        sharedCounter++;
        cout<<"thread "<<threadId<<" prints: "<<sharedCounter<<endl;
    }
    cout<<"thread "<<threadId<<" completed exe"<<endl;
}

int main(){
    int numThreads = 10;
    vector<thread> threads;
    for(int i=0;i<numThreads;i++){
        threads.emplace_back(incrementCounter, i + 1);
    }
    for(auto &thread:threads){
        thread.join();
    }
    return 0;
}