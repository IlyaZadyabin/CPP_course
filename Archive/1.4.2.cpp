#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

class FunctionPart {

private:
    char operation;
    double value;
public:
    FunctionPart(char operation, double value) {
        this->operation = operation;
        this->value = value;
    }
    double Apply(double source_value) const {
        if (operation == '+') {
            return source_value + value;
        } else if(operation == '-'){
            return source_value - value;
        } else if(operation == '*'){
            return source_value * value;
        } else if(operation == '/'){
            return source_value / value;
        }
    }
    void Invert() {
        if (operation == '+') {
            operation = '-';
        } else if(operation == '-'){
            operation = '+';
        } else if(operation == '*'){
            operation = '/';
        } else if(operation == '/'){
            operation = '*';
        }
    }
};

class Function {

private:
    vector<FunctionPart> parts;
public:
    void AddPart(char operation, double value) {
        parts.emplace_back(operation, value);
    }
    double Apply(double value) const {
        for (const FunctionPart& part : parts) {
            value = part.Apply(value);
        }
        return value;
    }
    void Invert() {
        for (FunctionPart& part : parts) {
            part.Invert();
        }
        reverse(begin(parts), end(parts));
    }
};
