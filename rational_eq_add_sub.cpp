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
        Rational res;
        int LCM = lcm(denominator, obj.denominator);
        int tmp_numenator = numerator * LCM / denominator + obj.numerator * LCM / obj.denominator;
        return {tmp_numenator, LCM};
    }

    Rational operator-(Rational & obj) const{
        Rational res;
        int LCM = lcm(denominator, obj.denominator);
        int tmp_numenator = numerator * LCM / denominator - obj.numerator * LCM / obj.denominator;
        return {tmp_numenator, LCM};
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
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}