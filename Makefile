# Makefile for Simple Messaging Service
# Compatible with GCC 4.4

CXX = g++
CXXFLAGS = -Wall -g -std=c++98
INCLUDES = -I./include
LIBS = -lsqlite3

# Source files
SRCS = src/message.cpp src/user.cpp src/database.cpp src/chat_service.cpp src/main.cpp
TEST_SRCS = test/test_main.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)
LIB_OBJS = src/message.o src/user.o src/database.o src/chat_service.o

# Executable names
EXEC = messaging_service
TEST_EXEC = run_tests

# Default target
all: $(EXEC) $(TEST_EXEC)

# Link object files to create executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LIBS)

# Link test object files to create test executable
$(TEST_EXEC): $(LIB_OBJS) $(TEST_SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $(LIB_OBJS) $(TEST_SRCS) $(LIBS)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(EXEC) $(TEST_EXEC) src/*.o test/*.o *.db

# Run the program
run: $(EXEC)
	./$(EXEC)

# Run the tests
test: $(TEST_EXEC)
	./$(TEST_EXEC)

.PHONY: all clean run test
