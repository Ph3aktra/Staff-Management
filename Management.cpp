#include <iostream>
#include <fstream>
#include <iomanip>
#include "Management.h"
using namespace std;

Staff::Staff(){
name = "N/a";
age = 0;
id = "N/A";
gender = "N/A";
department = "Unknown";
position = "Unknown";
year_started = -1;
salary = -1;
clock_in = "Unknown";
clock_out = "Unknown";
}
Staff::Staff(string Name, int Age, string ID, string Gender,string Department, string Position, int Year_Started,float Salary, string in, string out){
name = Name;
age = Age;
id = ID;
gender = Gender;
department = Department;
position = Position;
year_started = Year_Started;
salary = Salary;
clock_in = in;
clock_out = out;
}

void Staff::setName(string name){
this -> name = name;
}
void Staff::setID(string id){
this -> id = id;
}
void Staff::setGender(string gender){
this -> gender = gender;
}
void Staff::setDept(string department){
this -> department = department;
}
void Staff::setPosition(string position){
this -> position = position;
}
void Staff::setClockIn(string clock_in){
this -> clock_in = clock_in;
}
void Staff::setClockOut(string clock_out){
this -> clock_out = clock_out;
}
void Staff::setAge(int age){
this -> age = age;
}
void Staff::setSalary(float salary){
this -> salary = salary;
}
void Staff::setYear(int year_started){
this -> year_started = year_started;
}

string Staff::getName(){
return name;
};
string Staff::getID(){
return id;
};
string Staff::getGender(){
return gender;
};
string Staff::getDept(){
return department;
};
string Staff::getPosition(){
return position;
};
string Staff::getClockIn(){
return clock_in;
};
string Staff::getClockOut(){
return clock_out;
};
int Staff::getAge(){
return age;
};
float Staff::getSalary(){
return salary;
};
int Staff::getYear(){
return year_started;
};

void Staff::displayProfile(){
    cout << "---------------------------------------------------------------------\n";
    cout << "\033[33mProfile: " << name << "\033[0m\n";
    cout << "---------------------------------------------------------------------\n";
    cout << left
         << setw(30) << ("Name: " + name)
         << "|  "
         << ("Department: " + department) << endl;

    cout << setw(30) << ("ID: " + id)
         << "|  "
         << ("Position: " + position) << endl;

    cout << setw(30) << ("Age: " + to_string(age))
         << "|  "
         << ("Clock-In: " + clock_in) << endl;

    cout << setw(30) << ("Gender: " + gender)
         << "|  "
         << ("Clock-Out: " + clock_out) << endl;

    cout << setw(30) << ("Year Started: " + to_string(year_started))
         << "|  "
         << "Salary: $" << fixed << setprecision(2) << salary << endl;
} 

void Staff::saveToFile(ofstream& file){
    file << name << "," << age << "," << id << "," << gender << "," 
         << department << "," << position << "," << year_started << "," 
         << salary << "," << clock_in << "," << clock_out << "\n";
};
