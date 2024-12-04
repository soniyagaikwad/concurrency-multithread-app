#include <iostream>
#include <thread>
#include "producer_consumer.h"
#include "synchronization.h"

// Function to demonstrate the producer-consumer problem
void producer_consumer_demo() {
    // Output the initial balance before any producer or consumer actions
    std::cout << "Initial Balance: " << account_balance << std::endl;

    // Start a producer thread to simulate depositing funds into the account
    std::thread producer_thread([]() {
        std::cout << "Producer depositing 1000." << std::endl;
        producer(1000);  // Deposit $1000 into the account
    });

    // Start a consumer thread to simulate withdrawing funds from the account
    std::thread consumer_thread([]() {
        std::cout << "Consumer withdrawing 500." << std::endl;
        consumer(500);  // Withdraw $500 from the account
    });

    // Wait for both the producer and consumer threads to finish their operations
    producer_thread.join();  // Ensure the producer thread completes before moving forward
    consumer_thread.join();  // Ensure the consumer thread completes before moving forward

    // Output the final balance after both producer and consumer operations have completed
    std::cout << "Final Balance (after producer-consumer operations): " << account_balance << std::endl;
}

int main() {
    // Call the demo function to execute the producer-consumer scenario
    producer_consumer_demo();
    return 0;
}
