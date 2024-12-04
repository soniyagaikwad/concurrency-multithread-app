#ifndef SYNCHRONIZATION_H
#define SYNCHRONIZATION_H

#include <mutex>

// Global variable to store the account balance
extern int account_balance;  

// Mutex to protect access to the account balance, ensuring thread safety
extern std::mutex mtx;        

/**
 * @brief Deposits a specified amount into the account, updating the balance.
 * 
 * This function is synchronized using a mutex to ensure that only one thread
 * can modify the account balance at a time.
 * 
 * @param amount The amount to deposit into the account.
 */
void deposit(int amount);

/**
 * @brief Withdraws a specified amount from the account, updating the balance.
 * 
 * This function is synchronized using a mutex to ensure that only one thread
 * can modify the account balance at a time. If the withdrawal amount exceeds
 * the available balance, the operation is rejected.
 * 
 * @param amount The amount to withdraw from the account.
 */
void withdraw(int amount);

#endif
