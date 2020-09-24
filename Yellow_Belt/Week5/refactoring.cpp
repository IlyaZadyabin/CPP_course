#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Person {
public:
	explicit Person(const string & name, const string & job) :
			Name(name), Job(job) {}
	virtual void Walk(const string& destination) const {
		cout << Job << ": " << Name << " walks to: " << destination << endl;
	}

	string getJob() const {
		return Job;
	}
	string getName() const {
		return Name;
	}

protected:
	const string Name{};
	const string Job{};
};

class Student : public Person {
public:
	Student(const string & name, const string & favouriteSong) :
			Person(name, "Student"), FavouriteSong(favouriteSong) {}

	void Learn() const {
		cout << "Student: " << Name << " learns" << endl;
	}

	void Walk(const string& destination) const override {
		cout << "Student: " << Name << " walks to: " << destination << endl;
		cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
	}

	void SingSong() const {
		cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
	}

private:
	const string FavouriteSong;
};

class Teacher : public Person {
public:
	Teacher(const string & name, const string & subject) :
			Person(name, "Teacher"), Subject(subject) {}

	void Teach() const {
		cout << "Teacher: " << Name << " teaches: " << Subject << endl;
	}

private:
	const string Subject;
};

class Policeman : public Person {
public:
	explicit Policeman(const string & name) : Person(name, "Policeman") {}

	void Check(const Person &t) const {
		cout << "Policeman: " << Name << " checks " + t.getJob() + ". "
				+ t.getJob() + "'s name is: " << t.getName() << endl;
	}
};

void VisitPlaces(const Person& t, const vector<string>& places) {
	for (const auto& p : places) {
		t.Walk(p);
	}
}

int main() {
	Teacher t("Jim", "Math");
	Student s("Ann", "We will rock you");
	Policeman p("Bob");

	VisitPlaces(t, {"Moscow", "London"});
	p.Check(s);
	VisitPlaces(s, {"Moscow", "London"});
	return 0;
}
