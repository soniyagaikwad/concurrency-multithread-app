#include <iostream>
#include <thread>
#include <mutex>
#include <map>
#include <vector>
#include <unordered_set>
#include <chrono>
#include <atomic>
#include "synchronization.h" // Include synchronization.h to access account_balance

// Mutex for thread synchronization in deadlock detection
std::mutex detect_mutex;        
std::map<std::thread::id, std::vector<std::thread::id>> wait_for_graph;
std::atomic<bool> deadlock_detected{false}; // Flag to track if a deadlock is detected

// Add an edge to the wait-for graph, representing that thread t1 is waiting for thread t2.
void add_wait_for(std::thread::id t1, std::thread::id t2) {
    std::lock_guard<std::mutex> lock(detect_mutex);  // Lock the mutex to ensure thread safety
    if (t1 != t2) { // Avoid adding self-loops
        wait_for_graph[t1].push_back(t2);  // Add t2 to the list of threads that t1 is waiting for
    }
}

// Remove thread t1's entry from the wait-for graph (i.e., remove t1's dependencies).
void remove_wait_for(std::thread::id t1) {
    std::lock_guard<std::mutex> lock(detect_mutex);  // Lock the mutex to ensure thread safety
    wait_for_graph.erase(t1);  // Erase the entry for thread t1 from the graph
}

// Detect cycles in the wait-for graph to identify potential deadlocks.
bool detect_deadlock(std::thread::id current, std::unordered_set<std::thread::id>& visited) {
    if (visited.find(current) != visited.end()) return true;  // Cycle detected if current thread is already visited
    visited.insert(current);  // Mark the current thread as visited
    for (auto& next : wait_for_graph[current]) { // Check all threads that the current thread is waiting for
        if (detect_deadlock(next, visited)) return true; // Recursively check for deadlock
    }
    visited.erase(current);  // Backtrack: remove current thread from visited set
    return false;
}

// Continuously checks the wait-for graph for deadlocks.
void check_for_deadlock() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Check for deadlocks every 100 milliseconds
        std::lock_guard<std::mutex> lock(detect_mutex);  // Lock the mutex during the check
        for (auto& entry : wait_for_graph) { // Check each thread in the wait-for graph
            std::unordered_set<std::thread::id> visited;  // Set to track visited threads during DFS
            if (detect_deadlock(entry.first, visited)) { // If deadlock is detected for the current thread
                if (!deadlock_detected.exchange(true)) { // Log only once when a deadlock is detected
                    std::cout << "True deadlock detected involving thread " << entry.first << std::endl;
                }
                return;  // Exit the function after detecting a deadlock
            }
        }
        deadlock_detected = false; // Reset the flag if no deadlock is detected after checking all threads
    }
}

// Wrapper function to handle deposit operations with deadlock management.
void attempt_deposit(int amount) {
    std::thread::id another_thread_id = std::this_thread::get_id(); // Placeholder; modify as needed
    add_wait_for(std::this_thread::get_id(), another_thread_id); // Add the current thread to the wait-for graph
    
    deposit(amount);  // Call the existing deposit function from synchronization.cpp
    
    remove_wait_for(std::this_thread::get_id());  // Remove the current thread from the wait-for graph after the deposit
}

// Wrapper function to handle withdrawal operations with deadlock management.
void attempt_withdraw(int amount) {
    std::thread::id another_thread_id = std::this_thread::get_id(); // Placeholder; modify as needed
    add_wait_for(std::this_thread::get_id(), another_thread_id); // Add the current thread to the wait-for graph
    
    withdraw(amount);  // Call the existing withdraw function from synchronization.cpp
    
    remove_wait_for(std::this_thread::get_id());  // Remove the current thread from the wait-for graph after the withdrawal
}