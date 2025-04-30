#include <gtest/gtest.h>
#include "Book.h"


class BookTestSuite : public ::testing::Test {
};

TEST_F(BookTestSuite, ShouldCreateABook) {
    Book book("Ferdydurke", "Witold Gombrowicz", 1937, "Available");

    EXPECT_EQ(book.getTitle(), "Ferdydurke") << "Title is not as expected.";
    EXPECT_EQ(book.getAuthor(), "Witold Gombrowicz") << "Author is not as expected.";
    EXPECT_EQ(book.getYear(), 1937) << "Year is not as expected.";
    EXPECT_EQ(book.getStatus(), "Available") << "Status is not as expected.";

};

TEST_F(BookTestSuite, TestingSetters) {
    Book book("Ferdydurke", "Witold Gombrowicz", 1937, "Available");

    book.setTitle("Inny Swiat");
    book.setAuthor("Gustaw Herling-Grudziński");
    book.setYear(1951);
    book.setStatus("Borrowed");

    EXPECT_EQ(book.getTitle(), "Inny Swiat") << "Title is not as expected.";
    EXPECT_EQ(book.getAuthor(), "Gustaw Herling-Grudziński") << "Author is not as expected.";
    EXPECT_EQ(book.getYear(), 1951) << "Year is not as expected.";
    EXPECT_EQ(book.getStatus(), "Borrowed") << "Status is not as expected.";

};

TEST_F(BookTestSuite, TestingInvalidYear) {
    Book book("Ferdydurke", "Witold Gombrowicz", 1937, "Available");

    book.setYear(-10);
    EXPECT_EQ(book.getYear(), 1937) << "Year is not as expected.";
};

TEST_F(BookTestSuite, TestingDataSave){
    Book book("Ferdydurke", "Witold Gombrowicz", 1937, "Available");
    std::string expectedData = "Ferdydurke, Witold Gombrowicz, 1937Available";
    EXPECT_EQ(book.DataToSave(), expectedData);
};

TEST_F(BookTestSuite, TestAboutBook){
    Book book("Ferdydurke", "Witold Gombrowicz", 1937, "Available");

    std::stringstream buffer;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());

    book.AboutBook();

    std::cout.rdbuf(oldCoutBuffer);

    std::string expectedOutput = "Title: Ferdydurke Author: Witold Gombrowicz, year: 1937, Status: Available\n";
    EXPECT_EQ(buffer.str(), expectedOutput);
};
