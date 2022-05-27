CC=g++
FLAGS=-std=c++2a -c -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread


all: test_bin

test_bin: test.o ThreadPool.o
	$(CC) test.o ThreadPool.o -o test_bin $(TEST_LIBS)

test.o: test.cpp
	$(CC) $(FLAGS) test.cpp

ThreadPool.o: ThreadPool.cpp
	$(CC) $(FLAGS) ThreadPool.cpp
 
test:
	./test_bin

clean:
	rm -f *.o test