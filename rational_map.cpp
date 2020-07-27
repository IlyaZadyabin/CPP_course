#include <iostream>
#include <numeric>
#include <sstream>
#include <map>
#include <vector>
#include <set>

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
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}