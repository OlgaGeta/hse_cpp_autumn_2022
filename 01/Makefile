CC=g++
FLAGS=-std=c++20 -Wall -pedantic -Werror -Wextra 
TEST_LIB= -L/opt/homebrew/Cellar/googletest/1.12.1_1/lib -I/opt/homebrew/Cellar/googletest/1.12.1_1/lib/include/ -lgtest -lgtest_main -lpthread -Qunused-arguments


all: allocator test_bin

matrix: Allocator.cpp Allocator.hpp
	$(CC) $(FLAGS) -c Allocator.cpp

test_bin: Allocator.o test.cpp
	$(CC) $(FLAGS) allocator.o test.cpp -o test_bin $(TEST_LIB)

test:
	./test_bin

clean:
	rm -f *.o test_bin
	
