#include <iostream>
#include <string>
#include <vector>
#include "../include/chat_service.h"

void displayHelp() {
    std::cout << "Available commands:" << std::endl;
    std::cout << "  register <username> - Register a new user" << std::endl;
    std::cout << "  login <username> - Login as a user" << std::endl;
    std::cout << "  logout <username> - Logout a user" << std::endl;
    std::cout << "  send <username> <message> - Send a message as a user" << std::endl;
    std::cout << "  messages - Display all messages" << std::endl;
    std::cout << "  users - Display all registered users" << std::endl;
    std::cout << "  help - Display this help message" << std::endl;
    std::cout << "  exit - Exit the program" << std::endl;
}

int main() {
    ChatService chatService;
    std::string command, username, message;
    
    std::cout << "Simple Messaging Service" << std::endl;
    std::cout << "Type 'help' for available commands" << std::endl;
    
    while (true) {
        std::cout << "> ";
        std::cin >> command;
        
        if (command == "register") {
            std::cin >> username;
            if (chatService.registerUser(username)) {
                std::cout << "User '" << username << "' registered successfully" << std::endl;
            } else {
                std::cout << "User '" << username << "' already exists" << std::endl;
            }
        } else if (command == "login") {
            std::cin >> username;
            if (chatService.login(username)) {
                std::cout << "User '" << username << "' logged in successfully" << std::endl;
            } else {
                std::cout << "User '" << username << "' does not exist" << std::endl;
            }
        } else if (command == "logout") {
            std::cin >> username;
            if (chatService.logout(username)) {
                std::cout << "User '" << username << "' logged out successfully" << std::endl;
            } else {
                std::cout << "User '" << username << "' does not exist" << std::endl;
            }
        } else if (command == "send") {
            std::cin >> username;
            std::cin.ignore(); // Ignore the space after username
            std::getline(std::cin, message);
            
            if (chatService.sendMessage(username, message)) {
                std::cout << "Message sent successfully" << std::endl;
            } else {
                std::cout << "Failed to send message. User does not exist or is not logged in" << std::endl;
            }
        } else if (command == "messages") {
            std::vector<Message> messages = chatService.getMessages();
            if (messages.empty()) {
                std::cout << "No messages" << std::endl;
            } else {
                std::cout << "Messages:" << std::endl;
                for (size_t i = 0; i < messages.size(); ++i) {
                    std::cout << messages[i].toString() << std::endl;
                }
            }
        } else if (command == "users") {
            std::cout << "Users:" << std::endl;
            std::cout << "Feature not implemented yet" << std::endl;
        } else if (command == "help") {
            displayHelp();
        } else if (command == "exit") {
            std::cout << "Goodbye!" << std::endl;
            break;
        } else {
            std::cout << "Unknown command. Type 'help' for available commands" << std::endl;
        }
    }
    
    return 0;
}
