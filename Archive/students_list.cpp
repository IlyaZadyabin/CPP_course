#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

struct Student{
    std::string name;
    std::string surname;
    int birthDay;
    int birthMonth;
    int birthYear;
};

int main()
{
    int N;
    std::cin >> N;
    std::string firstName, secondName;
    int day, month, year;
    std::vector <Student> arr;
    for(int i = 0; i < N; i++){
        std::cin >> firstName >> secondName >> day >> month >> year;
        arr.push_back({firstName, secondName, day, month, year});
    }

    int M, k;
    std::cin >> M;
    std::string command;
    for(int i = 0; i < M; i++){
        std::cin >> command >> k;
        if(command != "name" && command != "date" || k < 1 || k > N){
            std::cout << "bad request" << std::endl;
        } else {
            k--;
            if (command == "name") {
                std::cout << arr[k].name << ' ' << arr[k].surname << std::endl;
            } else if (command == "date") {
                std::cout << arr[k].birthDay << '.' << arr[k].birthMonth << '.' << arr[k].birthYear << std::endl;
            }
        }
    }
}