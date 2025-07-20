CXX = g++
CXXFLAGS = -std=c++20 -Wall -Iinclude
SRC = $(wildcard src/**/*.cpp)
TESTS = $(wildcard tests/*.cpp)

all: main

main: main.cpp $(SRC)
	$(CXX) $(CXXFLAGS) -o logistic_churn main.cpp $(SRC)

test: $(TESTS) $(SRC)
	$(CXX) $(CXXFLAGS) -o run_tests $(TESTS) $(SRC)
	./run_tests

clean:
	rm -f logistic_churn run_tests
