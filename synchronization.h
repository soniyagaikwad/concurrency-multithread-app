#ifndef SYNCHRONIZATION_H
#define SYNCHRONIZATION_H

#include <mutex>

extern int account_balance;
extern std::mutex mtx;

void deposit(int amount);
void withdraw(int amount);

#endif
