
#include <cstdio>  // for std::remove and std::rename
#include <iostream>
#include <fstream>
#include <string>
#include "include/Book.h"
#include "include/Logger.h"
#include "User.h"
#include "Admin.h"
#include "Librarian.h"

    int main() {

        
        Logger log;
        Admin admin;
        Librarian librarian;
        User user;

        int chosenNumber;
        char adminChoice;
        int librarianChoice;
        std::cout << "Welcome to the Library" << std::endl;
        std::cout << "Press a number to choose from the option below:" << std::endl;
        std::cout << "[1] To view all books" << std::endl;
        std::cout << "[2] To search a book" << std::endl;
        std::cout << "[3] To log in" << std::endl;
        std::cout << "Press...";
        std::cin >> chosenNumber;

        switch (chosenNumber) {
        case 1:
            user.showBooks(); 
            break;

        case 2:
            user.searchBook();
            break;

        case 3:
            log.logIn(); 
            //if username and password is admin and admin then admin stuff
            
            //xxADD here who log ins check Librarian,cpp
            if (log.getUsername() == "admin" && log.getPassword() == "admin") {
                std::cout << "you can (a)dd or (d)elete books" << std::endl;
                std::cout << "Press...";
                std::cin >> adminChoice;

                switch (adminChoice) {
                case 'a':
                    admin.addBook();
                    break;

                case 'd':
                    admin.deleteBook();
                    break;
                }
            }
            else if ((log.getUsername() == "librarian" && log.getPassword() == "librarian")) {
                std::cout << "What would you like to do?" << std::endl;
                std::cout << "1. Add a book, 2. Delete a book, 3. Add a user, 4. Delete a user, 5. Display users,"
                          <<  "6. List of borrowed books, 7.List of overdue books," 
                          <<  "8. Update data about a book: " << std::endl;
                std::cout << "Press...";
                std::cin >> librarianChoice;


                std::string username, password, firstname, lastname;
                switch (librarianChoice){
                    case 1:
                        librarian.addBook();
                        break;
                    case 2:
                        librarian.deleteBook();
                        break;
                    case 3:
                        
                        std::cout << "Enter username: " << std::endl;
                        std::cin >> username;
        
                        while (librarian.IsUsernameTaken(username)){
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
                         librarian.AddUser(username, password, firstname, lastname);
                        break;
                    case 4:
                        std::cout << "Enter username you want to delete: " << std::endl;
                        std::cin >> username;
                        librarian.DeleteUser(username);
                        break;
                    case 5:
                         librarian.DisplayUsers();
                        break;
                    case 6:
                      //  librarian.ListOfBorrowedBooks();
                        break;
                    case 7:
                      //  librarian.ListOfOverdueBooks();
                        break;
                    case 8:
                        librarian.UpdateBook();
                        break;
                    case 9:
                       // librarian.AllowBookBorrowing();
                        break;
                
                    default:
                    std::cout << "Invalid input. Please enter a number between 1 and 9." << std::endl;
                 }           
                 return 0;
            }
            else std::cout << "user not found" << std::endl;
            break;

        default:
            std::cout << "Invalid option, please choose again." << std::endl;
            break;
        }

        //
        return 0;
    }
