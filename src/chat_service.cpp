#include "../include/chat_service.h"
#include <algorithm>
#include <iostream>

ChatService::ChatService() : db(NULL), useDatabase(false) {
}

ChatService::ChatService(const std::string& dbPath) : useDatabase(true) {
    db = new Database(dbPath);
    if (!db->connect()) {
        std::cerr << "Failed to connect to database at " << dbPath << std::endl;
        delete db;
        db = NULL;
        useDatabase = false;
    } else {
        messages = db->loadMessages();
    }
}

ChatService::~ChatService() {
    if (db != NULL) {
        db->disconnect();
        delete db;
        db = NULL;
    }
}

bool ChatService::registerUser(const std::string& username) {
    if (users.find(username) != users.end()) {
        return false; // User already exists
    }
    
    users[username] = User(username);
    
    if (useDatabase && db != NULL) {
        return db->saveUser(username, false);
    }
    
    return true;
}

bool ChatService::login(const std::string& username) {
    if (users.find(username) == users.end()) {
        return false; // User does not exist
    }
    
    users[username].setOnline(true);
    
    if (useDatabase && db != NULL) {
        return db->updateUserStatus(username, true);
    }
    
    return true;
}

bool ChatService::logout(const std::string& username) {
    if (users.find(username) == users.end()) {
        return false; // User does not exist
    }
    
    users[username].setOnline(false);
    
    if (useDatabase && db != NULL) {
        return db->updateUserStatus(username, false);
    }
    
    return true;
}

bool ChatService::sendMessage(const std::string& sender, const std::string& content) {
    if (users.find(sender) == users.end() || !users[sender].isOnline()) {
        return false; // User does not exist or is not online
    }
    
    Message msg(sender, content);
    messages.push_back(msg);
    
    if (useDatabase && db != NULL) {
        return db->saveMessage(msg);
    }
    
    return true;
}

std::vector<Message> ChatService::getMessages() const {
    return messages;
}

bool ChatService::isUserRegistered(const std::string& username) const {
    if (useDatabase && db != NULL) {
        return db->userExists(username);
    }
    
    return users.find(username) != users.end();
}

bool ChatService::isUserOnline(const std::string& username) const {
    if (useDatabase && db != NULL) {
        return db->isUserOnline(username);
    }
    
    if (users.find(username) == users.end()) {
        return false;
    }
    return users.at(username).isOnline();
}

bool ChatService::isDatabaseEnabled() const {
    return useDatabase && db != NULL;
}
