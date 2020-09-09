#include <iostream>
#include <numeric>
#include <sstream>
#include <map>
#include <vector>
#include <exception>
#include <set>
#include <stdexcept>

using namespace std;

class Rational {
public:
    Rational() {
        numerator = 0;
        denominator = 1;
    }

    Rational operator+(const Rational & obj) const{
        int LCM = lcm(denominator, obj.denominator);
        int tmp_numenator = numerator * LCM / denominator + obj.numerator * LCM / obj.denominator;
        return {tmp_numenator, LCM};
    }

    Rational operator-(const Rational & obj) const{
        int LCM = lcm(denominator, obj.denominator);
        int tmp_numenator = numerator * LCM / denominator - obj.numerator * LCM / obj.denominator;
        return {tmp_numenator, LCM};
    }

    Rational operator*(const Rational & obj) const{
        return {numerator * obj.numerator, denominator * obj.denominator};
    }

    Rational operator/(const Rational & obj) const {
        if(obj.numerator == 0){
            throw domain_error("zero divisor");
        }
        return {numerator * obj.denominator, denominator * obj.numerator};
    }

    Rational(int num, int denom) {
        if(denom == 0){
            throw invalid_argument("zero denominator");
        }
        int GCD = gcd(num, denom);
        numerator = num / GCD;
        denominator = denom / GCD;

        if(numerator == 0){
            denominator = 1;
        } else if(numerator * denominator > 0){
            numerator = abs(numerator);
            denominator = abs(denominator);
        } else if(numerator * denominator < 0){
            denominator = abs(denominator);
            numerator = numerator < 0 ? numerator : -numerator;
        }
    }

    bool operator==(Rational const & obj) const{
        return (numerator == obj.numerator) && (denominator == obj.denominator);
    }

    int Numerator() const {
        return numerator;
    }

    int Denominator() const {
        return denominator;
    }

    friend istream & operator>>(istream & stream, Rational & obj);
    friend ostream & operator<<(ostream & stream, const Rational & obj);
    friend bool operator<(const Rational & left, const Rational & right);
    friend bool operator>(const Rational & left, const Rational & right);

private:
    int numerator, denominator;
};

bool operator<(const Rational & left, const Rational & right){
    Rational tmp_left = left;
    Rational tmp_right = right;
    Rational tmp_substraction = tmp_left - tmp_right;
    return (tmp_substraction.Numerator() < 0);
}

bool operator>(const Rational & left, const Rational & right){
    Rational tmp_left = left;
    Rational tmp_right = right;
    Rational tmp_substraction = tmp_left - tmp_right;
    return (tmp_substraction.Numerator() > 0);
}

istream & operator>>(istream & stream, Rational & obj) {
    int tmp_num, tmp_den;
    if(!stream.eof()){
        stream >> tmp_num;
        stream.ignore(1);
        stream >> tmp_den;
        obj = {tmp_num, tmp_den};
    }
    return stream;
}

ostream & operator<<(ostream & stream, const Rational & obj) {
    stream << obj.numerator << "/" << obj.denominator;
    return stream;
}

int main() {
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument&) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error&) {
    }

    cout << "OK" << endl;
    return 0;
}