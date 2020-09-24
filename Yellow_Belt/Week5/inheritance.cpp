#include <iostream>

using namespace std;

class Animal {
public:
	explicit Animal(const string& name) : Name(name) {}

	const string Name;
};


class Dog : public Animal {
public:
	explicit Dog (const string& name) : Animal(name) {}

	void Bark() {
		cout << Name << " barks: woof!" << endl;
	}
};

