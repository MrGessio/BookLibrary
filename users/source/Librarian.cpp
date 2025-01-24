#include <vector>
#include <algorithm>  //find_if
#include <string>
#include <fstream>
#include <iostream>
#include "../include/Librarian.h"

extern std::fstream libraryDoc;

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
    std::ifstream inputFile("users.txt"); //open file

    if(!inputFile){
        std::cout << "Error, could not open the file" << std::endl;
        return;
    }

    UserInfo user;
    while (inputFile >> user.username >> user.password >> user.firstname >> user.lastname){
        users.push_back(user);
    }

    inputFile.close();
}

void Librarian:: SaveUsers(){
    std::ofstream outputFile("users.txt");

    if(!outputFile){
        std::cout << "Error. Could not open the file.";
        return;
    }

    for(auto &user : users){
        outputFile << user.username << " " << user.password << " " << user.firstname << " " << user.lastname << std::endl;
    }
    outputFile.close();

}

void Librarian:: AddUser(const std::string &username, const std::string &password, const std::string &firstname, const std::string &lastname){
    
    LoadUsers();
    //check if the user already exists
    auto it = std::find_if(users.begin(), users.end(), [&username](const UserInfo &user){
        return user.username == username;
    });

    if (it != users.end()){
        std::cout << "Error user named: " << username << " is already taken." << std::endl;
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
        return users.username == username;
    });

    if (it != users.end()){
        users.erase(it); //delete user from the list
        SaveUsers();

        std::cout << "User: " << username << " added correctly." << std::endl;
    } else std::cout << "Error. User: " << username << " not found." << std::endl;

}

void Librarian::DisplayUsers(){
    if(users.empty()) std::cout << "No users found." << std::endl;

    std::cout << "List of users: " << std::endl;
    for(auto &user : users){
        std::cout << "- username: " << user.username << ", name" << user.firstname
                  << " " << user.lastname << std::endl;
    }
}
    