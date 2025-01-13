#include "../include/User.h"

extern std::fstream libraryDoc;

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
    libraryDoc.open("library.txt", std::ios::in);
    if (libraryDoc.is_open()) {
        std::string line;
        while (std::getline(libraryDoc, line)) {
            std::cout << line << std::endl;
        }
        libraryDoc.close();
    } else {
        std::cout << "Error, couldn't open the file." << std::endl;
    }
}