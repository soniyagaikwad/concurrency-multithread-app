#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx; // mutex for synchronizing access to balance
int account_balance = 1000; // initial account balance

// deposit money
void deposit(int amount) {
    mtx.lock(); // lock the mutex
    account_balance += amount;
    std::cout << "Deposited: " << amount 
              << ", New Balance: " << account_balance << std::endl;
    mtx.unlock(); // unlock the mutex
}

// withdraw money
void withdraw(int amount) {
    mtx.lock(); // lock the mutex
    if (account_balance >= amount) {
        account_balance -= amount;
        std::cout << "Withdrew: " << amount 
                  << ", New Balance: " << account_balance << std::endl;
    } else {
        std::cout << "Withdrawal of " << amount << " failed. Insufficient balance." << std::endl;
    }
    mtx.unlock(); // unlock the mutex
}

int main() {
    std::thread t1(deposit, 500);  // deposit $500
    std::thread t2(withdraw, 300); // withdraw $300

    t1.join();  // wait for the deposit thread to finish
    t2.join();  // wait for the withdraw thread to finish

    return 0;
}
