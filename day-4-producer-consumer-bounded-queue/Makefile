CXX = g++
TARGET = simple-bounded-queue
SRC = simple-bounded-queue.cpp

COMMON_FLAGS = -std=c++20 -Wall -Wextra -pthread

DEBUG_FLAGS = -g -O0 -DDEBUG
RELEASE_FLAGS = -O2 -DNDEBUG

DEBUG_TARGET = $(TARGET)
RELEASE_TARGET = $(TARGET)

all: release

debug:
	$(CXX) $(COMMON_FLAGS) $(DEBUG_FLAGS) -o $(DEBUG_TARGET) $(SRC)

release:
	$(CXX) $(COMMON_FLAGS) $(RELEASE_FLAGS) -o $(RELEASE_TARGET) $(SRC)

clean:
	rm -f $(DEBUG_TARGET) $(RELEASE_TARGET)
