#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;

class Student {
private:
    string name;
    string rollNumber;
    double cgpa;
    vector<string> enrolledCourses;

public:
    Student() : name(""), rollNumber(""), cgpa(0.0) {}
    
    Student(const string& name, const string& rollNumber, double cgpa = 0.0)
        : name(name), rollNumber(rollNumber) {
        setCGPA(cgpa);
    }
    
    Student(const Student& other)
        : name(other.name), rollNumber(other.rollNumber), cgpa(other.cgpa), 
          enrolledCourses(other.enrolledCourses) {}
    
    ~Student() {
        enrolledCourses.clear();
    }
    
    string getName() const { return name; }
    string getRollNumber() const { return rollNumber; }
    double getCGPA() const { return cgpa; }
    vector<string> getEnrolledCourses() const { return enrolledCourses; }
    
    void setName(const string& newName) {
        if (!newName.empty()) {
            name = newName;
        } else {
            cerr << "Error: Name cannot be empty." << endl;
        }
    }
    
    void setRollNumber(const string& newRollNumber) {
        if (!newRollNumber.empty()) {
            rollNumber = newRollNumber;
        } else {
            cerr << "Error: Roll number cannot be empty." << endl;
        }
    }
    
    void setCGPA(double newCGPA) {
        if (newCGPA >= 0.0 && newCGPA <= 4.0) {
            cgpa = newCGPA;
        } else {
            cerr << "Error: CGPA must be between 0.0 and 4.0. Setting to 0.0." << endl;
            cgpa = 0.0;
        }
    }
    
    bool addCourse(const string& courseName) {
        if (find(enrolledCourses.begin(), enrolledCourses.end(), courseName) != enrolledCourses.end()) {
            cerr << "Error: Course '" << courseName << "' is already enrolled." << endl;
            return false;
        }
        
        enrolledCourses.push_back(courseName);
        return true;
    }
    
    void displayInfo() const {
        cout << "\n------ Student Information ------" << endl;
        cout << "Name: " << name << endl;
        cout << "Roll Number: " << rollNumber << endl;
        cout << "CGPA: " << fixed << setprecision(2) << cgpa << endl;
        
        cout << "Enrolled Courses: ";
        if (enrolledCourses.empty()) {
            cout << "None" << endl;
        } else {
            cout << endl;
            for (size_t i = 0; i < enrolledCourses.size(); ++i) {
                cout << "  " << (i + 1) << ". " << enrolledCourses[i] << endl;
            }
        }
        cout << "--------------------------------" << endl;
    }
};

class StudentManagementSystem {
private:
    vector<Student> students;

public:
    bool addStudent(const Student& student) {
        for (const auto& existingStudent : students) {
            if (existingStudent.getRollNumber() == student.getRollNumber()) {
                cerr << "Error: Student with roll number '" << student.getRollNumber() 
                          << "' already exists." << endl;
                return false;
            }
        }
        
        students.push_back(student);
        cout << "Student added successfully." << endl;
        return true;
    }
    
    Student* findStudent(const string& rollNumber) {
        for (auto& student : students) {
            if (student.getRollNumber() == rollNumber) {
                return &student;
            }
        }
        return nullptr;
    }
    
    void displayAllStudents() const {
        if (students.empty()) {
            cout << "No students in the system." << endl;
            return;
        }

        cout << "\n====== All Student Records ======" << endl;
        for (const auto& student : students) {
            student.displayInfo();
        }
        cout << "=================================" << endl;
    }
    
    size_t getStudentCount() const {
        return students.size();
    }
};

int main() {
    StudentManagementSystem sms;
    int choice;
    string name, rollNumber, courseName;
    double cgpa;

    do {
        cout << "\n===== Student Management System =====" << endl;
        cout << "1. Add a new student" << endl;
        cout << "2. Find and display student details" << endl;
        cout << "3. Add course to a student" << endl;
        cout << "4. Update student CGPA" << endl;
        cout << "5. Display all students" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                cout << "Enter student name: ";
                getline(cin, name);
                
                cout << "Enter roll number: ";
                getline(cin, rollNumber);
                
                cout << "Enter CGPA: ";
                cin >> cgpa;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                Student newStudent(name, rollNumber, cgpa);
                sms.addStudent(newStudent);
                break;
            }
            case 2: {
                cout << "Enter roll number to search: ";
                getline(cin, rollNumber);
                
                Student* foundStudent = sms.findStudent(rollNumber);
                if (foundStudent) {
                    foundStudent->displayInfo();
                } else {
                    cout << "Student with roll number '" << rollNumber << "' not found." << endl;
                }
                break;
            }
            case 3: {
                cout << "Enter student roll number: ";
                getline(cin, rollNumber);
                
                Student* foundStudent = sms.findStudent(rollNumber);
                if (foundStudent) {
                    cout << "Enter course name to add: ";
                    getline(cin, courseName);
                    
                    if (foundStudent->addCourse(courseName)) {
                        cout << "Course added successfully." << endl;
                    }
                } else {
                    cout << "Student with roll number '" << rollNumber << "' not found." << endl;
                }
                break;
            }
            case 4: {
                cout << "Enter student roll number: ";
                getline(cin, rollNumber);
                
                Student* foundStudent = sms.findStudent(rollNumber);
                if (foundStudent) {
                    cout << "Current CGPA: " << foundStudent->getCGPA() << endl;
                    cout << "Enter new CGPA: ";
                    cin >> cgpa;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    foundStudent->setCGPA(cgpa);
                    cout << "CGPA updated successfully." << endl;
                } else {
                    cout << "Student with roll number '" << rollNumber << "' not found." << endl;
                }
                break;
            }
            case 5:
                sms.displayAllStudents();
                break;
            case 0:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}