#define BOOK_H

#include <string>


class Book {

private:
    std::string title;
    std::string author;
    int year;
    bool isAvailable;

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

};

