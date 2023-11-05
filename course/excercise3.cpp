#include<iostream>
#include<thread>
#include<queue>
#include<chrono>

using namespace std;

queue<int> engineq;
queue<int> cleanerq;

void clean(){
    while (true)
    {
        if (!cleanerq.empty())
        {
            cleanerq.pop();
            cout<<"cleaning the ship\n";
            cout<<"cleaned\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));

        }else{
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
    
}

void engine(){
    while (true)
    {
        if (!engineq.empty())
        {
            int command = engineq.front();
            engineq.pop();
            switch (command)
            {
            case 2:
                cout<<"engine full speeding\n";
                cout<<"engine has set to full speed\n";
                break;
            case 3:
                cout<<"stopping engine\n";
                cout<<"stopped engine\n";
                break;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));

        }else{
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
}

int main(){
    thread cleaner(clean);
    thread engineThread(engine);
    cleaner.detach();
    engineThread.detach();
    int input;
    cout << "Enter command (1: clean, 2: full speed, 3: stop engine, 100: exit): ";
    while (true)
    {
        cin >> input;
        std::this_thread::sleep_for(std::chrono::seconds(1));

        if (input == 100) { // Command for stopping the program
            cout << "Stopping program..." << endl;
            break;
        }
        else if (input == 1) { // Cleaning command
            cleanerq.push(input);
        } else if (input == 2 || input == 3) { // Engine commands
            engineq.push(input);
        }else{
            cout<<"Invalid command\n";
        }
    }
    
    return 0;
}