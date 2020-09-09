#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

int main()
{
    std::ifstream input("input.txt");
    double num;
    while (input >> num) {
        std::cout << std::fixed << std::setprecision(3);
        std::cout << num << std::endl;
    }
    input.close();
}