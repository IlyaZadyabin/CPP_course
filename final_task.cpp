#include <iostream>
#include <exception>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <iomanip>

using namespace std;

class Date {
private:
    int year, month, day;
public:
    Date(const string& date_string){
        char denom;
        stringstream date_stream(date_string);
        if(!(date_stream >> year >> denom >> month >> denom >> day)){
            throw invalid_argument("Wrong date format: " + date_string);
        } else if(month < 0 || month > 12){
            throw invalid_argument("Month value is invalid: " + to_string(month));
        } else if(day < 1 || day > 31){
            throw invalid_argument("Day value is invalid: " + to_string(day));
        }
    }
    int GetYear() const { return year; }
    int GetMonth() const { return month; }
    int GetDay() const { return day; }
};

bool operator<(const Date& lhs, const Date& rhs){
    if(lhs.GetYear() < rhs.GetYear()){
        return true;
    } else if(lhs.GetYear() == rhs.GetYear()){
        if(lhs.GetMonth() < rhs.GetMonth()){
            return true;
        } else if(lhs.GetMonth() == rhs.GetMonth()){
            if(lhs.GetDay() < rhs.GetDay()){
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
}

class Database {
private:
    map<Date, set<string>> table;
public:
    void AddEvent(const Date& date, const string& event){
        table[date].insert(event);
    }
    bool DeleteEvent(const Date& date, const string& event){
        if(table[date].find(event) != table[date].end()){
            table[date].erase(event);
            return true;
        } else {
            return false;
        }

    }
    int DeleteDate(const Date& date){
        int ans = table[date].size();
        table.erase(date);
        return ans;
    }

    set<string> Find(const Date& date) const{
        return table.at(date);
    }

    void Print() const{
        for (const auto &[date, events] : table) {
            for (const auto &event : events) {
                cout << fixed << setw(4) << setfill('0') << date.GetYear();
                cout << '-' << setw(2) << date.GetMonth() << '-' << date.GetDay();
                cout << ' ' << event << endl;
            }
        }
    }
};

int main() {
    Database db;
    string command, event, date_string, task;

    while (getline(cin, command)) {
        stringstream command_stream(command);
        command_stream >> task >> date_string;
        try {
            Date date(date_string);
            if(task == "Add"){
                command_stream >> event;
                db.AddEvent(date, event);
            } else if(task == "Del"){
                if(command_stream >> event){
                    db.DeleteEvent(date, event);
                } else {
                    db.DeleteDate(date);
                }
            } else if(task == "Find"){
                set<string> ans = db.Find(date);
            } else if(task == "Print"){
                db.Print();
            } else {
                throw invalid_argument("Unknown command");
            }
        } catch (const exception & ex){
            cout << ex.what() << endl;
        }
    }
    return 0;
}

