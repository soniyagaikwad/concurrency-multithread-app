#ifndef CONCURRENCY_H
#define CONCURRENCY_H

/**
 * @brief External declaration of the global variable `concurrency_account_balance`.
 * 
 * This variable tracks the account balance for the concurrency-related operations.
 */
extern int concurrency_account_balance;

/**
 * @brief Deposits a specified amount into the account.
 * 
 * This function increases the `concurrency_account_balance` by the given `amount`.
 * It logs the deposited amount and the new balance to the console.
 * 
 * @param amount The amount to deposit into the account.
 */
void concurrency_deposit(int amount);

/**
 * @brief Withdraws a specified amount from the account.
 * 
 * This function attempts to decrease the `concurrency_account_balance` by the given `amount`.
 * If there are sufficient funds, the balance is updated and the withdrawal is logged to the console.
 * If the balance is insufficient, a failure message is printed instead.
 * 
 * @param amount The amount to withdraw from the account.
 */
void concurrency_withdraw(int amount);

#endif

