#include "../include/user.h"

User::User(const std::string& username) 
    : username(username), online(false) {
}

std::string User::getUsername() const {
    return username;
}

bool User::isOnline() const {
    return online;
}

void User::setOnline(bool status) {
    online = status;
}
