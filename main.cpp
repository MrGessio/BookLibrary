
#include <cstdio>  // for std::remove and std::rename
#include <iostream>
#include <fstream>
#include <string>
#include "Book.h"
#include "Logger.h"
#include "User.h"
#include "Admin.h"

Logger 



class User  //user as someoe who uses the library
{
    void searchBook() {
    }; //search by just the title

    void showBooks() {
        libraryDoc.open("library.txt", std::ios::in); //read
        if (libraryDoc.is_open()) {
            std::string line;
            while (std::getline(libraryDoc, line)) {
                std::cout << line << std::endl;
            }
            libraryDoc.close();
        }
    };
};

//who keeps the names. is it users or reades. Does admin needs to have a name? should log in somehow
class Reader //reader as someone who has an account excluding admin
{
    //name, surname
    //functions borrow, return, inherits logIn

    void borrowBook() {

    };
    void returnBook() {

    };
};

    class Admin : public User {
    public:
        //function: addBooks, deleteBooks
        //inhertis login from user?


        void addBook() {
            std::string title, author;
            int year;

            std::cout << "Write the title: " << std::endl;
            std::cin >> title;
            std::cout << "Write the author: " << std::endl;
            std::cin >> author;
            std::cout << "Write the year: " << std::endl;
            std::cin >> year;

            Book newBook(title, author, year);

            libraryDoc.open("library.txt", std::ios::app);
            if (libraryDoc.is_open()) {
                libraryDoc << newBook.dataToSave() << std::endl;
                libraryDoc.close();
                std::cout << "Book added: " << title << ", " << author << ", " << year << std::endl;
            }
        };
        void deleteBook() {
            std::string bookToDelete;
            std::cout << "Enter the title of a book you want to delete: ";
            std::cin >> bookToDelete;
            libraryDoc.open("library.txt", std::ios::in);
            //below is a temporary file for saving the books that wont be deleted
            std::fstream tempFile("libraryTemp.txt", std::ios::out);
            if (!tempFile.is_open()) {
                std::cout << "problem with opening the temporary file";
                libraryDoc.close();
            }

            std::string line;
            bool foundToDelete = false;
            while (std::getline(libraryDoc, line)) {
                if (line.find(bookToDelete) != std::string::npos) {
                    foundToDelete = true;
                    std::cout << "Deleting book: " << line << std::endl;
                    continue; //ignore this book while saving
                }
                //save all the books to the temporary file
                tempFile << line << std::endl;
            }
            libraryDoc.close();
            tempFile.close();

            if (foundToDelete) {
                //delete original file
                if (std::remove("library.txt") != 0) {
                    std::cout << "Error, couldnt delete the original file" << std::endl;
                }
                else {
                    std::cout << "File deleted successfully." << std::endl;  // Plik został usunięty
                }
            
            // change the temporary file name to original file
            if (std::rename("libraryTemp.txt", "library.txt") != 0) {
                std::cout << "error renaming the file's name" << std::endl;
                return;
            }
            std::cout << "Book deleted." << std::endl;
            }
            else {
                std::cout << "book not found" << std::endl;
            }
        };
    };

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
