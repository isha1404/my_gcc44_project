#include "../include/message.h"
#include <sstream>
#include <ctime>

Message::Message(const std::string& sender, const std::string& content) 
    : sender(sender), content(content) {
    timestamp = time(NULL);
}

std::string Message::getSender() const {
    return sender;
}

std::string Message::getContent() const {
    return content;
}

time_t Message::getTimestamp() const {
    return timestamp;
}

void Message::setTimestamp(time_t timestamp) {
    this->timestamp = timestamp;
}

std::string Message::toString() const {
    std::stringstream ss;
    struct tm* timeinfo = localtime(&timestamp);
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
    
    ss << "[" << buffer << "] " << sender << ": " << content;
    return ss.str();
}
