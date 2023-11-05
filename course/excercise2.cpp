#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void clean() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << "clean\n";
}

void fullSpeed() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << "full speeding\n";
}

void stopEngine() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << "stop\n";
}

int main() {
    int command;
        cout << "Enter command:\n1. cleaning\n2. full speed ahead\n3. stop\n4. 100: exit\n";
    do {
        cin >> command;
        
        switch (command) {
            case 1: {
                thread cleaner(clean);
                cleaner.detach();  // Run independently in the background
                break;
            }
            case 2: {
                thread fullSpeedAhead(fullSpeed);
                fullSpeedAhead.join();  // Wait for fullSpeed to complete
                break;
            }
            case 3: {
                thread stop(stopEngine);
                stop.join();  // Wait for stopEngine to complete
                break;
            }
            case 100:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid command!\n";
                break;
        }
    } while (command != 100);

    return 0;
}
