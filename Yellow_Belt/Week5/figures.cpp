#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <sstream>
#include <cmath>
#include <math.h>
#include <iomanip>

using namespace std;

class Figure {
public:
	virtual double Perimeter() const  = 0;
	virtual double Area() const  = 0;
	virtual string Name() const  = 0;
};

class Rect : public Figure {
public:
	explicit Rect(istringstream & par) {
		par >> width_ >> height_;
	}
	string Name() const override {
		return "RECT";
	}
	double Perimeter() const override {
		return width_ * 2 + height_ * 2;
	}
	double Area() const override {
		return width_ * height_;
	}

private:
	double width_{}, height_{};
};

class Circle : public Figure {
public:
	explicit Circle(istringstream & par) {
		par >> r;
	}
	string Name() const override {
		return "CIRCLE";
	}
	double Perimeter() const override {
		return 2 * 3.14 * r;
	}
	double Area() const override {
		return 3.14 * r * r;
	}

private:
	double r{};
};

class Triangle : public Figure {
public:
	explicit Triangle(istringstream & par) {
		par >> a >> b >> c;
	}
	string Name() const override {
		return "TRIANGLE";
	}
	double Perimeter() const override {
		return a + b + c;
	}
	double Area() const override {
		double s = (a + b + c) / 2;
		return sqrt(s * (s - a) * (s - b) * (s - c));
	}

private:
	double a{}, b{}, c{};
};

shared_ptr<Figure> CreateFigure(istringstream & is) {
	shared_ptr<Figure> created;
	string type;
	is >> type;
	if (type == "RECT") {
		created = make_shared<Rect>(is);
	} else if (type == "TRIANGLE") {
		created = make_shared<Triangle>(is);
	} else {
		created = make_shared<Circle>(is);
	}
	return created;
}

int main() {
	vector<shared_ptr<Figure>> figures;
	for (string line; getline(cin, line); ) {
		istringstream is(line);

		string command;
		is >> command;
		if (command == "ADD") {
			is >> ws;
			figures.push_back(CreateFigure(is));
		} else if (command == "PRINT") {
			for (const auto& current_figure : figures) {
				cout << fixed << setprecision(3)
					 << current_figure->Name() << " "
					 << current_figure->Perimeter() << " "
					 << current_figure->Area() << endl;
			}
		}
	}
	return 0;
}