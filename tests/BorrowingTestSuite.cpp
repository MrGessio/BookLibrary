#include <gtest/gtest.h>
#include "Logger.h"
#include "Reader.h"

TEST(BorrowingTestSuite, test1){
    
    std::string BookName = "Przedwiosnie";
    std::string libraryPath = "data/OneBookTestData.txt";
    std::string borrowedPath = "data/BorrowedBook.txt";


    Logger logger;
    Reader reader;

    reader.BorrowBook(BookName, logger, libraryPath, borrowedPath);

    //zrobic 2 zmienne stringowe, ktore zawieraja po wywolaniu testow
    // nazwa ksiazki autor not avaiable
    // drugi z borrow book
    //napisac funkcje ktora przyjmuje path'a odczyta i zwroci ten string i porownac w ASSERT_EQ
    //


    

}
