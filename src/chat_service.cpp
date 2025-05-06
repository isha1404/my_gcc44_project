#include "../include/chat_service.h"
#include <algorithm>

ChatService::ChatService() {
}

bool ChatService::registerUser(const std::string& username) {
    if (users.find(username) != users.end()) {
        return false; // User already exists
    }
    
    users[username] = User(username);
    return true;
}

bool ChatService::login(const std::string& username) {
    if (users.find(username) == users.end()) {
        return false; // User does not exist
    }
    
    users[username].setOnline(true);
    return true;
}

bool ChatService::logout(const std::string& username) {
    if (users.find(username) == users.end()) {
        return false; // User does not exist
    }
    
    users[username].setOnline(false);
    return true;
}

bool ChatService::sendMessage(const std::string& sender, const std::string& content) {
    if (users.find(sender) == users.end() || !users[sender].isOnline()) {
        return false; // User does not exist or is not online
    }
    
    messages.push_back(Message(sender, content));
    return true;
}

std::vector<Message> ChatService::getMessages() const {
    return messages;
}

bool ChatService::isUserRegistered(const std::string& username) const {
    return users.find(username) != users.end();
}

bool ChatService::isUserOnline(const std::string& username) const {
    if (users.find(username) == users.end()) {
        return false;
    }
    return users.at(username).isOnline();
}
