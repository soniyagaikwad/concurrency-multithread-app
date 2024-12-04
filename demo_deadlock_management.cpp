#include <iostream>
#include <thread>
#include "deadlock_management.h"
#include "synchronization.h"

int main() {
    // Start the thread for deadlock detection. This runs the check_for_deadlock function
    // in the background to detect any potential deadlocks in the system.
    std::thread t1(check_for_deadlock); // Run deadlock detection in the background

    // Start threads for deposit and withdraw operations (simulating concurrency)
    // t2 will perform a deposit operation of $500
    std::thread t2(attempt_deposit, 500);  // Thread for deposit

    // t3 will perform a withdrawal operation of $300
    std::thread t3(attempt_withdraw, 300); // Thread for withdrawal

    // Wait for both deposit and withdrawal threads to finish their execution
    t2.join();  // Wait for deposit thread to finish
    t3.join();  // Wait for withdrawal thread to finish

    // Detach the deadlock detection thread so it can continue running indefinitely
    // without blocking the main thread. This allows the system to check for deadlocks
    // in the background while the main program completes.
    t1.detach();  // Deadlock detection thread runs in the background

    // Output the final account balance after all operations
    std::cout << "Final Balance: " << account_balance << std::endl;
    return 0;
}
