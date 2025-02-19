#pragma once

#include <string>


class Book {

//public above private
//inicjalizacja zmiennych w klasach
///poczytac o serializacji danych
// zabezpieczyc dane wielki. w rok nie dawac stringu
//warto wykorzystac wskazniki

public:
    Book(std::string t, std::string a, int y, std::string s);

    void aboutBook();
    std::string getTitle();
    std::string getAuthor();
    int getYear();
    std::string getStatus();

    void setTitle(std::string t);
    void setAuthor(std::string a);
    void setYear(int y);
    void setStatus(std::string s);

    std::string dataToSave();

private:
    std::string title;
    std::string author;
    int year;
    std::string status;

};


