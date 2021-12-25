#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <mutex>
#include <iostream>
#include "container.h"

/// Ошибка при неправильном количестве аргументов.
void ArgNumError() {
    std::cout << "Для запуска программы не требуются какие-либо дополнительные аргументы";
}

/// Вход в программу.
int main(int argc, char *argv[]) {
    if (argc != 1) {
        std::cout << argc;
        ArgNumError();
        exit(EXIT_FAILURE);
    }

    container_st* container;
    Initialize(container);

    Dinner(container);
}

