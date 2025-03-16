#include "Reader.h"
#include <ctime>
#include <sstream>


void Reader::BorrowBook(const std::string &bookTitle, Logger &log){

    std::string trim(const std::string &str);
    std::ifstream libraryFile("library.txt");
    std::ofstream tempFile("libraryTemp.txt");

    std::string line, title, author, year, status;
    bool bookFound = false;
    bool alreadyBorrowed = false;

    while (std::getline(libraryFile, line)){
        std::istringstream lineStream(line);

        std::getline(lineStream, title, ',');
        std::getline(lineStream, author, ',');
        std::getline(lineStream, year, ',');
        std::getline(lineStream, status, ',');

        title = trim(title);
        status = trim(status);

        if(title == bookTitle){
            bookFound = true;
            if(status == "not available"){
                alreadyBorrowed = true;
            } else status = "not available";
        }

    tempFile << title << ", " << author << ", " << year << ", " << status << std::endl;

    }

    libraryFile.close();
    tempFile.close();

    if (!bookFound){
        std::cout << "Error: Book \"" << bookTitle << "\" not found in the library." << std::endl;
        return;
    }
    if(alreadyBorrowed){
        std::cout << "You can not borrow " << bookTitle << " because it is not available." << std::endl;
    }

    std::remove("library.txt");
    std::rename("libraryTemp.txt", "library.txt");

    if(bookFound && !alreadyBorrowed){
        std::ofstream file("borrowedBooks.txt", std::ios::app);
        if (file.is_open()){
            std::time_t now = std::time(nullptr);
            std::tm nowTm = *std::localtime(&now);
            char dateBuffer[11];
            std::strftime(dateBuffer, sizeof(dateBuffer), "%Y-%m-%d", &nowTm);

            file << log.getUsername() << ", " << bookTitle << "," << dateBuffer << "\n";
            std::cout << "Book \"" << bookTitle << "\" borrowed." << std::endl;
        } else std::cout << "Error. Could not open the borrowedBooks.txt" << std::endl;
    }
}
std::string trim(const std::string &str){
    const char* whitespace = " \t\n\r\f\v";
    size_t start = str.find_first_not_of(whitespace);
    size_t end = str.find_last_not_of(whitespace);

    if (start == std::string::npos || end == std::string::npos){
        return "";
    }

    return str.substr(start, end - start + 1);
}

void Reader::SearchBook() {
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

void Reader::ShowBooks() {
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
void Reader::ReturnBook(Logger &log) {
    std::string returnTitle;
    std::cout << "Enter the title of the book you want to return: " << std::endl;
    std::cin.ignore();
    std::getline(std::cin, returnTitle);
    std::ifstream borrowedFile("borrowedBooks.txt");
    std::ifstream libraryFile("library.txt");
    std::ofstream tempBorrowedFile("borrowedBooksTemp.txt");
    std::ofstream tempLibraryFile("libraryTemp.txt");

    if (!borrowedFile && !libraryFile) {
        std::cout << "Error. Could not open borrowedBooks.txt or library.txt" << std::endl;
        return;
    }

    if(!tempBorrowedFile && !tempLibraryFile){
        std::cout << "Error. Could not open borrowedBooksTemp.txt or libraryTemp.txt" << std::endl;
        return;
    }

    std::string line, username, title, status, borrowDate, year, author;
    bool bookToReturnFound = false;

    while (std::getline(borrowedFile, line)){
        std::istringstream lineStream(line);
        std::getline(lineStream >> std::ws, username, ',');
        std::getline(lineStream >> std::ws, title, ',');
        std::getline(lineStream >> std::ws, status, ',');
        lineStream >> borrowDate;

        if(title == returnTitle && username == log.getUsername()){
            bookToReturnFound = true;
            status = "available";
        } else  tempBorrowedFile << line << std::endl;
    }
        if(!bookToReturnFound){
            std::cout << "This book is not in your borrowed books list." << std::endl;
        }

    borrowedFile.close();
    tempBorrowedFile.close();

    bool bookUpdated = false;
    while(std::getline(libraryFile, line)){
        std::istringstream lineStream(line);
        std::getline(lineStream >> std::ws, title, ',' );
        std::getline(lineStream >> std::ws, author, ',');
        std::getline(lineStream >> std::ws, year, ',');
        std::getline(lineStream >> std::ws, status, ',');

        if(title == returnTitle){
            bookUpdated = true;
            status = "available";
        }

        tempLibraryFile << title << ", " << author << ", " << year << "," << status << std::endl;
    }
    libraryFile.close();
    tempLibraryFile.close();

    if(bookToReturnFound){
        std::cout << "The book " << returnTitle << " has been returned successfully." << std::endl;
        std::remove("borrowedBooks.txt");
        std::rename("borrowedBooksTemp.txt", "borrowedBooks.txt");
        if(bookUpdated){
            std::remove("library.txt");
            std::rename("libraryTemp.txt", "library.txt");
        }
    }
}

