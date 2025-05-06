#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string username;
    bool online;

public:
    User(const std::string& username);
    
    std::string getUsername() const;
    bool isOnline() const;
    
    void setOnline(bool status);
};

#endif // USER_H
