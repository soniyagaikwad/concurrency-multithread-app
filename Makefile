# Target to build the final executable for concurrency and synchronization
all: concurrency concurrency_sync

# Linking step to create the final executable from object files for concurrency
concurrency: main.o concurrency.o deadlock_management.o producer_consumer.o
	g++ -g -std=c++14 -o concurrency main.o concurrency.o deadlock_management.o producer_consumer.o -lpthread

# Linking step to create the final executable from object files for synchronization
concurrency_sync: main.o synchronization.o deadlock_management.o producer_consumer.o
	g++ -g -std=c++14 -o concurrency_sync main.o synchronization.o deadlock_management.o producer_consumer.o -lpthread

# Compile main.cpp into main.o
main.o: main.cpp concurrency.h synchronization.h deadlock_management.h producer_consumer.h
	g++ -g -std=c++14 -I. -Wall -c main.cpp

# Compile concurrency.cpp into concurrency.o
concurrency.o: concurrency.cpp concurrency.h
	g++ -g -std=c++14 -I. -Wall -c concurrency.cpp

# Compile synchronization.cpp into synchronization.o
synchronization.o: synchronization.cpp synchronization.h
	g++ -g -std=c++14 -I. -Wall -c synchronization.cpp

# Compile deadlock_management.cpp into deadlock_management.o
deadlock_management.o: deadlock_management.cpp deadlock_management.h
	g++ -g -std=c++14 -I. -Wall -c deadlock_management.cpp

# Compile producer_consumer.cpp into producer_consumer.o
producer_consumer.o: producer_consumer.cpp producer_consumer.h
	g++ -g -std=c++14 -I. -Wall -c producer_consumer.cpp

# Clean target to remove generated files
clean:
	rm -f *.o concurrency concurrency_sync
