#include <vector>
#include <algorithm>  //find_if
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
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
        std::string line, title, author, year;
        bool foundToChange = false;
        while (std::getline(libraryDoc, line)){
            std::istringstream lineStream(line);
            std::getline(lineStream, title, ',');
            std::getline(lineStream, author, ','); 
            lineStream >> year;
            
            if (title == bookToBeChanged){
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

void Librarian::ListOfBorrowedBooks(){
    std::ifstream file ("borrowedBooks.txt");
    std::cout << "\nList of borrowed books: " << std::endl;
    
    if(file.is_open()){
        std::string line, username, title, borrowDate;
        while(std::getline(file, line)){
            std::istringstream iss(line);
            std::getline(iss >> std::ws, username, ',');
            std::getline(iss >> std::ws, title, ',');
            iss >> borrowDate;
            std::cout << "- " << title << " (" << username << ")" << ", borrowed on: " << borrowDate << "\n";
        }
        file.close();
    std::cout << "\n";
    }else std::cout << "Error, could not open the borrowedBooks.txt" << std::endl;


}

void Librarian::ListOfOverdueBooks(){
    std::ifstream file ("borrowedBooks.txt");
    std::cout << "\nList of overdued books: " << std::endl;

    if(!file.is_open()){
        std::cout << "Error. Could not open borrowedBooks.txt" << std::endl;
        return;
    }

    std::string line, username, title, dateStr;
    const int overdueDays = 14;
    bool foundOverdueDays = false;

    std::time_t now = std::time(nullptr); //get current time
    std::tm nowTm = *std::localtime(&now);

    while (std::getline(file, line)){
        std::istringstream iss(line);
        std::getline(iss >> std::ws, username, ',');
        std::getline(iss >> std::ws, title, ',');
        iss >> dateStr;

        std::tm borrowDate = {};
        std::istringstream dateStream(dateStr);
        dateStream >> std::get_time(&borrowDate, "%Y-%m-%d");
        if (!dateStream.fail()){
            std::time_t borrowedTime = std::mktime(&borrowDate);
            //differance between the date of borrowing and current date
            double diffDays = std::difftime(now, borrowedTime) / (60*60*24);

            if (diffDays > overdueDays){
                std::cout << "- " << title << " (borrowed by: " << username << " on " << dateStr << ")" << std::endl;
                foundOverdueDays = true;
            }
        }
    }
    if(!foundOverdueDays){
        std::cout << "No overdue books found." << std::endl;
    }
    file.close();

}
    