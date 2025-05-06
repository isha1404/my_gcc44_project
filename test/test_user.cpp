#include <iostream>
#include <cassert>
#include "../include/user.h"

void test_user_creation() {
    std::cout << "Testing user creation... ";
    
    User user("testuser");
    
    assert(user.getUsername() == "testuser");
    assert(user.isOnline() == false); // Default is offline
    
    std::cout << "PASSED" << std::endl;
}

void test_user_status() {
    std::cout << "Testing user status... ";
    
    User user("testuser");
    assert(user.isOnline() == false); // Default is offline
    
    user.setOnline(true);
    assert(user.isOnline() == true);
    
    user.setOnline(false);
    assert(user.isOnline() == false);
    
    std::cout << "PASSED" << std::endl;
}

int main() {
    std::cout << "=== User Tests ===" << std::endl;
    
    test_user_creation();
    test_user_status();
    
    std::cout << "All user tests passed!" << std::endl;
    return 0;
}
