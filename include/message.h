#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <ctime>

class Message {
private:
    std::string sender;
    std::string receiver;
    std::string content;
    time_t timestamp;

public:
    Message(const std::string& sender, const std::string& receiver, const std::string& content);
    
    std::string getSender() const;
    std::string getReceiver() const;
    std::string getContent() const;
    time_t getTimestamp() const;
    void setTimestamp(time_t timestamp);
    
    std::string toString() const;
    bool isVisibleTo(const std::string& username) const;
};

#endif // MESSAGE_H
