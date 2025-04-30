
#include <cstdio>  // for std::remove and std::rename
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "include/Book.h"
#include "include/Logger.h"
#include "User.h"
#include "Reader.h"
#include "Admin.h"
#include "Librarian.h"

    int main() {

        bool mainScreen = true;
        bool adminScreen = true;
        bool librarianScreen = true;
        bool userScreen = true;
        Logger log;
        Admin admin;
        Librarian librarian;
        User user;
        Reader reader;

        int chosenNumber;
        char adminChoice;
        int librarianChoice;
        
        std::string titleToSearch;
        
        while(mainScreen){
            std::cout << "\n            Welcome to the Library" << std::endl;
            std::cout << "Press a number to choose from the option below:" << std::endl;
            std::cout << "[1] To view all books" << std::endl;
            std::cout << "[2] To search a book" << std::endl;
            std::cout << "[3] To log in" << std::endl;
            std::cout << "[9] To exit" << std::endl;
            std::cout << "Press...";
            std::cin >> chosenNumber;
            std::cout << "\n";

            switch (chosenNumber) {
            case 1:
                try {
                    reader.ShowBooks(); 
                } catch (const std::runtime_error& e){
                    std::cerr << "Error: " << e.what() << std::endl;
                }
                std::cout << "\n";
                break;

            case 2:
                std::cout << "Enter the title you are looking for: ";
                std::cin.ignore();
                std::getline(std::cin, titleToSearch);
                try {
                    reader.SearchBook(titleToSearch);
                } catch (const std::runtime_error& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
                std::cout << "\n";
                break;

            case 3:{
                std::string username, password;

                std::cout << "Write your username: ";
                std::cin.ignore();
                std::getline(std::cin, username);

                std::cout << "Write your password: ";
                std::getline(std::cin, password);
                
                log.LogIn(username, password);
                
                
                if (log.IsValidUser("users.txt")){
                    std::cout << "\nHello, " << log.getUsername() << "!" << std::endl;

                    if(log.getUsername() == "admin"){
                        adminScreen = true;
                        while(adminScreen){
                            std::cout << "you can (a)dd and (d)elete book, show (b)ooks or e(x)it" << std::endl;
                            std::cout << "Press...";
                            std::cin >> adminChoice;
                            std::cout << "\n";

                            switch (adminChoice) {
                            case 'a':{
                                std::string title, author, status, libraryPath;
                                std::cout << "Write the title: ";
                                std::cin.ignore();
                                std::getline(std::cin, title);
                                std::cout << "Write the author: ";
                                std::getline(std::cin, author);
                                int year = admin.GetValidYear();
                                admin.AddBook(title, author, year, status, libraryPath);
                                break;
                            }
                            case 'd':{
                                std::string bookToDelete, libraryPath, libraryPathTemp;
                                std::cout << "Enter the title of the book you want to delete: ";
                                std::cin >> bookToDelete;
                                admin.DeleteBook(bookToDelete, libraryPath, libraryPathTemp);}
                                break;

                            case 'b':
                                try {
                                    reader.ShowBooks();
                                } catch (const std::runtime_error& e) {
                                    std::cerr << "Error: " << e.what() << std::endl;
                                } 
                                std::cout << "\n";
                                break;

                            case 'x':
                                adminScreen = false;
                                break;
                            }
                        }
                    }
                

                    else if (log.getUsername() == "librarian") {
                        librarianScreen = true;
                        while(librarianScreen){
                            std::cout << "\nWhat would you like to do?" << std::endl;
                            std::cout << "1. Add a book. 2. Delete a book. 3. Add a user. 4. Delete a user. 5. Display users. "
                                    <<  "6. List of borrowed books. 7.List of overdue books. " 
                                    <<  "8. Update data about a book. " << "9. Exit. " << std::endl;
                            std::cout << "Press...";
                            std::cin >> librarianChoice;
                            std::cout << "\n";


                            std::string username, password, firstname, lastname, borrowedPath, UsersPath;
                            switch (librarianChoice){
                                case 1:{
                                    std::string title, author, status, libraryPath;
                                    std::cout << "Write the title: ";
                                    std::cin.ignore();
                                    std::getline(std::cin, title);
                                    std::cout << "Write the author: ";
                                    std::getline(std::cin, author);
                                    int year = admin.GetValidYear();
                                    //status = ", available";
                                    admin.AddBook(title, author, year, status, libraryPath);
                                    break;
                                }
                                case 2:{
                                    std::string bookToDelete, libraryPath, libraryPathTemp;
                                    std::cout << "Enter the title of the book you want to delete: ";
                                    std::cin >> bookToDelete;
                                    admin.DeleteBook(bookToDelete,libraryPath, libraryPathTemp);}
                                    break;

                                case 3:                        
                                    std::cout << "Enter username: " << std::endl;
                                    std::cin >> username;
            
                                    while (user.IsUsernameTaken(username, UsersPath)){
                                        std::cout << "Error. Username \"" << username << "\" is already taken." << std::endl;
                                        std::cout << "Enter username: " << std::endl;
                                        std::cin >> username;
                                    }                        

                                    std::cout << "Enter password: " << std::endl;
                                    std::cin >> password;
                                    std::cout << "Enter first name: " << std::endl;
                                    std::cin >> firstname;
                                    std::cout << "Enter last name: " << std::endl;
                                    std::cin >> lastname;
                                    user.AddUser(username, password, firstname, lastname, UsersPath);
                                    break;

                                case 4:
                                    std::cout << "Enter username you want to delete: " << std::endl;
                                    std::cin >> username;
                                    user.DeleteUser(username, UsersPath);
                                    break;

                                case 5:
                                    user.DisplayUsers(UsersPath);
                                    std::cout << "\n";
                                    break;

                                case 6:
                                    librarian.ListOfBorrowedBooks(borrowedPath);
                                    break;
                            
                                case 7:
                                    librarian.ListOfOverdueBooks(borrowedPath);
                                    break;
                                                  
                                case 8:{
                                    std::string bookToBeChanged, libraryPath, libraryPathTemp;
                                    std::cout << "Enter the title of a book to be changed: " << std::endl;
                                    std::cin.ignore();
                                    std::getline(std::cin, bookToBeChanged);
                                    admin.UpdateBook(bookToBeChanged, libraryPath, libraryPathTemp);
                                    break;
                                }
                                case 9:
                                    librarianScreen = false;
                                    break;
                        
                                default:
                                    std::cout << "Invalid input. Please enter a number between 1 and 9." << std::endl;
                                    break;
                            }           
                        } 
                    }  
                    else if(log.getUsername()!="admin" && log.getUsername()!="librarian") {
                        userScreen = true;
                        int userChoice;
                        while(userScreen){ 
                            mainScreen = false;
                            std::cout << "Press a number to choose the option:" << std::endl;
                            std::cout << "[1] To borrow a book." << std::endl;
                            std::cout << "[2] To view borrowed books." << std::endl;
                            std::cout << "[3] To search a book." << std::endl;
                            std::cout << "[4] To show books." << std::endl;
                            std::cout << "[5] To return a book." << std::endl;
                            std::cout << "[9] To exit." << std::endl;
                            std::cout << "Press...";
                            std::cin >> userChoice;
                            std::cout << "\n";

                            switch(userChoice){
                                case 1:{
                                    std::string bookTitle;
                                    std::cout << "Enter the title of the book you want to borrow" << std::endl;
                                    std::cin.ignore();
                                    std::getline(std::cin, bookTitle);
                                    try {
                                        reader.BorrowBook(bookTitle, log);
                                    } catch (const std::runtime_error& e) {
                                        std::cerr << "Error: " << e.what() << std::endl;
                                    }
                                    std::cout << "\n";
                                    break;
                                }

                                case 2:
                                {
                                    std::ifstream file("borrowedBooks.txt");
                                    std::cout << "List of borrowed books by user " << log.getUsername() << ":" << std::endl;
                                    
                                    if (file.is_open()){
                                        std::string line, username, title, borrowDate;

                                        while(std::getline(file, line)){
                                            std::istringstream iss(line);
                                            std::getline(iss >> std::ws, username, ',');
                                            std::getline(iss >> std::ws, title, ',');
                                            iss >> borrowDate;

                                            if (username == log.getUsername()){
                                                std::cout << "- " << title << " (borrowed on: " << borrowDate << ")" << std::endl;
                                            }
                                        }
                                    
                                        file.close();
                                    std::cout << "\n";
                                    } 
                                    else{
                                        std::cout << "Error. Could not open borrowedBooks.txt" << std::endl;
                                    }
                            
                                        break;
                                } 

                                case 3:
                                    std::cout << "Enter the title you are looking for: ";
                                    std::cin.ignore();
                                    std::getline(std::cin, titleToSearch);
                                    try {
                                        reader.SearchBook(titleToSearch);
                                    } catch (const std::runtime_error& e) {
                                        std::cerr << "Error: " << e.what() << std::endl;
                                    }
                                    std::cout << "\n";
                                    break;

                                case 4:
                                    try {
                                        reader.ShowBooks(); 
                                    } catch (const std::runtime_error& e) {
                                        std::cerr << "Error: " << e.what() << std::endl;
                                    }
                                    std::cout << "\n";
                                    break;

                                case 5:{
                                    std::string returnTitle;
                                    std::cout << "Enter the title of the book you want to return: " << std::endl;
                                    std::cin.ignore();
                                    std::getline(std::cin, returnTitle);
                                    try {
                                        reader.ReturnBook(returnTitle, log);
                                    } catch (const std::runtime_error& e) {
                                        std::cerr << "Error: " << e.what() << std::endl;
                                    }
                                    break;}
                        
                                case 9:
                                    userScreen = false;
                                    mainScreen = true;
                                    break;
                                
                                default:
                                std:: cout << "Invalid option, choose again" << std::endl;
                                break;

                            }
                        } 
                    } 
                    else std::cout << "user not found" << std::endl;
                    break;
                }   
            }
            case 9:
                mainScreen = false;
                break;
            default:
                std::cout << "Invalid option, please choose again." << std::endl;
                break;
            }       
        }
        return 0;
    }
    