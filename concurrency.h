#ifndef CONCURRENCY_H
#define CONCURRENCY_H

#include <mutex>

extern int account_balance;
extern std::mutex mtx;

void deposit(int amount);
void withdraw(int amount);

#endif
