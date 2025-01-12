#define LOGGER_H

#include <string>

class Logger{

private:
    std::string username, password;

public:
    void logIn();
    std::string getUsername();
    std::string getPassword();
};