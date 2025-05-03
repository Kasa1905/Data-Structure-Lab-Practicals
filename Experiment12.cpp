#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Employee {
    int id;
    string name;
    string designation;
    double salary;
};

void addEmployee(const Employee& emp) {
    ofstream dataFile("employees.dat", ios::app | ios::binary);
    if (dataFile) {
        dataFile.write(reinterpret_cast<const char*>(&emp), sizeof(Employee));
        dataFile.close();
    }
}

void deleteEmployee(int id) {
    ifstream dataFile("employees.dat", ios::binary);
    ofstream tempFile("temp.dat", ios::binary);
    Employee emp;
    bool found = false;

    if (dataFile && tempFile) {
        while (dataFile.read(reinterpret_cast<char*>(&emp), sizeof(Employee))) {
            if (emp.id != id) {
                tempFile.write(reinterpret_cast<const char*>(&emp), sizeof(Employee));
            } else {
                found = true;
            }
        }
        dataFile.close();
        tempFile.close();
        remove("employees.dat");
        rename("temp.dat", "employees.dat");
    }

    if (!found) {
        cout << "Employee with ID " << id << " not found." << endl;
    }
}

void displayEmployee(int id) {
    ifstream dataFile("employees.dat", ios::binary);
    Employee emp;
    bool found = false;

    if (dataFile) {
        while (dataFile.read(reinterpret_cast<char*>(&emp), sizeof(Employee))) {
            if (emp.id == id) {
                cout << "ID: " << emp.id << endl;
                cout << "Name: " << emp.name << endl;
                cout << "Designation: " << emp.designation << endl;
                cout << "Salary: " << emp.salary << endl;
                found = true;
                break;
            }
        }
        dataFile.close();
    }

    if (!found) {
        cout << "Employee with ID " << id << " not found." << endl;
    }
}

void displayAllEmployees() {
    ifstream dataFile("employees.dat", ios::binary);
    Employee emp;

    if (dataFile) {
        while (dataFile.read(reinterpret_cast<char*>(&emp), sizeof(Employee))) {
            cout << "ID: " << emp.id << ", Name: " << emp.name
                 << ", Designation: " << emp.designation
                 << ", Salary: " << emp.salary << endl;
        }
        dataFile.close();
    }
}

int main() {
    int choice;
    do {
        cout << "1. Add Employee" << endl;
        cout << "2. Delete Employee" << endl;
        cout << "3. Display Employee" << endl;
        cout << "4. Display All Employees" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            Employee emp;
            cout << "Enter ID: ";
            cin >> emp.id;
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, emp.name);
            cout << "Enter Designation: ";
            getline(cin, emp.designation);
            cout << "Enter Salary: ";
            cin >> emp.salary;
            addEmployee(emp);
        } else if (choice == 2) {
            int id;
            cout << "Enter ID to delete: ";
            cin >> id;
            deleteEmployee(id);
        } else if (choice == 3) {
            int id;
            cout << "Enter ID to display: ";
            cin >> id;
            displayEmployee(id);
        } else if (choice == 4) {
            displayAllEmployees();
        }
    } while (choice != 5);

    return 0;
}