#pragma once

#include <string>


class Book {

//public above private
//inicjalizacja zmiennych w klasach
///poczytac o serializacji danych
// zabezpieczyc dane wielki. w rok nie dawac stringu
//warto wykorzystac wskazniki


/*

public:
    Book(std::string t, std::string a, int y);

    void AboutBook();
    std::string GetTitle();
    std::string GetAuthor();
    int GetYear();

    void SetTitle(std::string t);
    void SetAuthor(std::string a);
    void SetYear(int y);

    std::string DataToSave();

private:
    std::string title_;
    std::string author_;
    int year_;
    bool isAvailable_;

};
*/
public:
    Book(std::string t, std::string a, int y);

    void aboutBook();
    std::string getTitle();
    std::string getAuthor();
    int getYear();

    void setTitle(std::string t);
    void setAuthor(std::string a);
    void setYear(int y);

    std::string dataToSave();

private:
    std::string title;
    std::string author;
    int year;
    bool isAvailable;

};


