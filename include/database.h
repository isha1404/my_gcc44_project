#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <sqlite3.h>
#include "message.h"

class Database {
private:
    sqlite3* db;
    std::string dbPath;
    bool isConnected;

public:
    Database(const std::string& dbPath);
    ~Database();
    
    bool connect();
    bool disconnect();
    bool isOpen() const;
    
    bool createTables();
    bool saveMessage(const Message& message);
    std::vector<Message> loadMessages();
    std::vector<Message> loadMessagesForUser(const std::string& username);
    
    // User-related database operations
    bool saveUser(const std::string& username, bool online);
    bool updateUserStatus(const std::string& username, bool online);
    bool userExists(const std::string& username);
    bool isUserOnline(const std::string& username);
};

#endif // DATABASE_H
