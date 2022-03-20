#include <unistd.h>
#include <pthread.h>
#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

int random(int min, int max) {
    static bool first = true;
    if (first) {
        srand(time(nullptr));
        first = false;
    }
    return min + rand() % ((max + 1) - min);
}

void randomSleepTime() {
    int sleepTime = random(1, 10);
    cout << "Sleeping for: " << sleepTime << " s" << endl;
    sleep(sleepTime);
}

int fibonacci(int n) {
   if (n <=1)
       return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

void counting() {
    cout << "Calculating..." << endl;
    int randElement = random(4,20);
    int result =  fibonacci(randElement);
    cout<<"Fibonacci sequence "<<randElement<<"-th element is: "<<result<<endl;
}

void *threadFunction(void *arg) {
    cout << "Thread created" << endl;
    counting();
    randomSleepTime();
    cout << "Ending thread" << endl;
    cout << endl;
    return nullptr;
}

void createThreads(int n) {
    for (int i = 0; i < n; ++i) {
        pthread_t newThread;
        cout << "Creating Thread " << i + 1 << endl;
        pthread_create(&newThread, nullptr, threadFunction, nullptr);
        pthread_join(newThread, nullptr);
    }
}

int numberOfThreads() {
    int number_of_threads;
    cout << "How many threads would you like to create: ";
    cin >> number_of_threads;
    return number_of_threads;
}

int main() {
    createThreads(numberOfThreads());
    return 0;
}


