#ifndef CHAT_SERVICE_H
#define CHAT_SERVICE_H

#include <vector>
#include <map>
#include <string>
#include "message.h"
#include "user.h"
#include "database.h"

class ChatService {
private:
    std::map<std::string, User> users;
    std::vector<Message> messages;
    Database* db;
    bool useDatabase;

public:
    ChatService();
    ChatService(const std::string& dbPath);
    ~ChatService();
    
    bool registerUser(const std::string& username);
    bool login(const std::string& username);
    bool logout(const std::string& username);
    
    bool sendMessage(const std::string& sender, const std::string& content);
    std::vector<Message> getMessages() const;
    
    bool isUserRegistered(const std::string& username) const;
    bool isUserOnline(const std::string& username) const;
    
    bool isDatabaseEnabled() const;
};

#endif // CHAT_SERVICE_H
