#include "../include/Logger.h"
#include <iostream>

void Logger::logIn(){
    std::cout << "Write your username: ";
    std::cin >> username;
    std::cout << "Write your password: ";
    std::cin >> password;
}

std::string Logger::getUsername() {
    return username;
}

std::string Logger::getPassword() {
    return password;
}
