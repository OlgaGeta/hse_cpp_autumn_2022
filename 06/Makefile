CC=g++
FLAGS=-std=c++20 -Wall -pedantic -Werror -Wextra 
TEST_LIB=-L/opt/homebrew/Cellar/googletest/1.12.1_1/lib -I/opt/homebrew/Cellar/googletest/1.12.1_1/lib/include/ -lgtest -lgtest_main -lpthread -Qunused-arguments

all: iskl test_bin

iskl: iskl.cpp 
	$(CC) $(FLAGS) -c iskl.cpp

test_bin: iskl.o tests.cpp
	$(CC) $(FLAGS) iskl.o tests.cpp -o test_bin $(TEST_LIB)

test:
	./test_bin

clean:
	rm -f *.o test_bin
	
