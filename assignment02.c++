#include <iostream>
#include <iomanip>  
#include <vector>
using namespace std;

class Person {
private:
    string name;
    int age;
    string ID;
    string contactInfo;
public:
    Person(string n, int a, string id, string contact) : name(n), age(a), ID(id), contactInfo(contact) {
        if (a <= 0 || a > 120) {
            cout << "Invalid age\n";
            age = 18;
        }
    }

    void setAge(int a) {
        if (a > 0 && a <= 120) age = a;
        else cout << "Invalid age \n";
    }

    int getAge() const { return age; }

    virtual void displayDetails() {
        cout << "Name: " << name << "\nAge: " << age << "\nID: " << ID << "\nContact: " << contactInfo << endl;
    }

    virtual double calculatePayment() { return 0; }
    virtual ~Person() {}
};

class Student : public Person {
private:
    string enrollmentDate;
    string program;
    double GPA;
public:
    Student(string n, int a, string id, string contact, string enrollDate, string prog, double g) 
        : Person(n, a, id, contact), enrollmentDate(enrollDate), program(prog), GPA(g) {
        if (GPA < 0.0 || GPA > 4.0) {
            cout << "Invalid GPA! Setting default value (2.5).\n";
            GPA = 2.5;
        }
    }

    void displayDetails() override {
        cout << "Student Details:\n";
        Person::displayDetails();
        cout << "Enrollment Date: " << enrollmentDate << "\nProgram: " << program << "\nGPA: " << GPA << endl;
    }
};

class Professor : public Person {
private:
    string department;
    string specialization;
    string hireDate;
public:
    Professor(string n, int a, string id, string contact, string dept, string spec, string hire) 
        : Person(n, a, id, contact), department(dept), specialization(spec), hireDate(hire) {}

    void displayDetails() override {
        cout << "Professor Details:\n";
        Person::displayDetails();
        cout << "Department: " << department << "\nSpecialization: " << specialization 
             << "\nHire Date: " << hireDate << endl;
    }

    double calculatePayment() override { return 70000; }
};

class Course {
private:
    string code, title;
    int credits;
    string description;
public:
    Course(string c, string t, int cr, string desc) : code(c), title(t), credits(cr), description(desc) {
        if (credits <= 0) {
            cout << "Invalid credits! Setting default value (3).\n";
            credits = 3;
        }
    }

    void displayCourse() {
        cout << "Course: " << title << " (" << code << ") - Credits: " << credits << "\nDescription: " << description << endl;
    }
};

class Department {
private:
    string name;
    string location;
    double budget;
public:
    Department(string n, string loc, double b) : name(n), location(loc), budget(b) {}

    void displayDepartment() {
        cout << "Department: " << name << "\nLocation: " << location << "\nBudget: Rs." << budget << endl;
    }
};

void showPersonDetails(Person* p) {
    p->displayDetails();
    cout << "Payment: Rs." << p->calculatePayment() << "\n" << endl;
}

int main() {
    Student s1("Rahul ", 20, "S101", "rahul@ncuindia.edu", "2024-08-01", "Computer Science", 3.5);
    Professor p1("Dr. Swati Tyagi", 32, "P202", "SwatiTyagi@example.com", "Engineering", "AI Research", "2015-09-12");

    Course c1("CS101", "Intro to Programming", 4, "Fundamentals of coding and logic.");
    Department d1("Computer Science", "Building A", 150000);

    cout << "\n    University Management System \n";
    
    showPersonDetails(&s1);
    showPersonDetails(&p1);

    cout << "\n Course Information \n";
    c1.displayCourse();

    cout << "\n Department Information \n";
    d1.displayDepartment();

    return 0;
}