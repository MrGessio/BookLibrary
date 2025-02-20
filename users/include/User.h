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
        void AddUser(const std::string &username, const std::string &password, const std::string &firstname, const std::string &lastname);
        bool IsUsernameTaken(const std::string &username);
        void DisplayUsers();
        void DeleteUser(const std::string &username);
        void LoadUsers(); //load the users from txt to vector
        void SaveUsers(); //save from vector to txt
    
    private:
        std::vector<UserInfo> users; //list of the users
};
