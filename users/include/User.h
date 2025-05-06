#pragma once
#include <string>
#include <vector>

struct UserInfo {
    std::string username;
    std::string password;
    std::string firstname;
    std::string lastname;
};

class User{
    public:
        void AddUser(const std::string &username, const std::string &password, const std::string &firstname, const std::string &lastname, const std::string &UsersPath = std::string("users.txt"));
        bool IsUsernameTaken(const std::string &username, const std::string &UsersPath = std::string("users.txt"));
        void DisplayUsers(const std::string &UsersPath = std::string("users.txt"));
        void DeleteUser(const std::string &username, const std::string &usersPath = std::string("users.txt"));
        void LoadUsers(const std::string &UsersPath = std::string("users.txt")); //load the users from txt to vector
        void SaveUsers(const std::string &UsersPath = std::string("users.txt")); //save from vector to txt
    
    private:
        std::vector<UserInfo> m_users; //list of the users
};
