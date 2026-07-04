#include <iostream>
#include <vector>
#include <string>

using namespace std;

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

public:
    // =====================================================
    // Constructor 1: Only mandatory fields
    // =====================================================
    Student(int rollNumber, int age, string name, string branch)
    {
        this->rollNumber = rollNumber;
        this->age = age;
        this->name = name;
        this->branch = branch;
    }

    // =====================================================
    // Constructor 2: Add fatherName
    // =====================================================
    Student(int rollNumber,
            int age,
            string name,
            string branch,
            string fatherName)
    {

        this->rollNumber = rollNumber;
        this->age = age;
        this->name = name;
        this->branch = branch;
        this->fatherName = fatherName;
    }

    // =====================================================
    // Constructor 3: Add fatherName + motherName
    // =====================================================
    Student(int rollNumber,
            int age,
            string name,
            string branch,
            string fatherName,
            string motherName)
    {

        this->rollNumber = rollNumber;
        this->age = age;
        this->name = name;
        this->branch = branch;
        this->fatherName = fatherName;
        this->motherName = motherName;
    }

    /*
      Problem:
      We CANNOT create another constructor like

      Student(int rollNumber,
              int age,
              string name,
              string branch,
              string fatherName,
              string motherName,
              string emailId)

      and

      Student(int rollNumber,
              int age,
              string name,
              string branch,
              string fatherName,
              string motherName,
              string mobileNo)

      because both have exactly the same parameter types.

      C++ overload resolution only considers:
      (number of parameters + types + order)

      NOT parameter names.

      Therefore these two constructors have identical signatures
      and compilation will fail.
    */

    // =====================================================
    // Big constructor (All fields)
    // =====================================================
    Student(int rollNumber,
            int age,
            string name,
            string branch,
            string fatherName,
            string motherName,
            vector<string> subjects,
            string mobileNo,
            string emailId)
    {

        this->rollNumber = rollNumber;
        this->age = age;
        this->name = name;
        this->branch = branch;
        this->fatherName = fatherName;
        this->motherName = motherName;
        this->subjects = subjects;
        this->mobileNo = mobileNo;
        this->emailId = emailId;
    }

    // =====================================================
    // Print Student Details
    // =====================================================
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
        for (string subject : subjects)
            cout << subject << " ";
        cout << endl;

        cout << "Mobile No   : " << mobileNo << endl;
        cout << "Email Id    : " << emailId << endl;
    }
};

int main()
{

    // Only mandatory fields
    Student s1(101, 20, "Ashish", "CSE");

    // Mandatory + Father Name
    Student s2(102, 21, "Rahul", "IT", "Rajesh");

    // Mandatory + Father + Mother
    Student s3(103, 22, "Amit", "ECE", "Suresh", "Anita");

    // All fields
    Student s4(
        104,
        23,
        "Priya",
        "CSE",
        "Mahesh",
        "Sunita",
        {"DBMS", "OS", "CN"},
        "9876543210",
        "priya@gmail.com");

    s1.printDetails();
    s2.printDetails();
    s3.printDetails();
    s4.printDetails();

    return 0;
}

// Problems with this approach (Telescoping Constructors)
// Too many constructors as optional fields increase (constructor explosion).
// Constructors become difficult to read and maintain.
// Parameters of the same type (string) can easily be passed in the wrong order.
// Cannot overload constructors if they differ only by parameter names (e.g., mobileNo vs. emailId), because C++/Java overload resolution depends on parameter types and order, not names.
// Clients often have to pass dummy values or ""/nullptr for unused optional fields.
// Long constructors are hard to understand and use.
// If the class is immutable (all fields const/final), setters cannot be used, making construction even more cumbersome.
// These issues are exactly why the Builder Design Pattern is preferred for classes with many optional parameters.