#include <iostream>
using namespace std;

class DBConnectionEager
{
private:
    static DBConnectionEager *instance;

    DBConnectionEager() {} // Private constructor

public:
    static DBConnectionEager *getInstance()
    {
        return instance;
    }

    void displayMessage()
    {
        cout << "Eager Initialization Singleton Design Pattern" << endl;
    }
};

DBConnectionEager *DBConnectionEager::instance = new DBConnectionEager(); // Eager initialization

int main()
{
    cout << "Singleton Eager Initialization Design Pattern" << endl;

    DBConnectionEager *dbConn = DBConnectionEager::getInstance();
    DBConnectionEager *dbConn2 = DBConnectionEager::getInstance();

    dbConn->displayMessage();
    dbConn2->displayMessage();

    if (dbConn == dbConn2)
        cout << "Same Instance" << endl;
    else
        cout << "Different Instances" << endl;

    return 0;
}