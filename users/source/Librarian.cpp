#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include "Librarian.h"


void Librarian::ListOfBorrowedBooks(const std::string &borrowedPath){
    std::ifstream file (borrowedPath);
    std::cout << "\nList of borrowed books: " << std::endl;

    if(file.is_open()){
        std::string line, username, title, borrowDate;
        while(std::getline(file, line)){
            std::istringstream iss(line);
            std::getline(iss >> std::ws, username, ',');
            std::getline(iss >> std::ws, title, ',');
            iss >> borrowDate;
            std::cout << "- " << title << " (" << username << ")" << ", borrowed on: " << borrowDate << "\n";
        }
        file.close();
    std::cout << "\n";
    }else std::cout << "Error, could not open the borrowedBooks.txt" << std::endl;


}

void Librarian::ListOfOverdueBooks(const std::string &borrowedPath){
    std::ifstream file (borrowedPath);
    std::cout << "\nList of overdued books: " << std::endl;

    if(!file.is_open()){
        std::cout << "Error. Could not open borrowedBooks.txt" << std::endl;
        return;
    }

    std::string line, username, title, dateStr;
    const int overdueDays = 14;
    bool foundOverdueDays = false;

    std::time_t now = std::time(nullptr); //get current time
    std::tm nowTm = *std::localtime(&now);

    while (std::getline(file, line)){
        std::istringstream iss(line);
        std::getline(iss >> std::ws, username, ',');
        std::getline(iss >> std::ws, title, ',');
        iss >> dateStr;

        std::tm borrowDate = {};
        std::istringstream dateStream(dateStr);
        dateStream >> std::get_time(&borrowDate, "%Y-%m-%d");
        if (!dateStream.fail()){
            std::time_t borrowedTime = std::mktime(&borrowDate);
            //differance between the date of borrowing and current date
            double diffDays = std::difftime(now, borrowedTime) / (60*60*24);

            if (diffDays > overdueDays){
                std::cout << "- " << title << " (borrowed by: " << username << " on " << dateStr << ")" << std::endl;
                foundOverdueDays = true;
            }
        }
    }
    if(!foundOverdueDays){
        std::cout << "No overdue books found." << std::endl;
    }
    file.close();

}
