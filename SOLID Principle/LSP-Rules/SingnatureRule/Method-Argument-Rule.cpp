#include <iostream>
using namespace std;

// Method Argument Rule: Subtypes must accept the same arguments as their supertypes. This means that if a method in a superclass accepts certain parameters, the corresponding method in the subclass should also accept those parameters.
// C++ imposes this rule through function overriding. When a subclass overrides a method from its superclass, it must have the same parameter list (or be compatible with it) to ensure that the subclass can be used in place of the superclass without causing issues.

class Parent
{
public:
    virtual void display(int x)
    {
        cout << "Parent: " << x << endl;
    }
};

class Child : public Parent
{
public:
    // This method correctly overrides the Parent's display method, accepting the same argument.
    void display(int x) override
    {
        cout << "Child: " << x << endl;
    }
};

class Client
{
private:
    Parent *p;

public:
    Client(Parent *parent) : p(parent) {}

    void execute()
    {
        p->display(10); // This will work correctly whether p is a Parent or a Child, demonstrating the Method Argument Rule.
    }
};

int main()
{
    Parent parent;
    Child child;

    Client client1(&parent);
    Client client2(&child);

    client1.execute(); // Output: Parent: 10
    client2.execute(); // Output: Child: 10

    return 0;
}