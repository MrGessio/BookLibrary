#include "User.h"
#include <vector>
#include <algorithm>  //find_if
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>

extern std::fstream usersDoc;

void User:: LoadUsers(const std::string &usersPath){
    std::cout << "TESTING BUGS " << usersPath << std::endl;
   m_users.clear(); //clears vector before loading data
   std::fstream usersDoc(usersPath, std::ios::in); 
   
    if(!usersDoc){
        std::cout << "Error, could not open the file" << std::endl;
        throw std::runtime_error("Error: couldn't open the file");
        return;
    }

    UserInfo user;
    while (usersDoc >> user.username >> user.password >> user.firstname >> user.lastname){
        m_users.push_back(user);
    }

    usersDoc.close();
}

void User:: SaveUsers(const std::string &usersPath){
    std::ofstream usersDoc(usersPath, std::ios::out);

    if(!usersDoc){
        std::cout << "Error. Could not open the file." << std::endl;
        throw std::runtime_error("Error: couldn't open the file");
        return;
    }

    for(const auto& user : m_users){
        usersDoc << user.username << " " << user.password << " " << user.firstname << " " << user.lastname << std::endl;
    }
    usersDoc.close();

}


bool User:: IsUsernameTaken(const std::string &username, const std::string &usersPath){
    LoadUsers(usersPath);
    auto it = std::find_if(m_users.begin(), m_users.end(), [&username](const UserInfo &user) {
        return user.username == username;
    });
    return it != m_users.end(); 
}

void User:: AddUser(const std::string &username, const std::string &password, const std::string &firstname, const std::string &lastname, const std::string &usersPath){

    if (IsUsernameTaken(username, usersPath)){
        std::cout << "Error. Username: " << username << " is already taken." << std::endl;
        throw std::runtime_error("Error: Username is already taken");
        return;
    }

    //add user to the list
    UserInfo newUser = {username, password, firstname, lastname};
    m_users.push_back(newUser);

    SaveUsers(usersPath); //save the edited list

    std::cout << "User named: " << username << " added correctly" << std::endl;
    
}

void User::DeleteUser(const std::string &username, const std::string &usersPath){

    LoadUsers(usersPath);
    auto it = std::find_if(m_users.begin(), m_users.end(), [&username](const UserInfo &user0){
        return user0.username == username;
    });

    if (it != m_users.end()){
        m_users.erase(it); //delete user from the list
        SaveUsers(usersPath);

        std::cout << "User: " << username << " deleted correctly." << std::endl;
    }   else {
            std::cout << "Error. User: " << username << " not found." << std::endl;
            throw std::runtime_error("Error: user not found");}

}

void User::DisplayUsers(const std::string &usersPath){
    LoadUsers(usersPath);
    std::cout << "Number of users: " << m_users.size() << std::endl;
    if(m_users.empty()) {
        std::cout << "No users found." << std::endl; 
        return;
        }

    std::cout << "List of users: " << std::endl;
    for(const auto& user : m_users){
        std::cout << "- username: " << user.username << ", name: " << user.firstname
                  << ", surname: " << user.lastname << std::endl;
    }
}
