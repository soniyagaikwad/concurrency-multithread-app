#include <iostream>
#include "concurrency.h"

// Global variable to track the account balance
int concurrency_account_balance = 1000; // Initial account balance set to $1000

// Function to deposit an amount into the account
void concurrency_deposit(int amount) {
    // Update the account balance by adding the deposit amount
    concurrency_account_balance += amount;
    
    // Output the deposit information and the new account balance to the console
    std::cout << "Deposited: " << amount 
              << ", New Balance: " << concurrency_account_balance << std::endl;
}

// Function to withdraw an amount from the account
void concurrency_withdraw(int amount) {
    // Check if there is enough balance to perform the withdrawal
    if (concurrency_account_balance >= amount) {
        // If there is a sufficient balance, update the account balance by subtracting the withdrawal amount
        concurrency_account_balance -= amount;
        
        // Output the withdrawal information and the new account balance to the console
        std::cout << "Withdrew: " << amount 
                  << ", New Balance: " << concurrency_account_balance << std::endl;
    } else {
        // If there is not enough balance, print a message indicating the failure
        std::cout << "Withdrawal of " << amount << " failed. Insufficient balance." << std::endl;
    }
}


