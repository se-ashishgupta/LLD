#include <iostream>
using namespace std;

class DBConnectionLazy
{
private:
    static DBConnectionLazy *instance;

    DBConnectionLazy() {} // Private constructor

public:
    static DBConnectionLazy *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new DBConnectionLazy(); // Lazy initialization
        }
        return instance;
    }

    void displayMessage()
    {
        cout << "Lazy Initialization Singleton Design Pattern" << endl;
    }
};

DBConnectionLazy *DBConnectionLazy::instance = nullptr; // Lazy initialization

int main()
{
    cout << "Singleton Lazy Initialization Design Pattern" << endl;

    DBConnectionLazy *dbConn = DBConnectionLazy::getInstance();
    DBConnectionLazy *dbConn2 = DBConnectionLazy::getInstance();

    dbConn->displayMessage();
    dbConn2->displayMessage();

    if (dbConn == dbConn2)
        cout << "Same Instance" << endl;
    else
        cout << "Different Instances" << endl;

    return 0;
}