#include <iostream>
using namespace std;

class Employee
{
public:
    int id;
    string name;

    Employee(int id, string name)
        : id(id), name(name) {}
};

class EmployeeDao
{
public:
    virtual void getEmployeeInfo(int empID) = 0;
    virtual void createEmployee(const Employee &obj) = 0;

    virtual ~EmployeeDao() = default;
};

class EmployeeDaoImpl : public EmployeeDao
{
public:
    void getEmployeeInfo(int empID) override
    {
        cout << "Fetching employee info for ID: " << empID << endl;
    }

    void createEmployee(const Employee &obj) override
    {
        cout << "Creating Employee: " << obj.name << endl;
    }
};

class EmployeeDaoProxy : public EmployeeDao
{
private:
    unique_ptr<EmployeeDao> empDaoObj;
    string clientRole;

public:
    EmployeeDaoProxy(string role)
    {
        this->clientRole = role;
        empDaoObj = make_unique<EmployeeDaoImpl>();
    }

    void getEmployeeInfo(int empID) override
    {
        if (clientRole == "ADMIN" || clientRole == "USER")
        {
            empDaoObj->getEmployeeInfo(empID);
        }
        else
        {
            throw runtime_error("Access Denied");
        }
    }

    void createEmployee(const Employee &obj) override
    {
        if (clientRole == "ADMIN")
        {
            empDaoObj->createEmployee(obj);
        }
        else
        {
            throw runtime_error("Access Denied");
        }
    }
};

int main()
{

    cout << "::Proxy Design Pattern::" << endl;

    Employee emp(101, "Ashish");

    try
    {
        unique_ptr<EmployeeDao> userProxy = make_unique<EmployeeDaoProxy>("USER");

        userProxy->getEmployeeInfo(101);
        userProxy->createEmployee(emp);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    cout << "\n----------------------\n";

    try
    {
        unique_ptr<EmployeeDao> userProxy = make_unique<EmployeeDaoProxy>("ADMIN");

        userProxy->getEmployeeInfo(101);
        userProxy->createEmployee(emp);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}