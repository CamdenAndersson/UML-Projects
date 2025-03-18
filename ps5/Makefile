CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
# Your .hpp files
DEPS = EDistance.hpp
# Your compiled .o files
OBJECTS = EDistance.o
# The name of your program
PROGRAM = EDistance

.PHONY: all clean lint

all: $(PROGRAM) test EDistance.a

# Wildcard recipe to make .o files from corresponding .cpp file
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

$(PROGRAM): main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

EDistance.a: EDistance.o 
	ar rcs EDistance.a EDistance.o

test: test.o EDistance.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

test.o: test.cpp EDistance.hpp
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm *.o $(PROGRAM) *.a test

lint:
	cpplint *.cpp *.hpp
