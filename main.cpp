#include <iostream>

class Book{

    private:
    std::string title;
    std::string author;
    int year;
    bool isAvailable;
};

//void showBooks(); //based by category comedy, fantasy etc. seems kinda too much
void logIn();

class Users{
    //name, surname
    //functions: LogIN
};

//who keeps the names. is it users or reades. Does admin needs to have a name? should log in somehow
class Readers{
    //name, surname
    //functions borrow, return, inherits logIn
    
    void searchBooks(); //search by what. by just the title, the author...?
    void borrowBooks();
    void returnBooks();
};

class Admin{
    //function: addBooks, deleteBooks
    //inhertis login from user?
        
    void addBooks();  
    void deleteBooks();
};

int main(){
    
    int chosenNumber;;
    std::cout << "Welcome to the Library" << std::endl;
    std::cout << "Press a number to choose from the option below:" << std::endl;
    std::cout << "[1] To view all books" << std::endl;
    std::cout << "[2] To search a book" << std::endl;
    std::cout << "[3] To log in" << std::endl;
    std::cout << "Press...";
    std::cin >>  chosenNumber;
    
    
    
    //
    return 0;
}