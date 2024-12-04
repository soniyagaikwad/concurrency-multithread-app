#ifndef PRODUCER_CONSUMER_H
#define PRODUCER_CONSUMER_H

#include <thread>
#include <condition_variable>

/**
 * @brief Producer thread function to deposit funds into the account.
 * 
 * This function calls the existing deposit function and notifies the consumer
 * thread to proceed with withdrawal after the deposit is complete.
 * 
 * @param amount The amount to deposit into the account.
 */
void producer(int amount);

/**
 * @brief Consumer thread function to withdraw funds from the account.
 * 
 * This function waits for funds to be available (i.e., the account balance 
 * must be greater than zero) before calling the existing withdraw function.
 * 
 * @param amount The amount to withdraw from the account.
 */
void consumer(int amount);

#endif
