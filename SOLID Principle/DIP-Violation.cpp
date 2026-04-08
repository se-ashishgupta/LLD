#include <iostream>
using namespace std;

// Dependency Inversion Principle (DIP) states that high-level modules should not depend on low-level modules. Both should depend on abstractions (e.g., interfaces). Additionally, abstractions should not depend on details. Details (concrete implementations) should depend on abstractions.

class MySQLDatabase
{ // Low-level module
public:
    void saveToSQL(string data)
    {
        cout << "Executing SQL Query: INSERT INTO users VALUES('" << data << "');" << endl;
    }
};

class MongoDBDatabase
{ // Low-level module
public:
    void saveToMongo(string data)
    {
        cout << "Executing MongoDB Function: db.users.insert({name: '" << data << "'})" << endl;
    }
};

class UserService
{ // High-level module (Tightly coupled)
private:
    MySQLDatabase sqlDb;     // Direct dependency on MySQL
    MongoDBDatabase mongoDb; // Direct dependency on MongoDB

public:
    void storeUserToSQL(string user)
    {
        // MySQL-specific code
        sqlDb.saveToSQL(user);
    }

    void storeUserToMongo(string user)
    {
        // MongoDB-specific code
        mongoDb.saveToMongo(user);
    }
};

int main()
{
    UserService service;
    service.storeUserToSQL("Aditya");
    service.storeUserToMongo("Rohit");
}
