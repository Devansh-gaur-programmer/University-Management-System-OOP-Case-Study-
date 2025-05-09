#include <iostream>
#include <vector>
using namespace std;

class Person {
protected:
    string name;
    int age;
    string ID;
public:
    Person(string n, int a, string id) : name(n), age(a), ID(id) {}

    virtual void displayDetails() {
        cout << "Name: " << name << "\nAge: " << age << "\nID: " << ID << endl;
    }

    virtual double calculatePayment() { return 0; }
    virtual ~Person() {}
};

class Student : public Person {
protected:
    string enrollmentDate;
    string program;
public:
    Student(string n, int a, string id, string enrollDate, string prog) 
        : Person(n, a, id), enrollmentDate(enrollDate), program(prog) {}

    void displayDetails() override {
        cout << "Student Details:\n";
        Person::displayDetails();
        cout << "Enrollment Date: " << enrollmentDate << "\nProgram: " << program << endl;
    }
};

class UndergraduateStudent : public Student {
private:
    string major, minor, graduationDate;
public:
    UndergraduateStudent(string n, int a, string id, string enrollDate, string prog, string maj, string min, string gradDate) 
        : Student(n, a, id, enrollDate, prog), major(maj), minor(min), graduationDate(gradDate) {}

    void displayDetails() override {
        cout << "Undergraduate Student:\n";
        Student::displayDetails();
        cout << "Major: " << major << "\nMinor: " << minor << "\nGraduation Date: " << graduationDate << endl;
    }
};

class GraduateStudent : public Student {
private:
    string researchTopic, advisor, thesisTitle;
public:
    GraduateStudent(string n, int a, string id, string enrollDate, string prog, string topic, string adv, string thesis) 
        : Student(n, a, id, enrollDate, prog), researchTopic(topic), advisor(adv), thesisTitle(thesis) {}

    void displayDetails() override {
        cout << "Graduate Student:\n";
        Student::displayDetails();
        cout << "Research Topic: " << researchTopic << "\nAdvisor: " << advisor << "\nThesis Title: " << thesisTitle << endl;
    }
};

class Professor : public Person {
protected:
    string department;
public:
    Professor(string n, int a, string id, string dept) : Person(n, a, id), department(dept) {}

    void displayDetails() override {
        cout << "Professor Details:\n";
        Person::displayDetails();
        cout << "Department: " << department << endl;
    }

    virtual double calculatePayment() override { return 80000; }
};

class AssistantProfessor : public Professor {
public:
    AssistantProfessor(string n, int a, string id, string dept) : Professor(n, a, id, dept) {}

    double calculatePayment() override { return 90000; }
};

class AssociateProfessor : public Professor {
public:
    AssociateProfessor(string n, int a, string id, string dept) : Professor(n, a, id, dept) {}

    double calculatePayment() override { return 110000; }
};

class FullProfessor : public Professor {
public:
    FullProfessor(string n, int a, string id, string dept) : Professor(n, a, id, dept) {}

    double calculatePayment() override { return 150000; }
};

class Course {
private:
    string code, title;
    int credits;
    Professor* instructor;
public:
    Course(string c, string t, int cr, Professor* prof) : code(c), title(t), credits(cr), instructor(prof) {}

    void displayCourse() {
        cout << "Course: " << title << " (" << code << ") - Credits: " << credits << endl;
        cout << "Instructor: ";
        instructor->displayDetails();
    }
};

class Department {
private:
    string name;
    vector<Professor*> professors;
public:
    Department(string n) : name(n) {}

    void addProfessor(Professor* prof) { professors.push_back(prof); }

    void displayDepartment() {
        cout << "Department: " << name << "\nProfessors:\n";
        for (auto prof : professors) prof->displayDetails();
    }
};

class University {
private:
    vector<Department*> departments;
public:
    void addDepartment(Department* dept) { departments.push_back(dept); }

    void displayUniversity() {
        cout << "University Overview:\n";
        for (auto dept : departments) dept->displayDepartment();
    }
};

int main() {
    AssistantProfessor p1("Dr. Swati Tyagi ", 32, "P202", "Engineering");
    AssociateProfessor p2("Dr. Seema Thakran ", 43, "P102", "Mathematics");

    Course c1("CSL108N", "Fundamentals of Computer Programming ", 4, &p1);
    Course c2("MAL152", "ENGINEERING MATHS-II", 3, &p2);

    Department d1("Computer Science");
    d1.addProfessor(&p1);

    Department d2("Mathematics");
    d2.addProfessor(&p2);

    University uni;
    uni.addDepartment(&d1);
    uni.addDepartment(&d2);

    cout << "\n                          University Management System \n";
    uni.displayUniversity();

    cout << "\n Course Information \n";
    c1.displayCourse();
    c2.displayCourse();

    return 0;
}
