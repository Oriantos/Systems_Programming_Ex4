CXX       := g++
CXXFLAGS  := -std=c++17 -Wall -Wextra -g -Icontainer

TARGET := main

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

doctests: doctests.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^


test: doctests
	@valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(TEST_BIN)


clean:
	rm -f $(TARGET) $(TEST_BIN)

.PHONY: all test clean