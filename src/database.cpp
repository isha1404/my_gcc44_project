#include "../include/database.h"
#include <iostream>
#include <sstream>
#include <cstring>

Database::Database(const std::string& dbPath)
    : dbPath(dbPath), db(NULL), isConnected(false) {
}

Database::~Database() {
    disconnect();
}

bool Database::connect() {
    if (isConnected) {
        return true;
    }
    
    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }
    
    isConnected = true;
    return createTables();
}

bool Database::disconnect() {
    if (!isConnected) {
        return true;
    }
    
    int rc = sqlite3_close(db);
    if (rc != SQLITE_OK) {
        std::cerr << "Error closing database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    
    isConnected = false;
    db = NULL;
    return true;
}

bool Database::isOpen() const {
    return isConnected;
}

bool Database::createTables() {
    if (!isConnected) {
        return false;
    }
    
    const char* createUsersTable = 
        "CREATE TABLE IF NOT EXISTS users ("
        "username TEXT PRIMARY KEY,"
        "online INTEGER"
        ");";
    
    const char* createMessagesTable = 
        "CREATE TABLE IF NOT EXISTS messages ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "sender TEXT,"
        "content TEXT,"
        "timestamp INTEGER,"
        "FOREIGN KEY(sender) REFERENCES users(username)"
        ");";
    
    char* errMsg = NULL;
    int rc = sqlite3_exec(db, createUsersTable, NULL, NULL, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    
    rc = sqlite3_exec(db, createMessagesTable, NULL, NULL, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    
    return true;
}

bool Database::saveMessage(const Message& message) {
    if (!isConnected) {
        return false;
    }
    
    const char* sql = 
        "INSERT INTO messages (sender, content, timestamp) "
        "VALUES (?, ?, ?);";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    
    sqlite3_bind_text(stmt, 1, message.getSender().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, message.getContent().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 3, message.getTimestamp());
    
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    return rc == SQLITE_DONE;
}

std::vector<Message> Database::loadMessages() {
    std::vector<Message> messages;
    
    if (!isConnected) {
        return messages;
    }
    
    const char* sql = 
        "SELECT sender, content, timestamp FROM messages "
        "ORDER BY timestamp ASC;";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        return messages;
    }
    
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        const char* sender = (const char*)sqlite3_column_text(stmt, 0);
        const char* content = (const char*)sqlite3_column_text(stmt, 1);
        time_t timestamp = sqlite3_column_int64(stmt, 2);
        
        Message msg(sender, content);
        
        messages.push_back(msg);
    }
    
    sqlite3_finalize(stmt);
    
    return messages;
}

bool Database::saveUser(const std::string& username, bool online) {
    if (!isConnected) {
        return false;
    }
    
    const char* sql = 
        "INSERT OR REPLACE INTO users (username, online) "
        "VALUES (?, ?);";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, online ? 1 : 0);
    
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    return rc == SQLITE_DONE;
}

bool Database::updateUserStatus(const std::string& username, bool online) {
    if (!isConnected) {
        return false;
    }
    
    const char* sql = 
        "UPDATE users SET online = ? WHERE username = ?;";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    
    sqlite3_bind_int(stmt, 1, online ? 1 : 0);
    sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);
    
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    return rc == SQLITE_DONE;
}

bool Database::userExists(const std::string& username) {
    if (!isConnected) {
        return false;
    }
    
    const char* sql = 
        "SELECT 1 FROM users WHERE username = ?;";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    
    rc = sqlite3_step(stmt);
    bool exists = (rc == SQLITE_ROW);
    
    sqlite3_finalize(stmt);
    
    return exists;
}

bool Database::isUserOnline(const std::string& username) {
    if (!isConnected) {
        return false;
    }
    
    const char* sql = 
        "SELECT online FROM users WHERE username = ?;";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    
    rc = sqlite3_step(stmt);
    bool online = false;
    
    if (rc == SQLITE_ROW) {
        online = (sqlite3_column_int(stmt, 0) == 1);
    }
    
    sqlite3_finalize(stmt);
    
    return online;
}
