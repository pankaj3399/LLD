#include <bits/stdc++.h>
#include <thread>
#include <mutex>
using namespace std;

class Logger
{
    static int counter;
    static Logger *instance;
    static mutex mtx;
    Logger()
    {
        counter++;
        cout << "Instances: " << counter << endl;
    }
    Logger(const Logger &);           // make copy constructor private as well
    Logger operator=(const Logger &); // make = operator overloading private as well

public:
    static Logger *getInstance()
    {
        // double checked locking
        if (instance == nullptr)
        {
            mtx.lock();
            if (instance == nullptr)
            {
                instance = new Logger();
            }
            mtx.unlock();
        }

        return instance;
    }
    void log(string msg)
    {
        cout << msg << endl;
    }
};

int Logger::counter = 0;
Logger *Logger::instance = nullptr;
mutex Logger::mtx;

void user1Logs()
{
    Logger *log1 = Logger::getInstance();
    log1->log("Hi");
}

void user2Logs()
{
    Logger *log2 = Logger::getInstance();
    log2->log("Bye");
}

int main()
{

    // Logger *log1 = Logger::getInstance();
    // Logger *log2 = Logger::getInstance();
    // log1->log("Hi");
    // log1->log("Bye");
    thread t1(user1Logs);
    thread t2(user2Logs);

    t1.join();
    t2.join();

    return 0;
}