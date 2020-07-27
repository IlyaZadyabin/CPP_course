#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;

int Aggressive() {
    throw runtime_error("fail");
    return 2;
}

int main() {
    try {
        cout << Aggressive() << endl;
    } catch (const runtime_error& ex) {
        cout << "exception: " << ex.what() << endl;
    }
    return 0;
}