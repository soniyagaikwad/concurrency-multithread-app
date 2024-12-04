#include <iostream>
#include <thread>
#include "concurrency.h"  // Include the concurrency header for the renamed functions

// Function to simulate concurrent transactions: deposit and withdrawals
void run_concurrent_transactions() {
    // Print the initial balance before any transactions
    std::cout << "Initial Balance: " << concurrency_account_balance << std::endl;

    // Create threads for concurrent deposit and withdrawal operations
    // t1 will deposit $500 into the account
    std::thread t1(concurrency_deposit, 500);  

    // t2 will withdraw $300 from the account
    std::thread t2(concurrency_withdraw, 300); 

    // t3 will withdraw $800 from the account
    std::thread t3(concurrency_withdraw, 800); 

    // Wait for all threads to finish their execution before proceeding
    t1.join();  // Wait for t1 (deposit) to complete
    t2.join();  // Wait for t2 (withdraw $300) to complete
    t3.join();  // Wait for t3 (withdraw $800) to complete

    // Print the final balance after all transactions
    // The balance may be inconsistent due to potential race conditions
    std::cout << "Final Balance (may be inconsistent due to race conditions): " << concurrency_account_balance << std::endl;
}

int main() {
    // Call the function to simulate concurrent transactions
    run_concurrent_transactions();
    return 0;
}
