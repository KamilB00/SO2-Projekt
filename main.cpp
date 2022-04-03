#include <unistd.h>
#include <pthread.h>
#include <cstdlib>
#include <iostream>

int random(int min, int max) {
    static bool first = true;
    if (first) {
        srand(time(nullptr));
        first = false;
    }
    return min + rand() % ((max + 1) - min);
}

int fibonacci(int n) {
    if (n <= 1)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int counting(int n) {
    int result = fibonacci(n);
    return result;
}

void *threadFunction(void *arg) {
    int index = *((int *) arg);
    int randElement = random(4, 20);
    int sleepTime = random(1, 10);
    printf("Thread %d: Created\n", index);
    printf("Thread %d: Result of calculating %d-th element of Fibonacci sequence is: %d\n", index, randElement,
           counting(randElement));
    printf("Thread %d: Sleep for:  %d s\n", index, sleepTime);
    sleep(sleepTime);
    printf("Thread %d: Ending\n", index);
    return nullptr;
}

void createThreads(int numberOfThreads) {
    pthread_t newThread[numberOfThreads];
    int threadArguments[numberOfThreads];
    for (int i = 1; i <= numberOfThreads; ++i) {
        threadArguments[i] = i;
        pthread_create(&newThread[i], nullptr, threadFunction, &threadArguments[i]);
    }
    for (int i = 1; i <= numberOfThreads; ++i) {
        pthread_join(newThread[i], nullptr);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Wrong number of given arguments!\n");
        exit(1);
    }
    int numberOfThreads;
    numberOfThreads = atoi(argv[1]);
    createThreads(numberOfThreads);
    return 0;
}


