#include "Reader.h"
#include <ctime>
#include <sstream>
#include <stdexcept>


void Reader::BorrowBook(const std::string &bookTitle, Logger &log, const std::string &libraryPath , const std::string &borrowedBooks){

    std::string trim(const std::string &str);
    std::ifstream libraryFile(libraryPath);
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

       // std::cout << "title: " << title << ", bookTitle: " << bookTitle << std::endl;
        if(title == bookTitle){
            bookFound = true;
            std::cout << "current status: " << status << std::endl;
            if(status == "not available"){
                alreadyBorrowed = true;
            } else status = "not available";
        }

    tempFile << title << "," << author << "," << year << "," << status << std::endl;

    }

    libraryFile.close();
    tempFile.close();

    if (!bookFound){
        std::cout << "Error: Book \"" << bookTitle << "\" not found in the library." << std::endl;
        return;
    }

    std::cout << std::boolalpha << "is book already borrowed: " << alreadyBorrowed << std::endl;
    if (alreadyBorrowed) {
        throw std::runtime_error("Error: Book \"" + bookTitle + "\" is already borrowed and not available.");
    }

    std::remove(libraryPath.c_str());
    std::rename("libraryTemp.txt", libraryPath.c_str());

    if(bookFound && !alreadyBorrowed){
        std::ofstream file(borrowedBooks, std::ios::app);
        if (file.is_open()){
            std::time_t now = std::time(nullptr);
            std::tm nowTm = *std::localtime(&now);
            char dateBuffer[11];
            std::strftime(dateBuffer, sizeof(dateBuffer), "%Y-%m-%d", &nowTm);

            file << log.getUsername() << ", " << bookTitle << ", " << dateBuffer << "\n";
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

void Reader::SearchBook(const std::string &titleToSearch, const std::string &libraryPath) {

    bool found = false;
    std::ifstream libraryFile(libraryPath);
    if (libraryFile.is_open()) {
        std::string line;
        while (std::getline(libraryFile, line)) {
            std::istringstream lineStream(line);
            std::string title;
            std::getline(lineStream, title, ',');  // Pobranie samego tytułu
            if (trim(title) == trim(titleToSearch)) {
                std::cout << "Book found: " << line << std::endl;
                found = true;
                }
        }
        libraryFile.close();
    } else {
        std::cout << "Error, couldn't open the file." << std::endl;
        throw std::runtime_error("Error: couldn't open the file.");
    }

    if (!found) {
        std::cout << "Book not found." << std::endl;
        throw std::runtime_error("Error: couldn't find the book");
    }
}

void Reader::ShowBooks(const std::string &libraryPath) {
    std::cout << "List of books in the library: " << std::endl;
    std::ifstream libraryFile(libraryPath);
    if (libraryFile.is_open()) {
        std::string line;
        while (std::getline(libraryFile, line)) {
            std::cout << "- " << line << std::endl;
        }
        libraryFile.close();
    } else {
        std::cout << "Error, couldn't open the file." << std::endl;
        throw std::runtime_error("Error: couldn't open the file.");
    }
}
void Reader::ReturnBook(const std::string &bookTitle, Logger &log, const std::string &libraryPath , const std::string &borrowedBooks, const std::string &libraryPathTemp , const std::string &borrowedBooksTemp){
    std::ifstream borrowedFile(borrowedBooks);
    std::ifstream libraryFile(libraryPath);
    std::ofstream tempBorrowedFile(borrowedBooksTemp);
    std::ofstream tempLibraryFile(libraryPathTemp);

    if (!borrowedFile || !libraryFile) {
        std::cout << "Error. Could not open borrowedBooks.txt or library.txt" << std::endl;
        throw std::runtime_error("Could not open files");
        return;
    }

    if(!tempBorrowedFile || !tempLibraryFile){
        std::cout << "Error. Could not open borrowedBooksTemp.txt or libraryTemp.txt" << std::endl;
        throw std::runtime_error("Could not open temporary files");
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

        if(title == bookTitle && username == log.getUsername()){
            bookToReturnFound = true;
            status = "available";
        } else  tempBorrowedFile << line << std::endl;
    }
        if(!bookToReturnFound){
            std::cout << "This book is not in your borrowed books list." << std::endl;
            throw std::runtime_error("This book is not in your borrowed books list.");
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

        if(title == bookTitle){
            bookUpdated = true;
            status = "available";
        }

        tempLibraryFile << title << ", " << author << ", " << year << ", " << status << std::endl;
    }
    libraryFile.close();
    tempLibraryFile.close();

    if(bookToReturnFound){
        std::cout << "The book " << bookTitle << " has been returned successfully." << std::endl;
        std::remove(borrowedBooks.c_str());
        std::rename(borrowedBooksTemp.c_str(), borrowedBooks.c_str());
        if(bookUpdated){
            std::remove(libraryPath.c_str());
            std::rename(libraryPathTemp.c_str(), libraryPath.c_str());
        }
    }
}

