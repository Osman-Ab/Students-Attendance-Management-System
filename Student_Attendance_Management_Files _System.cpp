#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cctype>
using namespace std;

// Constants
const int MAX_NAME = 50;
const int MAX_SECTION = 10;
const int MAX_DATE = 11;   // "YYYY-MM-DD" + null
const int MAX_STATUS = 10; // "Present"/"Absent"
const char STUDENT_FILE[] = "students.txt";
const char ATTENDANCE_FILE[] = "attendance.txt";

// Structure for a student
struct Student {
    int id;
    char name[MAX_NAME];
    char section[MAX_SECTION];
};

// Structure for an attendance record
struct Attendance {
    int studentId;
    char date[MAX_DATE];
    char status[MAX_STATUS];
};

// Function prototypes
void displayMenu();
int getChoice();
void addStudent();
void deleteStudent();
void markAttendance();
void viewAttendance();
void viewAllStudents();
void updateAttendance();
bool studentExists(int id);
void getStudentById(int id, Student &s);
bool isValidDate(const char *date);
void printLine(char ch = '-', int width = 60);

int main() {
    cout << "\n\t\tASTU Pre-Engineering Attendance System\n";
    int choice;
    do {
        displayMenu();
        choice = getChoice();
        switch (choice) {
            case 1: addStudent(); break;
            case 2: deleteStudent(); break;
            case 3: markAttendance(); break;
            case 4: viewAttendance(); break;
            case 5: viewAllStudents(); break;
            case 6: updateAttendance(); break;
            case 7: cout << "\n\tExiting system. Goodbye!\n"; break;
            default: cout << "\n\tInvalid choice. Please try again.\n";
        }
    } while (choice != 7);
    return 0;
}

// Display menu with formatting
void displayMenu() {
    cout << "\n";
    printLine('=', 50);
    cout << setw(30) << " MAIN MENU\n";
    printLine('=', 50);
    cout << left;
    cout << setw(4) << "1." << "Add Student\n";
    cout << setw(4) << "2." << "Delete Student\n";
    cout << setw(4) << "3." << "Mark Attendance\n";
    cout << setw(4) << "4." << "View Attendance (by ID)\n";
    cout << setw(4) << "5." << "View All Students\n";
    cout << setw(4) << "6." << "Update Attendance Status\n";
    cout << setw(4) << "7." << "Exit\n";
    printLine('=', 50);
    cout << "Enter your choice: ";
}

// Get a valid integer choice
int getChoice() {
    int choice;
    cin >> choice;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Enter a number: ";
        cin >> choice;
    }
    cin.ignore(1000, '\n');
    return choice;
}

// Check if a student ID already exists in the file
bool studentExists(int id) {
    ifstream in(STUDENT_FILE);
    if (!in) return false;
    Student temp;
    while (in >> temp.id >> temp.name >> temp.section) {
        if (temp.id == id) {
            in.close();
            return true;
        }
    }
    in.close();
    return false;
}

// Retrieve student details by ID (assumes student exists)
void getStudentById(int id, Student &s) {
    ifstream in(STUDENT_FILE);
    while (in >> s.id >> s.name >> s.section) {
        if (s.id == id) {
            in.close();
            return;
        }
    }
    in.close();
}

// Validate date format "YYYY-MM-DD"
bool isValidDate(const char *date) {
    if (strlen(date) != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;
    for (int i = 0; i < 10; ++i) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(date[i])) return false;
    }
    return true;
}

// Add a new student
void addStudent() {
    cout << "\n--- Add Student ---\n";
    Student s;
    cout << "Enter Student ID: ";
    cin >> s.id;
    if (studentExists(s.id)) {
        cout << "Error: Student with ID " << s.id << " already exists.\n";
        return;
    }
    cout << "Enter Name (single word): ";
    cin >> s.name;
    cout << "Enter Section: ";
    cin >> s.section;

    // Append to file
    ofstream out(STUDENT_FILE, ios::app);
    if (!out) {
        cout << "Error opening student file!\n";
        return;
    }
    out << left << setw(6) << s.id << setw(MAX_NAME) << s.name
        << setw(MAX_SECTION) << s.section << endl;
    out.close();
    cout << "Student added successfully.\n";
}

// Delete a student and his/her attendance records
void deleteStudent() {
    cout << "\n--- Delete Student ---\n";
    int id;
    cout << "Enter Student ID to delete: ";
    cin >> id;
    if (!studentExists(id)) {
        cout << "Error: Student not found.\n";
        return;
    }

    // Remove from students.txt
    ifstream in(STUDENT_FILE);
    ofstream temp("temp_students.txt");
    Student s;
    bool deleted = false;
    while (in >> s.id >> s.name >> s.section) {
        if (s.id != id)
            temp << left << setw(6) << s.id << setw(MAX_NAME) << s.name
                 << setw(MAX_SECTION) << s.section << endl;
        else
            deleted = true;
    }
    in.close();
    temp.close();
    if (deleted) {
        remove(STUDENT_FILE);
        rename("temp_students.txt", STUDENT_FILE);
    } else {
        remove("temp_students.txt");
    }

    // Remove all attendance records for that student
    ifstream attIn(ATTENDANCE_FILE);
    ofstream attTemp("temp_attendance.txt");
    Attendance a;
    if (attIn) {
        while (attIn >> a.studentId >> a.date >> a.status) {
            if (a.studentId != id)
                attTemp << left << setw(6) << a.studentId << setw(MAX_DATE)
                        << a.date << setw(MAX_STATUS) << a.status << endl;
        }
        attIn.close();
        attTemp.close();
        remove(ATTENDANCE_FILE);
        rename("temp_attendance.txt", ATTENDANCE_FILE);
    }
    cout << "Student and all associated attendance records deleted.\n";
}

// Mark attendance for a student on a given date
void markAttendance() {
    cout << "\n--- Mark Attendance ---\n";
    int id;
    cout << "Enter Student ID: ";
    cin >> id;
    if (!studentExists(id)) {
        cout << "Error: Student not found.\n";
        return;
    }
    char date[MAX_DATE];
    cout << "Enter date (YYYY-MM-DD): ";
    cin >> date;
    if (!isValidDate(date)) {
        cout << "Error: Invalid date format.\n";
        return;
    }
    // Check if attendance already exists for this student on this date
    ifstream in(ATTENDANCE_FILE);
    Attendance a;
    bool exists = false;
    if (in) {
        while (in >> a.studentId >> a.date >> a.status) {
            if (a.studentId == id && strcmp(a.date, date) == 0) {
                exists = true;
                break;
            }
        }
        in.close();
    }
    if (exists) {
        cout << "Attendance for this student on " << date << " already recorded.\n";
        return;
    }
    char status[MAX_STATUS];
    cout << "Enter status (Present/Absent): ";
    cin >> status;

    ofstream out(ATTENDANCE_FILE, ios::app);
    if (!out) {
        cout << "Error opening attendance file!\n";
        return;
    }
    out << left << setw(6) << id << setw(MAX_DATE) << date
        << setw(MAX_STATUS) << status << endl;
    out.close();
    cout << "Attendance recorded.\n";
}

// View attendance for a specific student
void viewAttendance() {
    cout << "\n--- View Attendance ---\n";
    int id;
    cout << "Enter Student ID: ";
    cin >> id;
    if (!studentExists(id)) {
        cout << "Error: Student not found.\n";
        return;
    }
    // Get student name for display
    Student stud;
    getStudentById(id, stud);

    cout << "\nAttendance records for " << stud.name << " (ID: " << id << "):\n";
    printLine('-', 45);
    cout << left << setw(12) << "Date" << setw(10) << "Status" << endl;
    printLine('-', 45);

    ifstream in(ATTENDANCE_FILE);
    Attendance a;
    int count = 0;
    while (in >> a.studentId >> a.date >> a.status) {
        if (a.studentId == id) {
            cout << left << setw(12) << a.date << setw(10) << a.status << endl;
            count++;
        }
    }
    in.close();
    if (count == 0) {
        cout << "No attendance records found.\n";
    }
    printLine('-', 45);
    cout << "Total records: " << count << endl;
}

// View all students
void viewAllStudents() {
    cout << "\n--- All Registered Students ---\n";
    ifstream in(STUDENT_FILE);
    if (!in) {
        cout << "No students registered yet.\n";
        return;
    }
    printLine('-', 55);
    cout << left << setw(8) << "ID" << setw(25) << "Name" << setw(12) << "Section" << endl;
    printLine('-', 55);
    Student s;
    int count = 0;
    while (in >> s.id >> s.name >> s.section) {
        cout << left << setw(8) << s.id << setw(25) << s.name
             << setw(12) << s.section << endl;
        count++;
    }
    in.close();
    printLine('-', 55);
    cout << "Total students: " << count << endl;
}

// Update an existing attendance record (change status)
void updateAttendance() {
    cout << "\n--- Update Attendance ---\n";
    int id;
    cout << "Enter Student ID: ";
    cin >> id;
    if (!studentExists(id)) {
        cout << "Error: Student not found.\n";
        return;
    }
    char date[MAX_DATE];
    cout << "Enter date (YYYY-MM-DD) to update: ";
    cin >> date;
    if (!isValidDate(date)) {
        cout << "Error: Invalid date format.\n";
        return;
    }

    // Check if record exists
    ifstream in(ATTENDANCE_FILE);
    if (!in) {
        cout << "Attendance file does not exist.\n";
        return;
    }
    ofstream temp("temp_attendance.txt");
    Attendance a;
    bool found = false;
    while (in >> a.studentId >> a.date >> a.status) {
        if (a.studentId == id && strcmp(a.date, date) == 0) {
            // Found record to update
            cout << "Current status: " << a.status << endl;
            cout << "Enter new status (Present/Absent): ";
            cin >> a.status;
            found = true;
        }
        temp << left << setw(6) << a.studentId << setw(MAX_DATE) << a.date
             << setw(MAX_STATUS) << a.status << endl;
    }
    in.close();
    temp.close();
    if (!found) {
        cout << "No attendance record found for this date.\n";
        remove("temp_attendance.txt");
    } else {
        remove(ATTENDANCE_FILE);
        rename("temp_attendance.txt", ATTENDANCE_FILE);
        cout << "Attendance status updated.\n";
    }
}

// Print a line of a given character
void printLine(char ch, int width) {
    for (int i = 0; i < width; ++i) cout << ch;
    cout << endl;
