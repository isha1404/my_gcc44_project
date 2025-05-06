#include <iostream>
#include <vector>
#include <stdexcept>
#include "../include/message.h"
#include "../include/user.h"
#include "../include/chat_service.h"

int run_message_tests();
int run_user_tests();
int run_chat_service_tests();

int main() {
    std::cout << "==============================" << std::endl;
    std::cout << "Running all tests..." << std::endl;
    std::cout << "==============================" << std::endl;
    
    int result = 0;
    
    result += run_message_tests();
    result += run_user_tests();
    result += run_chat_service_tests();
    
    if (result == 0) {
        std::cout << "==============================" << std::endl;
        std::cout << "All tests passed successfully!" << std::endl;
        std::cout << "==============================" << std::endl;
        return 0;
    } else {
        std::cout << "==============================" << std::endl;
        std::cout << "Some tests failed!" << std::endl;
        std::cout << "==============================" << std::endl;
        return 1;
    }
}

int run_message_tests() {
    std::cout << "\n=== Message Tests ===" << std::endl;
    
    try {
        std::cout << "Testing message creation... ";
        Message msg("user1", "user2", "Hello, world!");
        if (msg.getSender() != "user1" || 
            msg.getReceiver() != "user2" ||
            msg.getContent() != "Hello, world!" || 
            msg.getTimestamp() <= 0) {
            throw std::runtime_error("Message creation test failed");
        }
        std::cout << "PASSED" << std::endl;
        
        std::cout << "Testing message toString... ";
        std::string str = msg.toString();
        if (str.find("user1") == std::string::npos || 
            str.find("user2") == std::string::npos ||
            str.find("Hello, world!") == std::string::npos) {
            throw std::runtime_error("Message toString test failed");
        }
        std::cout << "PASSED" << std::endl;
        
        std::cout << "All message tests passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cout << "FAILED: " << e.what() << std::endl;
        return 1;
    }
}

int run_user_tests() {
    std::cout << "\n=== User Tests ===" << std::endl;
    
    try {
        std::cout << "Testing user creation... ";
        User user("testuser");
        if (user.getUsername() != "testuser" || user.isOnline() != false) {
            throw std::runtime_error("User creation test failed");
        }
        std::cout << "PASSED" << std::endl;
        
        std::cout << "Testing user status... ";
        user.setOnline(true);
        if (user.isOnline() != true) {
            throw std::runtime_error("User status (online) test failed");
        }
        
        user.setOnline(false);
        if (user.isOnline() != false) {
            throw std::runtime_error("User status (offline) test failed");
        }
        std::cout << "PASSED" << std::endl;
        
        std::cout << "All user tests passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cout << "FAILED: " << e.what() << std::endl;
        return 1;
    }
}

int run_chat_service_tests() {
    std::cout << "\n=== ChatService Tests ===" << std::endl;
    
    try {
        ChatService chatService;
        
        std::cout << "Testing user registration... ";
        bool result = chatService.registerUser("user1");
        if (result != true || !chatService.isUserRegistered("user1")) {
            throw std::runtime_error("User registration test failed");
        }
        
        result = chatService.registerUser("user1");
        if (result != false) {
            throw std::runtime_error("Duplicate user registration test failed");
        }
        std::cout << "PASSED" << std::endl;
        
        std::cout << "Testing user login/logout... ";
        result = chatService.login("user1");
        if (result != true || !chatService.isUserOnline("user1")) {
            throw std::runtime_error("User login test failed");
        }
        
        result = chatService.logout("user1");
        if (result != true || chatService.isUserOnline("user1")) {
            throw std::runtime_error("User logout test failed");
        }
        
        result = chatService.login("nonexistent");
        if (result != false) {
            throw std::runtime_error("Non-existent user login test failed");
        }
        std::cout << "PASSED" << std::endl;
        
        std::cout << "Testing message sending... ";
        chatService.registerUser("user2");
        chatService.login("user1");
        
        result = chatService.sendMessage("user1", "user2", "Hello, world!");
        if (result != true) {
            throw std::runtime_error("Message sending test failed");
        }
        
        std::vector<Message> messages = chatService.getMessages();
        if (messages.size() != 1 || 
            messages[0].getSender() != "user1" || 
            messages[0].getReceiver() != "user2" ||
            messages[0].getContent() != "Hello, world!") {
            throw std::runtime_error("Message retrieval test failed");
        }
        
        chatService.logout("user1");
        result = chatService.sendMessage("user1", "user2", "This should fail");
        if (result != false) {
            throw std::runtime_error("Offline user message sending test failed");
        }
        
        messages = chatService.getMessages();
        if (messages.size() != 1) {
            throw std::runtime_error("Message count test failed");
        }
        std::cout << "PASSED" << std::endl;
        
        std::cout << "All chat service tests passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cout << "FAILED: " << e.what() << std::endl;
        return 1;
    }
}
