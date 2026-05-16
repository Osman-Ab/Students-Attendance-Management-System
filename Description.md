# 🎓 ASTU Pre-Engineering Attendance System

A simple and efficient **console-based Attendance Management System** developed in **C++** using **file handling**.  
This project helps manage student records and attendance information in a school or university environment.

---

# ✨ Features

✅ Add new students  
✅ Delete students and their attendance records  
✅ Mark attendance (Present / Absent)  
✅ View attendance by student ID  
✅ View all registered students  
✅ Update attendance status  
✅ File-based permanent storage  
✅ Input validation for menu and date format  

---

# 🛠 Technologies Used

- **C++**
- **File Handling (`fstream`)**
- **Structures**
- **Functions**
- **String Handling**
- **Console Formatting (`iomanip`)**

---

# 📂 Files Used

| File Name | Description |
|-----------|-------------|
| `students.txt` | Stores student details |
| `attendance.txt` | Stores attendance records |

---

# 🧩 Data Structures

## 👨‍🎓 Student Structure

Stores:
- Student ID
- Student Name
- Section

```cpp
struct Student {
    int id;
    char name[MAX_NAME];
    char section[MAX_SECTION];
};
```

---

## 📅 Attendance Structure

Stores:
- Student ID
- Date
- Attendance Status

```cpp
struct Attendance {
    int studentId;
    char date[MAX_DATE];
    char status[MAX_STATUS];
};
```

---

# 📋 Menu Options

```text
1. Add Student
2. Delete Student
3. Mark Attendance
4. View Attendance (by ID)
5. View All Students
6. Update Attendance Status
7. Exit
```

---

# 📆 Date Format

Attendance dates must follow the format:

```text
YYYY-MM-DD
```

### Example

```text
2026-05-16
```

---

# ⚙️ How the System Works

- Student information is saved in `students.txt`
- Attendance records are stored in `attendance.txt`
- Duplicate attendance records for the same date are prevented
- Deleting a student also removes all associated attendance records
- Attendance status can be updated anytime

---

# 🖥 Example Output

```text
==================================================
                    MAIN MENU
==================================================
1. Add Student
2. Delete Student
3. Mark Attendance
4. View Attendance (by ID)
5. View All Students
6. Update Attendance Status
7. Exit
==================================================
Enter your choice:
```

---

# 📚 Concepts Demonstrated

- Modular Programming
- File Handling in C++
- Data Validation
- Structures
- Record Management
- Updating Files Using Temporary Files

---

# 🚀 Future Improvements

- Add password authentication
- Support full names with spaces
- Add attendance percentage calculation
- Create graphical user interface (GUI)
- Export reports

---

# 👨‍💻 Author

**Osman Mohammed**

Developed as a **C++ Mini Project** for practicing:
- File Handling
- Structured Programming
- Attendance Management Systems
