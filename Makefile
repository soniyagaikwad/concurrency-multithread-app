# Phony targets to avoid conflicts with file names
.PHONY: all clean

# Targets for all demos
all: demo_concurrency demo_synchronization demo_deadlock_management demo_producer_consumer

# Build demo for concurrency
demo_concurrency: demo_concurrency.o concurrency.o deadlock_management.o producer_consumer.o synchronization.o
	g++ -g -std=c++14 -Wall -I. -o demo_concurrency demo_concurrency.o concurrency.o deadlock_management.o producer_consumer.o synchronization.o -lpthread

# Build demo for synchronization
demo_synchronization: demo_synchronization.o synchronization.o deadlock_management.o producer_consumer.o
	g++ -g -std=c++14 -Wall -I. -o demo_synchronization demo_synchronization.o synchronization.o deadlock_management.o producer_consumer.o -lpthread

# Build demo for deadlock management
demo_deadlock_management: demo_deadlock_management.o deadlock_management.o synchronization.o
	g++ -g -std=c++14 -Wall -I. -o demo_deadlock_management demo_deadlock_management.o deadlock_management.o synchronization.o -lpthread

# Build demo for inter-thread communication
demo_producer_consumer: demo_producer_consumer.o producer_consumer.o synchronization.o
	g++ -g -std=c++14 -Wall -I. -o demo_producer_consumer demo_producer_consumer.o producer_consumer.o synchronization.o -lpthread

# Compile demo_concurrency.cpp into demo_concurrency.o
demo_concurrency.o: demo_concurrency.cpp concurrency.h synchronization.h
	g++ -g -std=c++14 -Wall -I. -c demo_concurrency.cpp

# Compile demo_synchronization.cpp into demo_synchronization.o
demo_synchronization.o: demo_synchronization.cpp synchronization.h
	g++ -g -std=c++14 -Wall -I. -c demo_synchronization.cpp

# Compile demo_deadlock_management.cpp into demo_deadlock_management.o
demo_deadlock_management.o: demo_deadlock_management.cpp deadlock_management.h synchronization.h
	g++ -g -std=c++14 -Wall -I. -c demo_deadlock_management.cpp

# Compile demo_producer_consumer.cpp into demo_producer_consumer.o
demo_producer_consumer.o: demo_producer_consumer.cpp producer_consumer.h synchronization.h
	g++ -g -std=c++14 -Wall -I. -c demo_producer_consumer.cpp

# Compile concurrency.cpp into concurrency.o
concurrency.o: concurrency.cpp concurrency.h
	g++ -g -std=c++14 -Wall -I. -c concurrency.cpp

# Compile synchronization.cpp into synchronization.o
synchronization.o: synchronization.cpp synchronization.h
	g++ -g -std=c++14 -Wall -I. -c synchronization.cpp

# Compile deadlock_management.cpp into deadlock_management.o
deadlock_management.o: deadlock_management.cpp deadlock_management.h synchronization.h
	g++ -g -std=c++14 -Wall -I. -c deadlock_management.cpp

# Compile producer_consumer.cpp into producer_consumer.o
producer_consumer.o: producer_consumer.cpp producer_consumer.h
	g++ -g -std=c++14 -Wall -I. -c producer_consumer.cpp

# Clean target to remove all generated files
clean:
	rm -f *.o demo_concurrency demo_synchronization demo_deadlock_management demo_producer_consumer
