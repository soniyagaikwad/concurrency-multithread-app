#include <iostream>
#include <thread>
#include <mutex>
#include <map>
#include <vector>
#include <unordered_set>
#include <chrono>
#include <atomic>

std::mutex account_mutex;       // Mutex for synchronizing access to balance
std::mutex detect_mutex;        // Mutex for deadlock detection
int account_balance = 1000;     // Initial account balance
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

// Deposit function with deadlock prevention using try_lock
void deposit(int amount) {
    if (account_mutex.try_lock()) {
        account_balance += amount;
        std::cout << "Deposited: " << amount << ", New Balance: " << account_balance << std::endl;
        account_mutex.unlock(); // Unlock the mutex
    } else {
        std::cout << "Deposit failed due to lock contention." << std::endl;
    }
    remove_wait_for(std::this_thread::get_id());
}

// Withdraw function with deadlock prevention using try_lock
void withdraw(int amount) {
    if (account_mutex.try_lock()) {
        if (account_balance >= amount) {
            account_balance -= amount;
            std::cout << "Withdrew: " << amount << ", New Balance: " << account_balance << std::endl;
        } else {
            std::cout << "Withdrawal of " << amount << " failed. Insufficient balance." << std::endl;
        }
        account_mutex.unlock(); // Unlock the mutex
    } else {
        std::cout << "Withdrawal failed due to lock contention." << std::endl;
    }
    remove_wait_for(std::this_thread::get_id());
}

// Wrapper function to handle wait-for graph and deadlock detection
void attempt_deposit(int amount) {
    add_wait_for(std::this_thread::get_id(), std::this_thread::get_id()); // Add to graph
    deposit(amount);
}

// Wrapper function to handle wait-for graph and deadlock detection
void attempt_withdraw(int amount) {
    add_wait_for(std::this_thread::get_id(), std::this_thread::get_id()); // Add to graph
    withdraw(amount);
}

int main() {
    std::thread t1(attempt_deposit, 500); // Deposit $500
    std::thread t2(attempt_withdraw, 300); // Withdraw $300
    std::thread t3(attempt_deposit, 200); // Deposit $200
    std::thread deadlock_thread(check_for_deadlock); // Separate thread for deadlock monitoring

    t1.join();
    t2.join();
    t3.join();
    deadlock_thread.detach(); // Detach as it runs continuously

    return 0;
}
