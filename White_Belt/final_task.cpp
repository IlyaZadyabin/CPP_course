#include <iostream>
#include <exception>
#include <string>
#include <map>
#include <set>
#include <iomanip>

using namespace std;

class Date {
private:
    int year{}, month{}, day{};
public:
    explicit Date(const string& date_string){
        char first_denom, second_denom;
        stringstream date_stream(date_string);
        if(!(date_stream >> year >> first_denom >> month >> second_denom >> day) ||
           first_denom != '-' || second_denom != '-' || !date_stream.eof()){
            throw invalid_argument("Wrong date format: " + date_string);
        } else if(month < 1 || month > 12){
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
        return table[date].erase(event) != 0;
    }
    int DeleteDate(const Date& date){
        int ans = table[date].size();
        table.erase(date);
        return ans;
    }

    set<string> Find(const Date& date) {
        return table[date];
    }

    void Print() const{
        for (const auto &[date, events] : table) {
            for (const auto &event : events) {
                cout << fixed << setw(4) << setfill('0') << date.GetYear()
                     << '-' << setw(2) << date.GetMonth() << '-' << setw(2)
                     << date.GetDay() << ' ' << event << endl;
            }
        }
    }
};

int main() {
    Database db;
    string command, event, date_string, task;

    while (getline(cin, command)) {
        if(command.empty()){ continue; }

        stringstream command_stream(command);
        command_stream >> task;
        try {
            if (task == "Print") {
                db.Print();
            } else {
                if(task != "Add" && task != "Del" && task != "Find") {
                    throw invalid_argument("Unknown command: " + task);
                }
                command_stream >> date_string;
                Date date(date_string);

                if (task == "Add") {
                    command_stream >> event;
                    db.AddEvent(date, event);
                } else if (task == "Del") {
                    if (command_stream >> event) {
                        if (db.DeleteEvent(date, event)) {
                            cout << "Deleted successfully" << endl;
                        } else {
                            cout << "Event not found" << endl;
                        }
                    } else {
                        int deletedEvents = db.DeleteDate(date);
                        cout << "Deleted " << to_string(deletedEvents) << " events" << endl;
                    }
                } else if (task == "Find") {
                    set<string> ans = db.Find(date);
                    for (const auto &item : ans) {
                        cout << item << endl;
                    }
                }
            }
        } catch (const invalid_argument & ex){
            cout << ex.what() << endl;
        }
    }
    return 0;
}

