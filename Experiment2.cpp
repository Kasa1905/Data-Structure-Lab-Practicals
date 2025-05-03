#include <iostream>
#include <fstream>
#include <string>
#include <cstdio> // for remove and rename

using namespace std;

struct Student {
    int rollNo;
    char name[50];
    char division;
    char address[100];
};

void addStudent() {
    ofstream outFile("students.dat", ios::binary | ios::app);
    if (!outFile) {
        cout << "Error opening file for writing." << endl;
        return;
    }

    Student s;
    cout << "Enter roll number: ";
    cin >> s.rollNo;
    cin.ignore();

    cout << "Enter name: ";
    cin.getline(s.name, 50);

    cout << "Enter division: ";
    cin >> s.division;
    cin.ignore();

    cout << "Enter address: ";
    cin.getline(s.address, 100);

    outFile.write(reinterpret_cast<char*>(&s), sizeof(Student));
    outFile.close();
    cout << "Student record added successfully." << endl;
}

void displayStudent() {
    ifstream inFile("students.dat", ios::binary);
    if (!inFile) {
        cout << "No records found." << endl;
        return;
    }

    int rollNo;
    cout << "Enter roll number to display: ";
    cin >> rollNo;

    Student s;
    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        if (s.rollNo == rollNo) {
            cout << "Roll Number: " << s.rollNo << endl;
            cout << "Name: " << s.name << endl;
            cout << "Division: " << s.division << endl;
            cout << "Address: " << s.address << endl;
            found = true;
            break;
        }
    }
    inFile.close();

    if (!found) {
        cout << "Student record not found." << endl;
    }
}

void deleteStudent() {
    ifstream inFile("students.dat", ios::binary);
    if (!inFile) {
        cout << "No records found." << endl;
        return;
    }

    int rollNo;
    cout << "Enter roll number to delete: ";
    cin >> rollNo;

    ofstream outFile("temp.dat", ios::binary);
    Student s;
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        if (s.rollNo == rollNo) {
            found = true;
            continue; // skip writing this record to delete it
        }
        outFile.write(reinterpret_cast<char*>(&s), sizeof(Student));
    }

    inFile.close();
    outFile.close();

    if (found) {
        remove("students.dat");
        rename("temp.dat", "students.dat");
        cout << "Student record deleted successfully." << endl;
    } else {
        remove("temp.dat");
        cout << "Student record not found." << endl;
    }
}

int main() {
    int choice;
    do {
        cout << "\nStudent Information System\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Display Student\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                deleteStudent();
                break;
            case 3:
                displayStudent();
                break;
            case 4:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
