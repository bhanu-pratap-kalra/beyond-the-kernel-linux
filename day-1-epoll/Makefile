CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic

DEBUG_FLAGS = -g -O0
RELEASE_FLAGS = -O2

SERVER_TARGET = simple-epoll-server
CLIENT_TARGET = simple-multi-client

SERVER_SOURCE = simple-epoll-server.cpp
CLIENT_SOURCE = simple-multi-client.cpp

release:
	$(CXX) $(CXXFLAGS) $(RELEASE_FLAGS) $(SERVER_SOURCE) -o $(SERVER_TARGET)
	$(CXX) $(CXXFLAGS) $(RELEASE_FLAGS) $(CLIENT_SOURCE) -o $(CLIENT_TARGET)

debug:
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) $(SERVER_SOURCE) -o $(SERVER_TARGET)
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) $(CLIENT_SOURCE) -o $(CLIENT_TARGET)

clean:
	rm -f $(SERVER_TARGET) $(CLIENT_TARGET)
