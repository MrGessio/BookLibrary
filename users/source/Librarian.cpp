#include <vector>
#include <algorithm>  //find_if
#include <string>
#include <fstream>
#include <iostream>
#include "../include/Librarian.h"

extern std::fstream libraryDoc;
extern std::fstream usersDoc;

void Librarian:: UpdateBook() {
     std::string bookToBeChanged;
     std::cout << "Enter the title of a book to be changed: " << std::endl;
     std::cin.ignore();
     std::getline(std::cin, bookToBeChanged);

     libraryDoc.open("library.txt", std::ios::in);
     std::fstream tempFile("libraryTemp.txt", std::ios::out);

     if(!libraryDoc.is_open() || !tempFile.is_open()){
        std::cout << "Error opening files." << std::endl;
        return;
     }
        std::string line;
        bool foundToChange = false;
        while (std::getline(libraryDoc, line)){
            if (line.find(bookToBeChanged) != std::string::npos){
                //addBook()
                foundToChange = true;
                std::cout << "You want to change this book: " << line << std::endl;
                continue;
            }
            tempFile << line << std::endl;
        }
        libraryDoc.close();
        tempFile.close();

        if(foundToChange){
            if (std::remove("library.txt") == 0){
                if(std::rename("libraryTemp.txt", "library.txt") == 0){
                   addBook();
                }
            }
        }
      else std::cout << "Error, could not open the file." << std::endl;
     if(!foundToChange) std::cout << "Book not found." << std::endl;
}

void Librarian:: LoadUsers(){
   users.clear(); //clears vector before loading data
   std::fstream usersDoc("users.txt", std::ios::in); 

    if(!usersDoc){
        std::cout << "Error, could not open the file" << std::endl;
        return;
    }

    UserInfo user;
    while (usersDoc >> user.username >> user.password >> user.firstname >> user.lastname){
        users.push_back(user);
    }

    usersDoc.close();
}

void Librarian:: SaveUsers(){
    std::ofstream usersDoc("users.txt", std::ios::out);

    if(!usersDoc){
        std::cout << "Error. Could not open the file." << std::endl;
        return;
    }

    for(auto &user : users){
        usersDoc << user.username << " " << user.password << " " << user.firstname << " " << user.lastname << std::endl;
    }
    usersDoc.close();

}


bool Librarian:: IsUsernameTaken(const std::string &username){
    LoadUsers();
    auto it = std::find_if(users.begin(), users.end(), [&username](const UserInfo &user) {
        return user.username == username;
    });
    return it != users.end(); 
}

void Librarian:: AddUser(const std::string &username, const std::string &password, const std::string &firstname, const std::string &lastname){

    if (IsUsernameTaken(username)){
        std::cout << "Error. Username: " << username << " is already taken." << std::endl;
        return;
    }

    //add user to the list
    UserInfo newUser = {username, password, firstname, lastname};
    users.push_back(newUser);

    SaveUsers(); //save the edited list

    std::cout << "User named: " << username << " added correctly" << std::endl;
    
}

void Librarian::DeleteUser(const std::string &username){

    LoadUsers();
    auto it = std::find_if(users.begin(), users.end(), [&username](const UserInfo &user0){
        return user0.username == username;
    });

    if (it != users.end()){
        users.erase(it); //delete user from the list
        SaveUsers();

        std::cout << "User: " << username << " deleted correctly." << std::endl;
    } else std::cout << "Error. User: " << username << " not found." << std::endl;

}

void Librarian::DisplayUsers(){
    LoadUsers();
    std::cout << "Number of users: " << users.size() << std::endl;
    if(users.empty()) {
        std::cout << "No users found." << std::endl; 
        return;
        }

    std::cout << "List of users: " << std::endl;
    for(const auto &user : users){
        std::cout << "- username: " << user.username << ", name: " << user.firstname
                  << ", surname: " << user.lastname << std::endl;
    }
}
    