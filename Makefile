# Makefile for Simple Messaging Service
# Compatible with GCC 4.4

CXX = g++
CXXFLAGS = -Wall -g -std=c++98
INCLUDES = -I./include

# Source files
SRCS = src/message.cpp src/user.cpp src/chat_service.cpp src/main.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = messaging_service

# Default target
all: $(EXEC)

# Link object files to create executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(EXEC)

# Run the program
run: $(EXEC)
	./$(EXEC)

.PHONY: all clean run
