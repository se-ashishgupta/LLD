#include <iostream>
using namespace std;

// Prototype interface
class Prototype
{
public:
    virtual Prototype *clone() = 0;
};

// Concrete class Student that implements the Prototype interface
class Student : public Prototype
{
private:
    int rollNo;

public:
    int id;
    string name;
    string branch;
    bool inHighSchool;

    Student() {}

    Student(int id, string name, string branch, int rollNo)
    {
        this->id = id;
        this->name = name;
        this->branch = branch;
        this->rollNo = rollNo;
    }

    void setInHighSchool(bool inHighSchool)
    {
        this->inHighSchool = inHighSchool;
    }

    Prototype *clone() override
    {
        return new Student(id, name, branch, rollNo);
    }

    void printDetails()
    {
        cout << "Student Details: " << endl;
        cout << "ID: " << id << " Name: " << name << " Branch: " << branch << " Roll No: " << rollNo << endl;
    }
};

int main()
{
    cout << "Prototype Design Pattern" << endl;

    Student *student = new Student(1, "John Doe", "Computer Science", 101);
    student->printDetails();

    Student *studentClone = dynamic_cast<Student *>(student->clone());
    studentClone->printDetails();
}

// What is dynamic_cast ?
// dynamic_cast is a C++ operator used to safely convert a pointer / reference from a base class to a derived class.

// In Prototype Pattern, dynamic_cast is usually only needed when you're working with objects through the base Prototype* interface and need to recover the concrete type afterward.