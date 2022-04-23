CC=g++
FLAGS=-std=c++2a -c -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread


all: test_bin

test_bin: tests.o BigInt.o
	$(CC) tests.o BigInt.o -o test_bin $(TEST_LIBS)

tests.o: tests.cpp
	$(CC) $(FLAGS) tests.cpp

BigInt.o: BigInt.cpp
	$(CC) $(FLAGS) BigInt.cpp
 
test:
	./test_bin

clean:
	rm -f *.o test