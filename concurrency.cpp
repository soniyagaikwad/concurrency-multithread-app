#include <iostream>
#include <thread>

int account_balance = 1000; // initial account balance

// Deposit money without synchronization
void deposit(int amount) {
    account_balance += amount;
    std::cout << "Deposited: " << amount 
              << ", New Balance: " << account_balance << std::endl;
}

// Withdraw money without synchronization
void withdraw(int amount) {
    if (account_balance >= amount) {
        account_balance -= amount;
        std::cout << "Withdrew: " << amount 
                  << ", New Balance: " << account_balance << std::endl;
    } else {
        std::cout << "Withdrawal of " << amount << " failed. Insufficient balance." << std::endl;
    }
}



