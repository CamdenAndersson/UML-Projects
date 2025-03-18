CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
# Your .hpp files
DEPS = FibLFSR.hpp
# Your compiled .o files
OBJECTS = FibLFSR.o 
# The name of your program
PROGRAM = PhotoMagic

SLIB = PhotoMagic.a

.PHONY: all clean lint


# Wildcard recipe to make .o files from corresponding .cpp file
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

$(PROGRAM): test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

test: test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

PhotoMagic.a: PhotoMagic.o $(OBJECTS)
	ar rcs PhotoMagic.a FibLFSR.o PhotoMagic.o

all: $(PROGRAM) test PhotoMagic.a


clean:
	rm *.o *.a $(PROGRAM) test

lint:
	cpplint *.cpp *.hpp
