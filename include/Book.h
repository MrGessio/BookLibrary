#pragma once

#include <string>


class Book {

public:
    Book(std::string t, std::string a, int y, std::string s);

    void AboutBook();
    std::string getTitle();
    std::string getAuthor();
    int getYear();
    std::string getStatus();

    void setTitle(std::string t);
    void setAuthor(std::string a);
    void setYear(int y);
    void setStatus(std::string s);

    std::string DataToSave();

private:
    std::string title;
    std::string author;
    int year;
    std::string status;

};


