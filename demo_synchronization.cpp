#include <iostream>
#include <thread>
#include "synchronization.h"

// Function to demonstrate synchronized transactions
void run_synchronized_transactions() {
    // Output the initial balance before any deposit or withdrawal actions
    std::cout << "Initial Balance: " << account_balance << std::endl;

    // Start a thread to deposit $500 into the account
    std::thread t1(deposit, 500);  // Deposit $500
    // Start a thread to withdraw $300 from the account
    std::thread t2(withdraw, 300); // Withdraw $300
    // Start a thread to withdraw $800 from the account
    std::thread t3(withdraw, 800); // Withdraw $800

    // Wait for all threads to finish their operations before proceeding
    t1.join();  // Ensure the deposit thread completes
    t2.join();  // Ensure the first withdraw thread completes
    t3.join();  // Ensure the second withdraw thread completes

    // Output the final balance after all synchronized transactions have completed
    std::cout << "Final Balance (consistent due to synchronization): " << account_balance << std::endl;
}

int main() {
    // Call the demo function to execute synchronized transactions
    run_synchronized_transactions();
    return 0;
}

