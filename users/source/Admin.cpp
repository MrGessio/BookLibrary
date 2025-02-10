#include "../users/include/Admin.h"
#include <limits>

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

void Admin::addBook() {
    std::string title, author, status;
    bool Availability;

    std::cout << "Write the title: ";
    std::cin.ignore();
    std::getline(std::cin, title);
    std::cout << "Write the author: ";
    std::getline(std::cin, author);
    int year = GetValidYear();
    status = ", available";

 Book newBook(title, author, year, status);

    libraryDoc.open("library.txt", std::ios::app);
    if (libraryDoc.is_open()) {
        libraryDoc << newBook.dataToSave() << std::endl;
        libraryDoc.close();
        std::cout << "Book added: " << title << ", " << author << ", " << year << status << std::endl;
    } else {
        std::cout << "Error, couldn't open the file." << std::endl;
    }
}
void Admin::deleteBook() {
    std::string bookToDelete;
    std::cout << "Enter the title of the book you want to delete: ";
    std::cin >> bookToDelete;

    libraryDoc.open("library.txt", std::ios::in);
    std::fstream tempFile("libraryTemp.txt", std::ios::out);

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
        if (std::remove("library.txt") != 0) {
            std::cout << "Error deleting the original file." << std::endl;
        } else if (std::rename("libraryTemp.txt", "library.txt") != 0) {
            std::cout << "Error renaming the temporary file." << std::endl;
        } else {
            std::cout << "Book deleted." << std::endl;
        }
    } else {
        std::cout << "Book not found." << std::endl;
    }
}
