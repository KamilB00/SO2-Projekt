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

int counting() {
    cout << "Calculating..." << endl;
    int a = 2;
    return a + a * a;
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
        cout << "Creating Thread " << i+1 << endl;

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


