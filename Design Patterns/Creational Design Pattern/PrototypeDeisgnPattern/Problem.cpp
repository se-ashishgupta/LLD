#include <iostream>
using namespace std;

class Student
{
private:
    int rollNo;

public:
    int id;
    string name;
    string branch;

    Student() {}

    Student(int id, string name, string branch, int rollNo)
    {
        this->id = id;
        this->name = name;
        this->branch = branch;
        this->rollNo = rollNo;
    }

    void printDetails()
    {
        cout << "Student Details: " << endl;
        cout << "ID: " << id << " Name: " << name << " Branch: " << branch << " Roll No: " << rollNo << endl;
    }
};

int main()
{
    Student *student = new Student(1, "John Doe", "Computer Science", 101);
    student->printDetails();

    Student *studentClone = new Student();
    studentClone->id = student->id;
    studentClone->name = student->name;
    studentClone->branch = student->branch;

    studentClone->printDetails();

    return 0;
}

// Cant access private members: The rollNo property is private, so we cannot access it in the clone object. This can lead to inconsistencies in the data and can cause issues in the future.