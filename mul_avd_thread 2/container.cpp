#include "container.h"
#include <string>
#include <iostream>
#include <utility>

/// Семафоры-вилки, всего пять штук.
sem_t dinner_forks[5];
/// Массив состояний философов.
std::string philosophers_state[5] = {"think ", "think ", "think ", "think ", "think "};
/// Массив потоков-философов.
pthread_t philosophers[5];
/// Мьютекс для блокировки частей кода.
std::mutex mtx;

/// Метод, выводящий в консоль информацию о текущих состояниях философов.
void PrintState(std::string state, int index) {
    philosophers_state[index] = std::move(state);
    // блокируем вывод информации от
    // вмешивания со стороны других потоков.
    mtx.lock();
    printf("\n");
    for (auto & i : philosophers_state) {
        std::cout << ("   ");
        std::cout << i;
    }
    // снимаем блокировку.
    mtx.unlock();
}

/// Метод печатает имена философов как заголовки.
void PrintPhilosophers() {
    std::cout << "\n";
    std::cout << " | Kant " << "| Plato "
    << "| Socrates " << "| Locke " << "| Voltaire | ";
}

/// Выносим отдельно состояние приема пищи философом.
void EatingState(int index) {
    // филосов берет вилки, либо ждет, пока они освободятся.
    sem_wait(&dinner_forks[index]);
    sem_wait(&dinner_forks[(index + 1) % 5]);
    // флосов ест.
    PrintState("EATING", index);
    sleep(1);
    // филосов отпускает вилки после еды.
    sem_post(&dinner_forks[(index + 1) % 5]);
    sem_post(&dinner_forks[index]);
}

/// Метод, отвечающий за состояния философов за столом.
void* ChangeState(void *arg) {
    auto index = (int64_t) arg;
    // филосов голоден.
    PrintState("hungry", index);
    // философ идет есть.
    EatingState(index);
    // философ думает.
    PrintState("think ", index);
    pthread_exit(nullptr);
}
/// Инициализируем семафоры.
void Initialize(container_st *container) {
    for (int i = 0; i < 5; i++) {
        sem_init(&dinner_forks[i], 0, 1);
    }
    // выводим заголовки.
    PrintPhilosophers();
}
/// Метод создает потоки и ждет их завершения.
void Dinner(container_st *container) {
    for (int i = 0; i < 5; i++) {
        pthread_create(&philosophers[i], nullptr, ChangeState, (void *) i);
    }

    for (auto & philosopher : philosophers) {
        pthread_join(philosopher, nullptr);
    }
    PrintPhilosophers();
}

