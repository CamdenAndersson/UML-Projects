CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
# Your .hpp files
DEPS = RandWriter.hpp
# Your compiled .o files
OBJECTS = RandWriter.o
# The name of your program
PROGRAM = TextWriter

.PHONY: all clean lint

all: $(PROGRAM) test TextWriter.a

# Wildcard recipe to make .o files from corresponding .cpp file
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

$(PROGRAM): TextWriter.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

TextWriter.a: RandWriter.o
	ar rcs TextWriter.a RandWriter.o

test: test.o RandWriter.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

test.o: test.cpp RandWriter.hpp
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm *.o $(PROGRAM) *.a test

lint:
	cpplint *.cpp *.hpp
