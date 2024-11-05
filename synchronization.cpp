#include <iostream>
#include <mutex>
#include "synchronization.h"

int account_balance = 1000;
std::mutex mtx;

// Deposit function with synchronization
void deposit(int amount) {
    std::lock_guard<std::mutex> lock(mtx);  // Lock the mutex with lock_guard
    account_balance += amount;
    std::cout << "Deposited: " << amount 
              << ", New Balance: " << account_balance << std::endl;
}

// Withdraw function with synchronization
void withdraw(int amount) {
    std::lock_guard<std::mutex> lock(mtx);  // Lock the mutex with lock_guard
    if (account_balance >= amount) {
        account_balance -= amount;
        std::cout << "Withdrew: " << amount 
                  << ", New Balance: " << account_balance << std::endl;
    } else {
        std::cout << "Withdrawal of " << amount 
                  << " failed. Insufficient balance." << std::endl;
    }
}
