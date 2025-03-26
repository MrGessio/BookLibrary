#include "../include/Book.h"
#include <iostream>
#include <fstream>

std::fstream libraryDoc;

Book::Book(std::string t, std::string a, int y, std::string s) {
        title = t;
        author = a;
        year = y;
        status = s;
    }

        void Book::AboutBook() {
        std::cout << "Title: " << title << " Author: " << author << ", year: " << year
                  << ", Status: " << status << std::endl;
        libraryDoc.open("library.txt", std::ios::in); //read
        if (libraryDoc.is_open()) {
       // show exact one
            libraryDoc.close();
        }
    }

    
    std::string Book::getTitle() {
        return title;
    }
    
    std::string Book::getAuthor() {
        return author;
    }
    int Book::getYear() {
        return year;
    }

    std::string Book::getStatus() {
        return status;
    } 

    void Book::setTitle(std::string t) {
        title = t;
    }
    void Book::setAuthor(std::string a) {
        author = a;
    }
    void Book::setYear(int y) {
        if (y > 0){
        year = y;
        } else std::cerr << "Invalid year" << std::endl;
    }
    void Book::setStatus(std::string s) {
        status = s;
    }
    //Available
    std::string Book::DataToSave() {
        return title + ", " + author + ", " + std::to_string(year) + status;
    }
