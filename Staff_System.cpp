#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "Management.h"
using namespace std;

Staff staff[10] =
{
    Staff("Timothy", 30, "2400NA", "Male", "Marketing", "Video Editor", 2020, 2000, "10:00 PM", "3:00 AM"),
    Staff("Tailor Slo", 25, "2400NB", "Female", "Human Resource", "Manager", 2019, 2200, "9:00 AM", "1:00 PM"),
    Staff("Molikor Lesbaras", 28, "2400NC", "Female", "Marketing", "Lower Management", 2020, 1300, "5:00 AM", "10:00 AM")
};

string name, id, gender, department, position, clock_in, clock_out;
int    year_started, age;
float salary;

bool mainCondition = true, statusFound = false;
int  menuOptions, staff_count = 3, matchedIndex, matches[10], count;
char addStaff;
string keyword;

void saveFile(Staff staff[], int count) {
    ofstream Add;
    Add.open("Staff-Info.txt");
    for (int i = 0; i < count; i++) {
        staff[i].saveToFile(Add);
    }
    Add.close();
}

void database(Staff staff[], int& count) {
    ifstream TakeOut;
    TakeOut.open("Staff-Info.txt");
    if (TakeOut.fail()) {
        count = staff_count;
        return;
    }
    string extract;
    count = 0;
    while (getline(TakeOut, extract) && count < 10) {
        stringstream ss(extract);
        getline(ss, name, ',');
        ss >> age; ss.ignore();
        getline(ss, id, ',');
        getline(ss, gender, ',');
        getline(ss, department, ',');
        getline(ss, position, ',');
        ss >> year_started; ss.ignore();
        ss >> salary; ss.ignore();
        getline(ss, clock_in, ',');
        getline(ss, clock_out, ',');

        staff[count] = Staff(name, age, id, gender, department, position, year_started, salary, clock_in, clock_out);
        count++;
    }
}

void Menu() {
    cout << "\033[33mOptions: \033[0m" << endl;
    cout << left << setw(35) << "1. Add Staff" << "2. Display all Staff Profiles\n";
    cout << left << setw(35) << "3. Update Staff Profile" << "4. Search Staff\n";
    cout << left << setw(35) << "5. Employee Log" << "6. Delete staff\n";
    cout << "7. Exit\n";
    cout << "Enter: ";
}

void findStaff(string keyword, Staff staff[]) {
    for (int i = 0; i < staff_count; i++) {
        if (staff[i].getID() == keyword || staff[i].getName() == keyword) {
            staff[i].displayProfile();
            statusFound = true;
            matchedIndex = i;
        }
    }
}

void findByDept(string keyword, Staff staff[]) {
    for (int i = 0; i < staff_count; i++) {
        if (staff[i].getDept() == keyword) {
            matches[count] = i;
            statusFound = true;
            count++;
        }
    }
    if (!statusFound) {
        cout << "\033[31mStaff(s) not found.\033[0m\n";
    }
}

void Adding() {
    for (int i = staff_count; i < 10; i++) {

        cout << "\033[34m  [Adding New Staff]" << ":\033[0m" << endl;
        cout << "Name: ";
        cin.ignore();
        getline(cin, name); staff[i].setName(name);

        cout << "Age: ";
        cin >> age; staff[i].setAge(age);

        cout << "ID: ";
        cin >> id; staff[i].setID(id);

        cout << "Gender: ";
        cin >> gender; staff[i].setGender(gender);

        cout << "Department: ";
        cin.ignore();
        getline(cin, department); staff[i].setDept(department);

        cout << "Position: ";
        getline(cin, position); staff[i].setPosition(position);

        cout << "Starting Year: ";
        cin >> year_started; staff[i].setYear(year_started);

        cout << "Clock In Time: ";
        cin.ignore();
        getline(cin, clock_in); staff[i].setClockIn(clock_in);

        cout << "Clock Out Time: ";
        getline(cin, clock_out); staff[i].setClockOut(clock_out);

        cout << "Salary: $";
        cin >> salary; staff[i].setSalary(salary);
        staff_count++;

        cout << "Add more staff (y/n): ";
        cin >> addStaff;
        
        if (toupper(addStaff) == 'Y') continue;
        else if (toupper(addStaff) == 'N') {
            saveFile(staff, staff_count);
            break;
        }
        else {
            cout << "\033[31mInvalid Option!\033[0m" << endl;
            continue;
        }
        if (staff_count == 9) {
            cout << "Max Number of Staff Reached";
            break;
        }
    }
}

int convertToM(const string clock) {
    int hours, minutes;
    char colon;
    string AP;
    stringstream ss(clock);
    ss >> hours >> colon >> minutes >> AP;
    
    // Converts format to 24-hours
    if (AP == "PM" && hours != 12) {
        hours += 12;
    }
    else if (AP == "AM" && hours == 12) {
        hours = 0;
    }
    return hours * 60 + minutes;
}

string convertToH(int minutes) {
    int hours = minutes / 60;
    int min = minutes % 60;

    // Saves the string into an output stream
    ostringstream time;
    time << hours << "hrs " << setw(2) << setfill('0') << min << "mns";
    return time.str();
}

void clockList() {
    cout << "\033[33mClock In:\033[0m" << endl;
    for (int i = 0; i < staff_count; i++) {
        cout << left << setw(25) << staff[i].getName() << ": " << staff[i].getClockIn() << endl;
    }
    cout << endl;

    cout << "\033[33mClock Out:\033[0m" << endl;
    for (int i = 0; i < staff_count; i++) {
        cout << left << setw(25) << staff[i].getName() << ": " << staff[i].getClockOut() << endl;
    }
    cout << endl;
}

void timeCalc() {
    cout << "\033[33mHours Worked: \033[0m\n";
    for (int i = 0; i < staff_count; i++) {
        int hoursWorked = convertToM(staff[i].getClockOut()) - convertToM(staff[i].getClockIn());
        if (hoursWorked < 0) {
            hoursWorked += 24 * 60;
        }
        cout << left << setw(25) << staff[i].getName() << ": " << convertToH(hoursWorked) << endl;
    }
}

void editStaff(int slot, Staff staff[]) {
    int options;

    cout << "\033[33mEdit:\033[0m\n";
    cout << "1. Department\n";
    cout << "2. Position\n";
    cout << "3. Clock In Time\n";
    cout << "4. Clock Out Time\n";
    cout << "5. Salary\n";
    cout << "6. Back to Menu\n";

    while (true) {
        cout << "Enter: ";
        cin >> options;
        cin.ignore();

        switch (options) {
            case 1:
                cout << "Change Department to: ";
                getline(cin, department); staff[slot].setDept(department);
                break;

            case 2:
                cout << "Change Position to: ";
                getline(cin, position); staff[slot].setPosition(position);
                break;

            case 3:
                cout << "Change Start Time: ";
                getline(cin, clock_in); staff[slot].setClockIn(clock_in);
                break;

            case 4:
                cout << "Change End Time: ";
                getline(cin, clock_out); staff[slot].setClockOut(clock_out);
                break;

            case 5:
                cout << "Change Salary Amount: ";
                cin >> salary; staff[slot].setSalary(salary);
                break;

            case 6:
                system("cls");
                saveFile(staff, staff_count);
                return;

            default:
                cout << "\033[31mInvalid Input!\033[0m";
                break;
        }
    }
}

void deleteStaff(int slot, Staff staff[]) {
    char confirm;

    cout << "---------------------------------------------------------------------\n";
    cout << "\033[31mAre you sure you want to delete this staff?\033[0m" << endl;
    cout << "---------------------------------------------------------------------\n";
    cout << "Enter (y/n): ";
    cin >> confirm;

    if (toupper(confirm) == 'Y') {
        for (int i = slot; i < staff_count; i++) {
            staff[i] = staff[i + 1];
        }
        staff_count--;
        saveFile(staff, staff_count);

        cout << "\033[32mDeletion complete.\033[0m\n";
    }
    else {
        cout << "\033[31mDeletion cancelled.\033[0m\n";
    }
}

int main() {
    database(staff, staff_count);

    cout << "\033[33m---------------------------------------------------------------------\n";
    cout << "                       Staff Management System\n";
    cout << "---------------------------------------------------------------------\033[0m\n";
    while (mainCondition) {

        Menu();
        cin >> menuOptions;
        switch (menuOptions) {

            case 1:
                Adding();
                system("cls");
                break;

            case 2:
                system("cls");
                for (int i = 0; i < staff_count; i++) {
                    staff[i].displayProfile();
                }
                break;

            case 3:
                count = 0;
                statusFound = false;

                cout << "Search (id, name, dept): ";
                cin.ignore();
                getline(cin, keyword);

                findStaff(keyword, staff);
                if (statusFound) {
                    editStaff(matchedIndex, staff);
                }
                else {
                    findByDept(keyword, staff);
                    if (statusFound) {
                        int edit;

                        for (int i = 0; i < count; i++) {
                            staff[matches[i]].displayProfile();
                        }

                        while (true) {
                            cout << "\033[34mWhich staff would you like to edit: \033[0m";
                            cin >> edit;
                            if (edit >= 1 && edit <= count) {
                                editStaff(edit, staff);
                                break;
                            }
                            else {
                                cout << "\033[31mInvalid choice.\033[0m\n";
                            }
                        }
                    }
                }
                cout << endl;
                break;

            case 4:
                count = 0;
                statusFound = false;

                cout << "Search (id, name, dept): ";
                cin.ignore();
                getline(cin, keyword);

                findStaff(keyword, staff);
                if (!statusFound) {
                    findByDept(keyword, staff);
                    if (statusFound) {
                        for (int i = 0; i < count; i++) {
                            staff[matches[i]].displayProfile();
                        }
                    }
                }
                cout << endl;
                break;

            case 5:
                system("cls");
                cout << "---------------------------------------------------------------------\n";
                cout << "\033[32mAttendance Log:\033[0m\n";
                cout << "---------------------------------------------------------------------\n";
                clockList();
                timeCalc();
                cout << "---------------------------------------------------------------------\n";
                cout << endl;
                break;

            case 6:
                count = 0;
                statusFound = false;

                cout << "Search (id, name, dept): ";
                cin.ignore();
                getline(cin, keyword);

                findStaff(keyword, staff);
                if (statusFound) {
                    deleteStaff(matchedIndex, staff);
                }
                else {
                    findByDept(keyword, staff);
                    if (statusFound) {
                        int edit;

                        for (int i = 0; i < count; i++) {
                            staff[matches[i]].displayProfile();
                        }

                        while (true) {
                            cout << "\033[34mWhich profile would you like to erase: \033[0m";
                            cin >> edit;
                            if (edit >= 1 && edit <= count) {
                                deleteStaff(edit, staff);
                                break;
                            }
                            else {
                                cout << "\033[31mInvalid choice.\033[0m\n";
                            }
                        }
                    }
                }
                cout << endl;
                break;

            case 7:
                cout << "\033[31mExiting program...\033[0m\n";
                saveFile(staff, staff_count);
                mainCondition = false;
                break;

            default:
                cout << "\033[31mInvalid Input!\033[0m" << endl;
                break;
        }
    }
    return 0;
}
