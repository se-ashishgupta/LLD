#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Forward declaration
class StudentBuilder;

// =======================
// Product Class
// =======================
class Student
{
private:
    // Mandatory fields
    int rollNumber;
    int age;
    string name;
    string branch;

    // Optional fields
    string fatherName;
    string motherName;
    vector<string> subjects;
    string mobileNo;
    string emailId;

    // Only builders can create Student - giving access of private member or fucntion to StudentBuilder class
    friend class StudentBuilder;

    Student(const StudentBuilder &builder);

public:
    void printDetails()
    {
        cout << "\n===== Student Details =====\n";
        cout << "Roll Number : " << rollNumber << endl;
        cout << "Name        : " << name << endl;
        cout << "Age         : " << age << endl;
        cout << "Branch      : " << branch << endl;
        cout << "Father Name : " << fatherName << endl;
        cout << "Mother Name : " << motherName << endl;

        cout << "Subjects    : ";
        for (string s : subjects)
            cout << s << " ";
        cout << endl;

        cout << "Mobile No   : " << mobileNo << endl;
        cout << "Email Id    : " << emailId << endl;
    }
};

// =======================
// Abstract Builder
// =======================
class StudentBuilder
{
protected:
    // Mandatory fields
    int rollNumber;
    int age;
    string name;
    string branch;

    // Optional fields
    string fatherName;
    string motherName;
    vector<string> subjects;
    string mobileNo;
    string emailId;

public:
    StudentBuilder(int rollNumber,
                   int age,
                   string name,
                   string branch)
    {
        this->rollNumber = rollNumber;
        this->age = age;
        this->name = name;
        this->branch = branch;
    }

    virtual ~StudentBuilder() {}

    StudentBuilder &setFatherName(string fatherName)
    {
        this->fatherName = fatherName;
        return *this;
    }

    StudentBuilder &setMotherName(string motherName)
    {
        this->motherName = motherName;
        return *this;
    }

    StudentBuilder &setMobileNo(string mobileNo)
    {
        this->mobileNo = mobileNo;
        return *this;
    }

    StudentBuilder &setEmailId(string emailId)
    {
        this->emailId = emailId;
        return *this;
    }

    // Different builders can set subjects differently
    virtual StudentBuilder &setSubjects(vector<string> subjects) = 0;

    Student build()
    {
        return Student(*this);
    }

    friend class Student;
};

// =======================
// Student Constructor
// =======================
Student::Student(const StudentBuilder &builder)
{
    rollNumber = builder.rollNumber;
    age = builder.age;
    name = builder.name;
    branch = builder.branch;

    fatherName = builder.fatherName;
    motherName = builder.motherName;
    subjects = builder.subjects;
    mobileNo = builder.mobileNo;
    emailId = builder.emailId;
}

// =======================
// Concrete Builder
// =======================
class EngineeringStudentBuilder : public StudentBuilder
{
public:
    EngineeringStudentBuilder(int rollNumber,
                              int age,
                              string name,
                              string branch)
        : StudentBuilder(rollNumber, age, name, branch)
    {
    }

    StudentBuilder &setSubjects(vector<string> subjects) override
    {
        this->subjects = subjects;
        return *this;
    }
};

// =======================
// Concrete Builder
// =======================
class MedicalStudentBuilder : public StudentBuilder
{
public:
    MedicalStudentBuilder(int rollNumber,
                          int age,
                          string name,
                          string branch)
        : StudentBuilder(rollNumber, age, name, branch)
    {
    }

    StudentBuilder &setSubjects(vector<string> subjects) override
    {
        this->subjects = subjects;
        return *this;
    }
};

// =======================
// Main
// =======================
int main()
{
    Student student =
        EngineeringStudentBuilder(101,
                                  20,
                                  "Ashish",
                                  "CSE")
            .setFatherName("Rajesh")
            .setMotherName("Sunita")
            .setSubjects({"DBMS", "OS", "CN"})
            .setMobileNo("9876543210")
            .setEmailId("ashish@gmail.com")
            .build();

    Student student1 =
        EngineeringStudentBuilder(101,
                                  20,
                                  "Ashish",
                                  "CSE")
            .setFatherName("Rajesh")
            .setMotherName("Sunita")
            .setSubjects({"Bio", "Botny", "Physics"})
            .setMobileNo("9876543210")
            .setEmailId("ashish@gmail.com")
            .build();

    student.printDetails();
    student1.printDetails();

    return 0;
}