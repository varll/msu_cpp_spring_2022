CC=g++
FLAGS=-std=c++2a -c -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread


all: test_bin

test_bin: test.o allocator.o
	$(CC) test.o allocator.o -o test_bin $(TEST_LIBS)

test.o: test.cpp
	$(CC) $(FLAGS) test.cpp

allocator.o:
	$(CC) $(FLAGS) allocator.cpp
 
test:
	./test_bin

clean:
	rm -f *.o test