#include <iostream>
#include <cassert>
#include <vector>
#include "../include/chat_service.h"

void test_user_registration() {
    std::cout << "Testing user registration... ";
    
    ChatService chatService;
    
    bool result = chatService.registerUser("user1");
    assert(result == true);
    assert(chatService.isUserRegistered("user1") == true);
    
    result = chatService.registerUser("user1");
    assert(result == false); // Should fail
    
    std::cout << "PASSED" << std::endl;
}

void test_user_login_logout() {
    std::cout << "Testing user login/logout... ";
    
    ChatService chatService;
    
    chatService.registerUser("user1");
    
    bool result = chatService.login("user1");
    assert(result == true);
    assert(chatService.isUserOnline("user1") == true);
    
    result = chatService.logout("user1");
    assert(result == true);
    assert(chatService.isUserOnline("user1") == false);
    
    result = chatService.login("nonexistent");
    assert(result == false);
    
    std::cout << "PASSED" << std::endl;
}

void test_message_sending() {
    std::cout << "Testing message sending... ";
    
    ChatService chatService;
    
    chatService.registerUser("user1");
    chatService.login("user1");
    
    bool result = chatService.sendMessage("user1", "Hello, world!");
    assert(result == true);
    
    std::vector<Message> messages = chatService.getMessages();
    assert(messages.size() == 1);
    assert(messages[0].getSender() == "user1");
    assert(messages[0].getContent() == "Hello, world!");
    
    chatService.logout("user1");
    result = chatService.sendMessage("user1", "This should fail");
    assert(result == false);
    
    messages = chatService.getMessages();
    assert(messages.size() == 1);
    
    std::cout << "PASSED" << std::endl;
}

int main() {
    std::cout << "=== ChatService Tests ===" << std::endl;
    
    test_user_registration();
    test_user_login_logout();
    test_message_sending();
    
    std::cout << "All chat service tests passed!" << std::endl;
    return 0;
}
