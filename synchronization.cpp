#include <iostream>
#include <mutex>
#include "synchronization.h"

// Initialize the account balance to $1000
int account_balance = 1000;  

// Mutex for ensuring thread safety when accessing or modifying the account balance
std::mutex mtx;             

// Deposit function: Adds the specified amount to the account balance
void deposit(int amount) {
    std::lock_guard<std::mutex> lock(mtx);  // Lock the mutex to ensure thread safety
    account_balance += amount;  // Increase the account balance by the deposit amount
    std::cout << "Deposited: " << amount 
              << ", New Balance: " << account_balance << std::endl; // Output the deposit details
}

// Withdraw function: Subtracts the specified amount from the account balance
void withdraw(int amount) {
    std::lock_guard<std::mutex> lock(mtx);  // Lock the mutex to ensure thread safety
    if (account_balance >= amount) {  // Check if there is sufficient balance for the withdrawal
        account_balance -= amount;  // Decrease the account balance by the withdrawal amount
        std::cout << "Withdrew: " << amount 
                  << ", New Balance: " << account_balance << std::endl;  // Output the withdrawal details
    } else {
        std::cout << "Withdrawal of " << amount 
                  << " failed. Insufficient balance." << std::endl;  // Output error message if balance is insufficient
    }
}
