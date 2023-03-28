CC=g++
FLAGS=-std=c++20 -Wall -pedantic -Werror -Wextra
TEST_LIB=-L/opt/homebrew/Cellar/googletest/1.12.1_1/lib -I/opt/homebrew/Cellar/googletest/1.12.1_1/lib/include/ -lgtest -lgtest_main -lpthread -Qunused-arguments

all: token_parser test_bin

token_parser: TokenParser.cpp TokenParser.hpp
	$(CC) $(FLAGS) -c TokenParser.cpp

test_bin: TokenParser.o test.cpp
	$(CC) $(FLAGS) TokenParser.o test.cpp -o test_bin $(TEST_LIB)

test:
	./test_bin

clean:
	rm -f *.o test_bin
	
