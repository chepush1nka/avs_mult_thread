#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <mutex>

#ifndef MUL_AVD_THREAD_CONTAINER_H
#define MUL_AVD_THREAD_CONTAINER_H

typedef struct {
    pthread_t philosophers[5];
} container_st;


void Initialize(container_st *container);

void Dinner(container_st *container);

void PrintPhilosophers();

void EatingState(int index);

void* ChangeState(void *arg);

void PrintState(std::string state, int index);

#endif //MUL_AVD_THREAD_CONTAINER_H
