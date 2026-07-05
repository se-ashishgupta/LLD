#include <iostream>
#include <mutex>
using namespace std;

class DBConnectionDoubleLocking
{
private:
    static DBConnectionDoubleLocking *instance;
    static mutex mtx; // Mutex for synchronization

    DBConnectionDoubleLocking() {} // Private constructor

public:
    static DBConnectionDoubleLocking *getInstance()
    {
        if (instance == nullptr)
        {
            lock_guard<mutex> lock(mtx);
            if (instance == nullptr)
            {
                instance = new DBConnectionDoubleLocking(); // Thread-safe lazy initialization with double locking
            }
        }
        return instance;
    }

    void displayMessage()
    {
        cout << "Double Locking Initialization Singleton Design Pattern" << endl;
    }
};

DBConnectionDoubleLocking *DBConnectionDoubleLocking::instance = nullptr; // Thread-safe lazy initialization
mutex DBConnectionDoubleLocking::mtx;                                     // Mutex for synchronization

int main()
{
    cout << "Singleton Double Locking Initialization Design Pattern" << endl;

    DBConnectionDoubleLocking *dbConn = DBConnectionDoubleLocking::getInstance();
    DBConnectionDoubleLocking *dbConn2 = DBConnectionDoubleLocking::getInstance();

    dbConn->displayMessage();
    dbConn2->displayMessage();

    if (dbConn == dbConn2)
        cout << "Same Instance" << endl;
    else
        cout << "Different Instances" << endl;

    return 0;
}