#pragma once
#include <iostream>
using namespace std;

class DBConnectionEager
{
private:
    static DBConnectionEager instance; // Eager initialization

    DBConnectionEager() // Private constructor
    {
        cout << "DBConnectionEager instance created." << endl;
    }

    // Prevent copy constructor - Nobody is allowed to copy this class. ex: DBConnectionEager obj1 = obj2;
    DBConnectionEager(const DBConnectionEager &) = delete;
    // Prevent assignment operator - Nobody is allowed to assign this class. ex: obj1 = obj2;
    DBConnectionEager &operator=(const DBConnectionEager &) = delete;

public:
    static DBConnectionEager &getInstance()
    {
        return instance;
    }

    void displayMessage()
    {
        cout << "Eager Initialization Singleton - " << this << endl;
    }
};