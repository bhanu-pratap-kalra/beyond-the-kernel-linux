CXX = g++
CXXFLAGS = -std=c++20 -O2 -Wall -Wextra

TARGET = SimpleIterationExample
SOURCE = SimpleIterationExample.cpp

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCE) Makefile
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SOURCE) $(LDFLAGS) $(LDLIBS) -o $@

clean:
	$(RM) $(TARGET)
