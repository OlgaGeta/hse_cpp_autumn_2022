CC=g++
FLAGS=-std=c++20 -Wall -pedantic -Werror -Wextra 
TEST_LIB= -L/opt/homebrew/Cellar/googletest/1.12.1_1/lib -I/opt/homebrew/Cellar/googletest/1.12.1_1/lib/include/ -lgtest -lgtest_main -lpthread -Qunused-arguments


all: matrix test_bin

matrix: matrix.cpp
	$(CC) $(FLAGS) -c matrix.cpp

test_bin: matrix.o Test.cpp
	$(CC) $(FLAGS) matrix.o Test.cpp -o test_bin $(TEST_LIB)

test:
	./test_bin

clean:
	rm -f *.o test_bin
	