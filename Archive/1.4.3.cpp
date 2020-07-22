#include <fstream>
#include <iostream>
#include <string>

int main()
{
    std::ifstream input("input.txt");
    std::string line;
    if(input.is_open()) {
        while (std::getline(input, line)) {
            std::cout << line << std::endl;
        }
    } else {
        std::cout << "Failure" << std::endl;
    }
}