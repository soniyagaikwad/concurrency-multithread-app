# Concurrency Control in Multi-Threaded Applications

**Overview**:  
This program simulates a bank transaction system, focusing on key concepts in multi-threaded programming such as concurrency, deadlock prevention, and inter-process communication (IPC). The system models scenarios where multiple threads are handling deposit and withdrawal operations on a shared bank account, demonstrating the need for synchronization mechanisms to ensure consistency and avoid race conditions.

**Key Concepts**:  
- **Concurrency**: The ability of a system to handle multiple threads of execution at once, potentially executing in parallel.
- **Deadlocks**: A situation where two or more threads are blocked indefinitely, each waiting for the other to release a resource.
- **Process Synchronization**: Mechanisms like mutexes and condition variables used to ensure that concurrent processes or threads do not interfere with each other, maintaining data consistency.
- **Inter-Thread Communication**: The coordination between threads to ensure correct sequencing of actions and sharing of data, typically using condition variables or other synchronization primitives.

**Language(s) of choice**:  
- **C++**: The program is written in C++ and leverages the C++ Standard Library to manage multi-threading and synchronization. The features used include `std::thread`, `std::mutex`, `std::lock_guard`, and `std::condition_variable`.

---

## Features

- **Concurrency Management**:  
  The system uses multiple threads to simulate concurrent bank transactions. Threads perform deposit and withdrawal operations on a shared account balance.

- **Synchronized Transactions**:  
  Ensures that concurrent transactions (deposit/withdraw) are handled correctly using locks to prevent race conditions and maintain consistency of the account balance.

- **Deadlock Prevention**:  
  The program includes mechanisms to detect and prevent deadlocks that may occur when multiple threads are waiting on each other to release resources.

- **Producer-Consumer Model**:  
  Demonstrates inter-thread communication where one thread (producer) deposits money into the account, and another thread (consumer) withdraws funds.

---

## Explanation of Files

- **concurrency.cpp / concurrency.h**:  
  Implements concurrency-related functions, including deposit and withdrawal operations for multiple threads, demonstrating potential race conditions if not handled properly.

- **synchronization.cpp / synchronization.h**:  
  Contains functions for handling deposit and withdrawal operations, synchronized using a mutex to avoid race conditions.

- **deadlock_management.cpp / deadlock_management.h**:  
  Provides functions to detect and prevent deadlocks in multi-threaded operations, ensuring that thread operations do not result in a deadlock situation.

- **producer_consumer.cpp / producer_consumer.h**:  
  Implements the producer-consumer problem where a producer deposits money and a consumer withdraws it, using condition variables for thread synchronization.

- **demo_concurrency.cpp**:  
  Demonstrates a scenario with concurrent transactions, showing potential issues when synchronization is not applied.

- **demo_synchronization.cpp**:  
  Shows how synchronization (via mutexes) ensures thread-safe access to shared resources.

- **demo_deadlock_management.cpp**:  
  Simulates the occurrence and detection of deadlocks, showing how to prevent them with appropriate locks.

- **demo_producer_consumer.cpp**:  
  Demonstrates a producer-consumer scenario where a producer deposits funds and a consumer withdraws funds, using condition variables to ensure proper synchronization.

- **Makefile**:  
  Contains rules for compiling and linking all the demo programs.

---

## How to Build and Run

1. **Prerequisites**:  
   - C++14 compatible compiler (e.g., g++)
   - POSIX threads library (`-lpthread`)

2. **Building the Program**:  
   Run the following command to build all demos:

   ```bash
   make
   ```

### Running the Demos

After building the project, you can run each demo as follows:

- **Concurrency Demo**:  
  Run the concurrency demo using:
  ```bash
  ./demo_concurrency
  ```

- **Synchronization Demo**:  
  Run the synchronization demo using:
  ```bash
  ./demo_synchronization
  ```

- **Deadlock Management Demo**:  
  Run the deadlock management demo using:
  ```bash
  ./demo_deadlock_management
  ```

- **Producer-Consumer Demo**:  
  Run the producer-consumer demo using:
  ```bash
  ./demo_producer_consumer
  ```