#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <thread>
#include <chrono>
#include <condition_variable>

using namespace std;

int destinatino_dist =5;
int distance_covered = 0;
condition_variable cv;
mutex m;

void keep_driving(){
    while (distance_covered!= destinatino_dist){
        this_thread::sleep_for(chrono::seconds(1));
        distance_covered+=1;
        cout<<"still driving\n";
    }
    cv.notify_one();
}

void wake_up_passenger(){
    std::unique_lock<std::mutex> ul(m);
	cv.wait(ul, [] {return distance_covered == destinatino_dist; });
    cout<<"driver wakes the passenger thread "<<destinatino_dist<<" km\n";
}

int main(){
    thread driver_thread(keep_driving);
    thread passenger_thread(wake_up_passenger);
    driver_thread.join();
    passenger_thread.join();
}