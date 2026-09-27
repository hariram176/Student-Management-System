#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>
#include <cstdio>

using namespace std;

const string FILE_NAME = "students.txt";

struct Student {
    int rollNo;
    string name;
    int age;
    string gender;
    string department;
    string phone;
    string email;
};

// Function declarations
void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
bool studentExists(int rollNo);
void clearInputBuffer();

// Clear invalid input
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Check whether a student already exists
bool studentExists(int rollNo) {
    ifstream file(FILE_NAME);
    Student s;

    while (file >> s.rollNo) {
        file.ignore();
        getline(file, s.name);
        file >> s.age;
        file.ignore();
        getline(file, s.gender);
        getline(file, s.department);
        getline(file, s.phone);
        getline(file, s.email);

        if (s.rollNo == rollNo) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

// Add a new student
void addStudent() {
    Student s;

    cout << "\n========== ADD STUDENT ==========\n";

    cout << "Enter Roll Number: ";
    while (!(cin >> s.rollNo)) {
        cout << "Invalid input. Enter a number: ";
        clearInputBuffer();
    }

    if (studentExists(s.rollNo)) {
        cout << "Student with Roll Number "
             << s.rollNo << " already exists!\n";
        return;
    }

    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, s.name);

    cout << "Enter Age: ";
    while (!(cin >> s.age)) {
        cout << "Invalid input. Enter age: ";
        clearInputBuffer();
    }

    cin.ignore();

    cout << "Enter Gender: ";
    getline(cin, s.gender);

    cout << "Enter Department: ";
    getline(cin, s.department);

    cout << "Enter Phone Number: ";
    getline(cin, s.phone);

    cout << "Enter Email: ";
    getline(cin, s.email);

    ofstream file(FILE_NAME, ios::app);

    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    file << s.rollNo << '\n';
    file << s.name << '\n';
    file << s.age << '\n';
    file << s.gender << '\n';
    file << s.department << '\n';
    file << s.phone << '\n';
    file << s.email << '\n';

    file.close();

    cout << "\nStudent added successfully!\n";
}

// Display all students
void displayStudents() {
    ifstream file(FILE_NAME);

    if (!file) {
        cout << "\nNo student records found.\n";
        return;
    }

    Student s;
    bool found = false;

    cout << "\n==================== STUDENT RECORDS ====================\n";

    cout << left
         << setw(10) << "Roll No"
         << setw(22) << "Name"
         << setw(8) << "Age"
         << setw(12) << "Gender"
         << setw(20) << "Department"
         << setw(16) << "Phone"
         << setw(30) << "Email"
         << endl;

    cout << string(118, '-') << endl;

    while (file >> s.rollNo) {
        file.ignore();

        getline(file, s.name);
        file >> s.age;
        file.ignore();
        getline(file, s.gender);
        getline(file, s.department);
        getline(file, s.phone);
        getline(file, s.email);

        cout << left
             << setw(10) << s.rollNo
             << setw(22) << s.name
             << setw(8) << s.age
             << setw(12) << s.gender
             << setw(20) << s.department
             << setw(16) << s.phone
             << setw(30) << s.email
             << endl;

        found = true;
    }

    file.close();

    if (!found) {
        cout << "No student records available.\n";
    }
}

// Search for a student
void searchStudent() {
    int rollNo;

    cout << "\n========== SEARCH STUDENT ==========\n";
    cout << "Enter Roll Number: ";

    while (!(cin >> rollNo)) {
        cout << "Invalid input. Enter a number: ";
        clearInputBuffer();
    }

    ifstream file(FILE_NAME);

    if (!file) {
        cout << "No student records found.\n";
        return;
    }

    Student s;
    bool found = false;

    while (file >> s.rollNo) {
        file.ignore();

        getline(file, s.name);
        file >> s.age;
        file.ignore();
        getline(file, s.gender);
        getline(file, s.department);
        getline(file, s.phone);
        getline(file, s.email);

        if (s.rollNo == rollNo) {
            cout << "\nStudent Found!\n";
            cout << "-----------------------------\n";
            cout << "Roll Number : " << s.rollNo << endl;
            cout << "Name        : " << s.name << endl;
            cout << "Age         : " << s.age << endl;
            cout << "Gender      : " << s.gender << endl;
            cout << "Department  : " << s.department << endl;
            cout << "Phone       : " << s.phone << endl;
            cout << "Email       : " << s.email << endl;
            cout << "-----------------------------\n";

            found = true;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "\nStudent not found!\n";
    }
}

// Update student details
void updateStudent() {
    int rollNo;

    cout << "\n========== UPDATE STUDENT ==========\n";
    cout << "Enter Roll Number to update: ";

    while (!(cin >> rollNo)) {
        cout << "Invalid input. Enter a number: ";
        clearInputBuffer();
    }

    ifstream file(FILE_NAME);

    if (!file) {
        cout << "No student records found.\n";
        return;
    }

    ofstream tempFile("temp.txt");

    Student s;
    bool found = false;

    while (file >> s.rollNo) {
        file.ignore();

        getline(file, s.name);
        file >> s.age;
        file.ignore();
        getline(file, s.gender);
        getline(file, s.department);
        getline(file, s.phone);
        getline(file, s.email);

        if (s.rollNo == rollNo) {
            found = true;

            cout << "\nEnter New Details\n";

            cin.ignore();

            cout << "Enter Name: ";
            getline(cin, s.name);

            cout << "Enter Age: ";
            while (!(cin >> s.age)) {
                cout << "Invalid input. Enter age: ";
                clearInputBuffer();
            }

            cin.ignore();

            cout << "Enter Gender: ";
            getline(cin, s.gender);

            cout << "Enter Department: ";
            getline(cin, s.department);

            cout << "Enter Phone Number: ";
            getline(cin, s.phone);

            cout << "Enter Email: ";
            getline(cin, s.email);
        }

        tempFile << s.rollNo << '\n';
        tempFile << s.name << '\n';
        tempFile << s.age << '\n';
        tempFile << s.gender << '\n';
        tempFile << s.department << '\n';
        tempFile << s.phone << '\n';
        tempFile << s.email << '\n';
    }

    file.close();
    tempFile.close();

    remove(FILE_NAME.c_str());
    rename("temp.txt", FILE_NAME.c_str());

    if (found)
        cout << "\nStudent updated successfully!\n";
    else
        cout << "\nStudent not found!\n";
}

// Delete a student
void deleteStudent() {
    int rollNo;

    cout << "\n========== DELETE STUDENT ==========\n";
    cout << "Enter Roll Number to delete: ";

    while (!(cin >> rollNo)) {
        cout << "Invalid input. Enter a number: ";
        clearInputBuffer();
    }

    ifstream file(FILE_NAME);

    if (!file) {
        cout << "No student records found.\n";
        return;
    }

    ofstream tempFile("temp.txt");

    Student s;
    bool found = false;

    while (file >> s.rollNo) {
        file.ignore();

        getline(file, s.name);
        file >> s.age;
        file.ignore();
        getline(file, s.gender);
        getline(file, s.department);
        getline(file, s.phone);
        getline(file, s.email);

        if (s.rollNo == rollNo) {
            found = true;
            continue;
        }

        tempFile << s.rollNo << '\n';
        tempFile << s.name << '\n';
        tempFile << s.age << '\n';
        tempFile << s.gender << '\n';
        tempFile << s.department << '\n';
        tempFile << s.phone << '\n';
        tempFile << s.email << '\n';
    }

    file.close();
    tempFile.close();

    remove(FILE_NAME.c_str());
    rename("temp.txt", FILE_NAME.c_str());

    if (found)
        cout << "\nStudent deleted successfully!\n";
    else
        cout << "\nStudent not found!\n";
}

// Main function
int main() {
    int choice;

    do {
        cout << "\n\n";
        cout << "============================================\n";
        cout << "       STUDENT MANAGEMENT SYSTEM\n";
        cout << "============================================\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "============================================\n";

        cout << "Enter your choice: ";

        while (!(cin >> choice)) {
            cout << "Invalid choice. Enter a number: ";
            clearInputBuffer();
        }

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                cout << "\nThank you for using Student Management System!\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 6);

    return 0;
}