CC=g++
FLAGS=-std=c++2a -c -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread


all: test_bin

test_bin: test.o matrix.o
	$(CC) test.o matrix.o -o test_bin $(TEST_LIBS)

test.o: test.cpp
	$(CC) $(FLAGS) test.cpp

matrix.o: matrix.cpp
	$(CC) $(FLAGS) matrix.cpp
 
test:
	./test_bin

clean:
	rm -f *.o test