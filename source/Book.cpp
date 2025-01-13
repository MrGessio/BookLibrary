#include "../include/Book.h"
#include <iostream>
#include <fstream>

std::fstream libraryDoc;

Book::Book(std::string t, std::string a, int y) {
        title = t;
        author = a;
        year = y;
        //isAvailable = true;
    }

        void Book::aboutBook() {
        std::cout << "Title: " << title << " Author: " << author << ", year: " << year
                  << ", Available: " << isAvailable << std::endl;
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
    //avaiable 

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
    //Available
    std::string Book::dataToSave() {
        return title + ", " + author + ", " + std::to_string(year);
    }