#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

int main()
{
    std::ifstream input("input.txt");
    int N, M, num;
    char delim;
    input >> N >> M;

    for (int i = 0; i < N; i ++) {
        for(int j = 0; j < M; j ++){
            input >> num;
            if(j != M - 1){
                input >> delim;
            }
            std::cout << std::setw(10) << std::setfill(' ') << num;
            if(j != M - 1){
                std::cout << ' ';
            }
        }
        if(i != N - 1) {
            std::cout << std::endl;
        }
    }
    input.close();
}