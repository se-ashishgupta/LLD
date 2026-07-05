#include <iostream>
#include <mutex>
using namespace std;

class DBConnectionSynchronized
{
private:
    static DBConnectionSynchronized *instance;
    static mutex mtx; // Mutex for synchronization

    DBConnectionSynchronized() {} // Private constructor

public:
    static DBConnectionSynchronized *getInstance()
    {
        lock_guard<mutex> lock(mtx);
        if (instance == nullptr)
        {
            instance = new DBConnectionSynchronized(); // Thread-safe lazy initialization
        }
        return instance;
    }

    void displayMessage()
    {
        cout << "Thread-Safe/Synchronized Initialization Singleton Design Pattern" << endl;
    }
};

DBConnectionSynchronized *DBConnectionSynchronized::instance = nullptr; // Thread-safe lazy  initialization
mutex DBConnectionSynchronized::mtx;                                    // Mutex for synchronization

int main()
{
    cout << "Singleton Thread-Safe/Synchronized Initialization Design Pattern" << endl;

    DBConnectionSynchronized *dbConn = DBConnectionSynchronized::getInstance();
    DBConnectionSynchronized *dbConn2 = DBConnectionSynchronized::getInstance();

    dbConn->displayMessage();
    dbConn2->displayMessage();

    if (dbConn == dbConn2)
        cout << "Same Instance" << endl;
    else
        cout << "Different Instances" << endl;

    return 0;
}
// Every call to getInstance() acquires the lock.DBConnectionLazy::getInstance();
// DBConnectionLazy::getInstance();
// DBConnectionLazy::getInstance();
// DBConnectionLazy::getInstance();
// Even after the singleton is created, every call still locks and unlocks the mutex.That can become a performance bottleneck if getInstance () is called frequently.
