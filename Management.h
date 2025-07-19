#ifndef STAFF_H
#define STAFF_H
#include <iostream>
#include <fstream>
using namespace std;

class Staff {
private:
    string name, id, gender, department, position, clock_in, clock_out;
    int year_started, age;
    float salary;

public:
    Staff();

    Staff(string Name, int Age, string ID, string Gender, string Department, string Position, int Year_Started, float Salary, string in, string out);

    void setName(string name);
    void setID(string id);
    void setGender(string gender);
    void setDept(string department);
    void setPosition(string position);
    void setClockIn(string clock_in);
    void setClockOut(string clock_out);
    void setAge(int age);
    void setSalary(float salary);
    void setYear(int year_started);

    string getName();
    string getID();
    string getGender();
    string getDept();
    string getPosition();
    string getClockIn();
    string getClockOut();
    int getAge();
    float getSalary();
    int getYear();

    void displayProfile();
    void saveToFile(ofstream& file);
};

#endif