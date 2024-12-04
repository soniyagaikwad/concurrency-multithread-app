#include "producer_consumer.h"
#include "synchronization.h"  // Reuse existing deposit and withdraw functions

// Mutex to synchronize access to the account balance
std::mutex account_mutex;  

// Condition variable to coordinate the producer and consumer threads
std::condition_variable cv;  

// Producer thread function that deposits funds into the account
// It calls the existing deposit function and notifies the consumer thread afterward.
void producer(int amount) {
    deposit(amount);  // Reuse existing deposit function from synchronization.cpp
    cv.notify_one();  // Notify the consumer that funds are available
}

// Consumer thread function that withdraws funds from the account
// It waits until the account has a positive balance before withdrawing funds.
void consumer(int amount) {
    std::unique_lock<std::mutex> lock(account_mutex);  // Lock the mutex for thread synchronization
    cv.wait(lock, [](){ return account_balance > 0; });  // Wait for funds to be available
    withdraw(amount);  // Reuse existing withdraw function from synchronization.cpp
}
