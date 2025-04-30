#include "Admin.h"
#include <limits>
#include <sstream>

extern std::fstream libraryDoc;

 int Admin::GetValidYear(){

        int year;
        while(true){
            std::cout << "Write the year: ";
            if (std::cin >> year){
                if (year >0) return year;
                else std::cout << "Incorrect year" << std::endl;
            }
            else{
                std::cout << "This is incorrect, type a number" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

    }

void Admin::AddBook(const std::string &title, const std::string &author, int year, const std::string &status, const std::string &libraryPath) {
    Book newBook(title, author, year, status);

    std::ofstream libraryDoc(libraryPath, std::ios::app);
    if (libraryDoc.is_open()) {
        libraryDoc << newBook.DataToSave() << std::endl;
        libraryDoc.close();
        std::cout << "Book added: " << title << ", " << author << ", " << year << status << std::endl;
    } else {
        std::cout << "Error, couldn't open the file." << std::endl;
    }
}
void Admin::DeleteBook(const std::string& bookToDelete, const std::string &libraryPath, const std::string &libraryPathTemp) {

    libraryDoc.open(libraryPath, std::ios::in);
    std::fstream tempFile(libraryPathTemp, std::ios::out);

    if (!libraryDoc.is_open() || !tempFile.is_open()) {
        std::cout << "Error opening files." << std::endl;
        return;
    }

    std::string line;
    bool foundToDelete = false;
    while (std::getline(libraryDoc, line)) {
        if (line.find(bookToDelete) != std::string::npos) {
            foundToDelete = true;
            std::cout << "Deleting book: " << line << std::endl;
            continue;
        }
        tempFile << line << std::endl;
    }
    libraryDoc.close();
    tempFile.close();

    if (foundToDelete) {
        if (std::remove(libraryPath.c_str()) != 0) {
            std::cout << "Error deleting the original file." << std::endl;
        } else if (std::rename(libraryPathTemp.c_str(), libraryPath.c_str())!= 0) {
            std::cout << "Error renaming the temporary file." << std::endl;
        } else {
            std::cout << "Book deleted." << std::endl;
        }
    } else {
        std::cout << "Book not found." << std::endl;
        std::remove(libraryPathTemp.c_str());
    }
}

void Admin:: UpdateBook(const std::string& bookToBeChanged, const std::string& libraryPath, const std::string& libraryPathTemp) {
    libraryDoc.open(libraryPath, std::ios::in);
    std::fstream tempFile(libraryPathTemp, std::ios::out);

    if(!libraryDoc.is_open() || !tempFile.is_open()){
       std::cout << "Error opening files." << std::endl;
       return;
    }
       std::string line, title, author;
       int year;

       bool foundToChange = false;
       while (std::getline(libraryDoc, line)){
           std::istringstream lineStream(line);
           std::getline(lineStream, title, ',');
           std::getline(lineStream, author, ',');
           lineStream >> year;

           if (title == bookToBeChanged){
               //AddBook()
               foundToChange = true;
               std::cout << "You want to change this book: " << line << std::endl;
               continue;
           }
           tempFile << line << std::endl;
       }
       libraryDoc.close();
       tempFile.close();

       if (std::remove(libraryPath.c_str()) == 0 && std::rename(libraryPathTemp.c_str(), libraryPath.c_str()) == 0){
            AddBook(title, author, year, ", available", libraryPath);
       }

    if(!foundToChange) std::cout << "Book not found." << std::endl;
}

