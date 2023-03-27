CC=g++-20
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-L/opt/homebrew/Cellar/googletest/1.12.1_1/lib -I/opt/homebrew/Cellar/googletest/1.12.1_1/lib/include/ -lgtest -lgtest_main -lpthread -Qunused-arguments

.PHONY: test clean

all: test_bin

Serializer_Deserializer.o: Serializer_Deserializer.cpp Serializer_Deserializer.hpp other.cpp
	$(CC) $(FLAGS) Serializer_Deserializer.cpp -c

test.o: test.cpp Serializer_Deserializer.hpp other.cpp
	$(CC) $(FLAGS) test.cpp -c

test_bin: Serializer_Deserializer.o test.o
	$(CC) $(FLAGS) Serializer_Deserializer.o test.o -o test_bin $(TEST_LIBS)

test:
	./test_bin

clean:
	rm -f *.o main test_bin

