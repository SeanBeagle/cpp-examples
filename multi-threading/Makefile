#
# Simple Makefile that shows g++ command if <thread> library is included.
#

CC = g++
CCFLAGS = -Wall

multithreading: multithreading.cpp
	$(CC) $(CCFLAGS) -o multithreading multithreading.cpp -pthread

clean:
	- rm multithreading
