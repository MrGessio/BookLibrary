#include "../include/Logger.h"
#include <iostream>
#include <sstream>
#include <fstream>

void Logger::LogIn(const std::string &u, const std::string &p){
    username = u;
    password = p;
}

std::string Logger::getUsername() {
    return username;
}

std::string Logger::getPassword() {
    return password;
}

bool Logger::IsValidUser(const std::string& filename){
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cerr << "Error: Could not open file " << filename << std::endl;
        loggedInUser = "";
        return false;

    }

    std::string line;
    while(std::getline(file, line)){ //reads line from the file and saves into 'line'
        std::stringstream stst(line);
        std::string fileUsername, filePassword; //variables read from the file

        std::getline(stst, fileUsername, ' ');
        std::getline(stst, filePassword, ' ');
        if (username == fileUsername && password == filePassword){
            loggedInUser = username;
            return true; // user found
        }
    }
    file.close();
    loggedInUser = "";
    return false; //user not found
}
