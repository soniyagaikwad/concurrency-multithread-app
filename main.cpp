#include <iostream>
#include <thread>
//#include "concurrency.h"
#include "synchronization.h"          // Synchronized version with account balance management
#include "deadlock_management.h"      // Include the new deadlock management file
#include "producer_consumer.h"        // Include the producer-consumer header

#define USE_SYNC  // Define this to use the synchronized version

int main() {
    // Demonstrate race conditions without synchronization only if USE_SYNC is not defined
    #ifndef USE_SYNC
        std::cout << "Demonstrating race conditions without synchronization:" << std::endl;

        // Create multiple threads to simulate concurrent access
        std::thread t1(deposit, 300);  // Deposit $300
        std::thread t2(withdraw, 200);  // Withdraw $200
        std::thread t3(deposit, 400);  // Deposit $400
        std::thread t4(withdraw, 500);  // Withdraw $500

        // Join threads to wait for them to finish
        t1.join();
        t2.join();
        t3.join();
        t4.join();

        std::cout << "Final Balance (without synchronization): " << account_balance << std::endl;
    #endif

    // Use the synchronized version by including synchronization.h
    #ifdef USE_SYNC
        std::cout << "\nNow demonstrating synchronization with mutex:\n";
        std::thread t1_sync(attempt_deposit, 300);  // Use the deadlock-safe deposit
        std::thread t2_sync(attempt_withdraw, 200);  // Use the deadlock-safe withdraw
        std::thread t3_sync(attempt_deposit, 400);  // Use the deadlock-safe deposit
        std::thread t4_sync(attempt_withdraw, 500);  // Use the deadlock-safe withdraw

        // Join threads to wait for them to finish
        t1_sync.join();
        t2_sync.join();
        t3_sync.join();
        t4_sync.join();
        std::cout << "Final Balance (with synchronization and deadlock management): " << account_balance << std::endl;
    #endif

    // Producer-Consumer Demonstration
    std::cout << "\nDemonstrating producer-consumer model:\n";
    std::thread producer_thread(producer, 1000);  // Start producer thread
    std::thread consumer_thread(consumer, 500);    // Start consumer thread

    // Join producer-consumer threads
    producer_thread.join();
    consumer_thread.join();

    return 0;
}
