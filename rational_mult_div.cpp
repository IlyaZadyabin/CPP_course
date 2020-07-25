#include <iostream>
#include <numeric>
using namespace std;

class Rational {
public:
    Rational() {
        numerator = 0;
        denominator = 1;
    }

    Rational operator+(Rational & obj) const{
        int LCM = lcm(denominator, obj.denominator);
        int tmp_numenator = numerator * LCM / denominator + obj.numerator * LCM / obj.denominator;
        return {tmp_numenator, LCM};
    }

    Rational operator-(Rational & obj) const{
        int LCM = lcm(denominator, obj.denominator);
        int tmp_numenator = numerator * LCM / denominator - obj.numerator * LCM / obj.denominator;
        return {tmp_numenator, LCM};
    }

    Rational operator*(Rational & obj) const{
        return {numerator * obj.numerator, denominator * obj.denominator};
    }

    Rational operator/(Rational & obj) const {
        return {numerator * obj.denominator, denominator * obj.numerator};
    }

    Rational(int num, int denom) {
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

private:
    int numerator, denominator;
};

int main() {
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;
    return 0;
}