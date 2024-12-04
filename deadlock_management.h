#ifndef DEADLOCK_MANAGEMENT_H
#define DEADLOCK_MANAGEMENT_H

#include <thread>
#include <mutex>
#include <map>
#include <unordered_set>
#include <atomic>

/**
 * @brief Mutex used for synchronization in deadlock detection.
 */
extern std::mutex detect_mutex;

/**
 * @brief A map that represents the wait-for graph, where each thread is associated with a list of threads it is waiting for.
 */
extern std::map<std::thread::id, std::vector<std::thread::id>> wait_for_graph;

/**
 * @brief Flag that tracks if a deadlock has been detected.
 */
extern std::atomic<bool> deadlock_detected;

/**
 * @brief Adds an edge to the wait-for graph, representing that thread t1 is waiting for thread t2.
 * 
 * @param t1 The thread that is waiting.
 * @param t2 The thread that is being waited on.
 */
void add_wait_for(std::thread::id t1, std::thread::id t2);

/**
 * @brief Removes an edge from the wait-for graph for thread t1.
 * 
 * @param t1 The thread whose dependencies are to be removed.
 */
void remove_wait_for(std::thread::id t1);

/**
 * @brief Detects cycles in the wait-for graph to identify deadlocks.
 * 
 * This function performs a depth-first search (DFS) to detect cycles in the wait-for graph, which indicate a deadlock.
 * 
 * @param current The thread currently being checked for deadlock.
 * @param visited Set of threads already visited during DFS.
 * @return True if a cycle is detected; false otherwise.
 */
bool detect_deadlock(std::thread::id current, std::unordered_set<std::thread::id>& visited);

/**
 * @brief Continuously checks the wait-for graph for any potential deadlocks.
 * 
 * This function periodically inspects the wait-for graph and logs any detected deadlock.
 */
void check_for_deadlock();

/**
 * @brief Wrapper function to manage deposit operations and avoid deadlock.
 * 
 * This function adds the calling thread to the wait-for graph before performing the deposit, and cleans up afterward.
 * 
 * @param amount The amount to deposit.
 */
void attempt_deposit(int amount);

/**
 * @brief Wrapper function to manage withdrawal operations and avoid deadlock.
 * 
 * This function adds the calling thread to the wait-for graph before performing the withdrawal, and cleans up afterward.
 * 
 * @param amount The amount to withdraw.
 */
void attempt_withdraw(int amount);

#endif