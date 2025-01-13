
#include <cstdio>  // for std::remove and std::rename
#include <iostream>
#include <fstream>
#include <string>
#include "include/Book.h"
#include "include/Logger.h"
#include "User.h"
#include "Admin.h"

    int main() {

        
        Logger log;
        Admin admin;
        User user;

        int chosenNumber;
        char adminChoice;
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
            else if ((log.getUsername() == "user1" && log.getPassword() == "user1")) {

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
