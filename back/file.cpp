#include <fstream>
#include <iostream>
#include <string>

class file
{
private:
    std::ofstream handler;
    std::string buffer;
    // Methods
    void saveToFile(){
        this->handler << this->buffer;
    }

public:
    file(std::string name){
        this->handler = std::ofstream(name);
    }
    void addChar(char c){
        this->buffer = this->buffer.append(&c);
    }
};