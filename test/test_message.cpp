#include <iostream>
#include <cassert>
#include <cstring>
#include "../include/message.h"

void test_message_creation() {
    std::cout << "Testing message creation... ";
    
    Message msg("user1", "Hello, world!");
    
    assert(msg.getSender() == "user1");
    assert(msg.getContent() == "Hello, world!");
    assert(msg.getTimestamp() > 0);
    
    std::cout << "PASSED" << std::endl;
}

void test_message_to_string() {
    std::cout << "Testing message toString... ";
    
    Message msg("user1", "Hello, world!");
    std::string str = msg.toString();
    
    assert(str.find("user1") != std::string::npos);
    assert(str.find("Hello, world!") != std::string::npos);
    
    std::cout << "PASSED" << std::endl;
}

int main() {
    std::cout << "=== Message Tests ===" << std::endl;
    
    test_message_creation();
    test_message_to_string();
    
    std::cout << "All message tests passed!" << std::endl;
    return 0;
}
