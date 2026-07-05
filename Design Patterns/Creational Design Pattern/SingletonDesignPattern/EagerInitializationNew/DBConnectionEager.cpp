#include "DBConnectionEager.h"
#include <iostream>
using namespace std;

// Object of DBConnectionEager is created at the time of class loading, so it is thread-safe and we don't need to use any synchronization mechanism.
// object is created before main() is called, so it is guaranteed to be created before any thread accesses it. This is the main advantage of eager initialization over lazy initialization.
// This line tells the compiler : "Allocate memory for instance and call its constructor."
DBConnectionEager DBConnectionEager::instance; // Eager initialization

int main()
{
    cout << "===== Eager Initialization Singleton =====" << endl;

    // Cannot create object directly
    // DBConnectionEager obj; // Compilation Error

    DBConnectionEager &obj1 = DBConnectionEager::getInstance();
    DBConnectionEager &obj2 = DBConnectionEager::getInstance();

    obj1.displayMessage();
    obj2.displayMessage();

    if (&obj1 == &obj2)
        cout << "Same Instance" << endl;
    else
        cout << "Different Instances" << endl;

    return 0;
}