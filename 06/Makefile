CC=g++
FLAGS=-std=c++20 -Wall -pedantic -Werror -Wextra 
TEST_LIB=-L/opt/homebrew/Cellar/googletest/1.12.1_1/lib -I/opt/homebrew/Cellar/googletest/1.12.1_1/lib/include/ -lgtest -lgtest_main -lpthread -Qunused-arguments

all: format test_bin

iskl: format.h
	$(CC) $(FLAGS) -c format.h

test_bin: format.o tests.cpp
	$(CC) $(FLAGS) format.o tests.cpp -o test_bin $(TEST_LIB)

test:
	./test_bin

clean:
	rm -f *.o test_bin
	
