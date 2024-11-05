#ifndef PRODUCER_CONSUMER_H
#define PRODUCER_CONSUMER_H

#include <thread>
#include <condition_variable>

void producer(int amount);
void consumer(int amount);

#endif
