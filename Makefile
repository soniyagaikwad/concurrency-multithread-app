all:
	g++ -g -std=c++14 -I. -Wall -o concurrency concurrency.cpp -lpthread

