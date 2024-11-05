#ifndef DEADLOCK_MANAGEMENT_H
#define DEADLOCK_MANAGEMENT_H

#include <thread>
#include <mutex>
#include <map>
#include <unordered_set>
#include <atomic>

extern std::mutex detect_mutex;
extern std::map<std::thread::id, std::vector<std::thread::id>> wait_for_graph;
extern std::atomic<bool> deadlock_detected;

void add_wait_for(std::thread::id t1, std::thread::id t2);
void remove_wait_for(std::thread::id t1);
bool detect_deadlock(std::thread::id current, std::unordered_set<std::thread::id>& visited);
void check_for_deadlock();
void attempt_deposit(int amount);
void attempt_withdraw(int amount);

#endif
