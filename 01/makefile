CC=g++
FLAGS=-Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread


all: test_bin

test_bin: test.o allocator.o
	$(CC) test.o allocator.o -o test_bin $(TEST_LIBS)

test.o: test.cpp
	$(CC) $(FLAGS) -c test.cpp

allocator.o:
	$(CC) $(FLAGS) -c allocator.cpp
 
test:
	./test_bin

clean:
	rm -f *.o test