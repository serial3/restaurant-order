CXX = g++
CXXFLAGS = -g -Wall -Iinclude -std=c++11
LDFLAGS = -lgmock_main -lgmock -lgtest -lgtest_main

TESTS = test_order
APP = main
TEST_SRCS = test_order.cpp
SRC_SRCS = $(filter-out $(TEST_SRCS), $(wildcard *.cpp))
OBJS = $(SRC_SRCS:.cpp=.o)

all: $(TESTS) $(APP)

$(TESTS): $(OBJS) $(TEST_SRCS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

$(APP): $(OBJS) main.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TESTS) $(APP) $(OBJS) *.o

run-tests: $(TESTS)
	./$(TESTS)

run: $(APP)
	./$(APP)
