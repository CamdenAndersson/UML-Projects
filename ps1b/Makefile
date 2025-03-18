CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
# Your .hpp files
DEPS = FibLFSR.hpp PhotoMagic.hpp
# Your compiled .o files
OBJECTS = FibLFSR.o PhotoMagic.o
# The name of your program
PROGRAM = PhotoMagic 

SLIB = PhotoMagic.a

.PHONY: all clean lint

# Wildcard recipe to make .o files from corresponding .cpp file
#%.o: %.cpp $(DEPS)
#	$(CC) $(CFLAGS) -c $<

all: $(PROGRAM) PhotoMagic.a test

main.o: main.cpp FibLFSR.hpp PhotoMagic.hpp 
	$(CC) $(CFLAGS) -c $< -o $@ 

PhotoMagic.o: PhotoMagic.cpp PhotoMagic.hpp
	$(CC) $(CFLAGS) -c $< -o $@ 

FibLFSR.o: FibLFSR.cpp FibLFSR.hpp
	$(CC) $(CFLAGS) -c $< -o $@ 

PhotoMagic: PhotoMagic.o main.o FibLFSR.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

test: test.o FibLFSR.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

test.o: test.cpp FibLFSR.hpp
	$(CC) $(CFLAGS) -c $< -o $@ 

PhotoMagic.a: PhotoMagic.o FibLFSR.o
	ar rcs PhotoMagic.a FibLFSR.o PhotoMagic.o



clean:
	rm *.o *.a $(PROGRAM) test *.gch

lint:
	cpplint *.cpp *.hpp
