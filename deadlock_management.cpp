#include <iostream>
#include <thread>
#include <mutex>
#include <map>
#include <vector>
#include <unordered_set>
#include <chrono>
#include <atomic>
#include "synchronization.h" // Include synchronization.h to access account_balance

// Mutex for deadlock detection
std::mutex detect_mutex;        
std::map<std::thread::id, std::vector<std::thread::id>> wait_for_graph;
std::atomic<bool> deadlock_detected{false}; // To track deadlock status

// Function to add edges to the wait-for graph
void add_wait_for(std::thread::id t1, std::thread::id t2) {
    std::lock_guard<std::mutex> lock(detect_mutex);
    wait_for_graph[t1].push_back(t2);
}

// Function to remove edges from the wait-for graph
void remove_wait_for(std::thread::id t1) {
    std::lock_guard<std::mutex> lock(detect_mutex);
    wait_for_graph.erase(t1);
}

// Deadlock detection: detects cycles in the wait-for graph
bool detect_deadlock(std::thread::id current, std::unordered_set<std::thread::id>& visited) {
    if (visited.find(current) != visited.end()) return true;
    visited.insert(current);
    for (auto& next : wait_for_graph[current]) {
        if (detect_deadlock(next, visited)) return true;
    }
    visited.erase(current);
    return false;
}

// Function to check if deadlock exists
void check_for_deadlock() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Reduce check frequency
        std::lock_guard<std::mutex> lock(detect_mutex);
        for (auto& entry : wait_for_graph) {
            std::unordered_set<std::thread::id> visited;
            if (detect_deadlock(entry.first, visited)) {
                if (!deadlock_detected.exchange(true)) { // Only log once
                    std::cout << "True deadlock detected involving thread " << entry.first << std::endl;
                }
                return;
            }
        }
        deadlock_detected = false;
    }
}

// Wrapper function to handle wait-for graph and deadlock detection
void attempt_deposit(int amount) {
    add_wait_for(std::this_thread::get_id(), std::this_thread::get_id()); // Add to graph
    deposit(amount); // Use the existing deposit function from synchronization.cpp
}

// Wrapper function to handle wait-for graph and deadlock detection
void attempt_withdraw(int amount) {
    add_wait_for(std::this_thread::get_id(), std::this_thread::get_id()); // Add to graph
    withdraw(amount); // Use the existing withdraw function from synchronization.cpp
}
