#include "../include/User.h"

extern std::fstream libraryDoc;

void User::BorrowBook(const std::string &bookTitle, Logger &log){
    std::ofstream file("borrowedBooks.txt", std::ios::app);
    if (file.is_open()){
        file << log.getUsername() << " " << bookTitle << "\n";
        std::cout << "Book \"" << bookTitle << "\" borrowed." << std::endl;
    } else std::cout << "Error. Could not open the borrowedBooks.txt" << std::endl;
}

void User::searchBook() {
    std::string titleToSearch;
    bool found = false;
    std::cout << "Enter the title you are looking for: ";
    std::cin.ignore();
    std::getline(std::cin, titleToSearch);

    libraryDoc.open("library.txt", std::ios::in);
    if (libraryDoc.is_open()) {
        std::string line;
        while (std::getline(libraryDoc, line)) {
            if (line.find(titleToSearch) != std::string::npos) {
                std::cout << "Book found: " << line << std::endl;
                found = true;
            }
        }
        libraryDoc.close();
    } else {
        std::cout << "Error, couldn't open the file." << std::endl;
    }

    if (!found) {
        std::cout << "Book not found." << std::endl;
    }
}

void User::showBooks() {
    std::cout << "List of books in the library: " << std::endl;
    libraryDoc.open("library.txt", std::ios::in);
    if (libraryDoc.is_open()) {
        std::string line;
        while (std::getline(libraryDoc, line)) {
            std::cout << "- " << line << std::endl;
        }
        libraryDoc.close();
    } else {
        std::cout << "Error, couldn't open the file." << std::endl;
    }
}