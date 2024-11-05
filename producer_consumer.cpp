#include "producer_consumer.h"
#include "synchronization.h"  // Reuse existing deposit and withdraw functions

std::mutex account_mutex;
std::condition_variable cv;

// Producer thread that deposits funds into the account
void producer(int amount) {
    deposit(amount);  // Reuse existing deposit function from synchronization.cpp
    cv.notify_one();  // Notify consumer after deposit
}

// Consumer thread that withdraws funds from the account
void consumer(int amount) {
    std::unique_lock<std::mutex> lock(account_mutex);
    cv.wait(lock, [](){ return account_balance > 0; });  // Wait if no funds available
    withdraw(amount);  // Reuse existing withdraw function from synchronization.cpp
}
