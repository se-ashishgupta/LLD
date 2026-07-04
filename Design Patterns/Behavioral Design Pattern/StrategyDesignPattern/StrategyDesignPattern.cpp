#include <iostream>
using namespace std;

// Drive Interface
class DriveStrategy
{
public:
    virtual void drive() = 0;
};

class NormalDriveStrategy : public DriveStrategy
{
public:
    void drive()
    {
        cout << "Speacial Drive Fucntionality" << endl;
    }
};

class SportsDriveStrategy : public DriveStrategy
{
public:
    void drive()
    {
        cout << "Sports Drive Fucntionality" << endl;
    }
};

class Vehical
{
private:
    DriveStrategy *driveObj;

public:
    Vehical(DriveStrategy *drive)
    {
        this->driveObj = drive;
    }

    void drive()
    {
        driveObj->drive();
    }

    ~Vehical()
    {
        delete driveObj;
    }
};

class SportVehical : public Vehical
{
public:
    SportVehical() : Vehical(new SportsDriveStrategy()) {}
};

class PassengerVehical : public Vehical
{
public:
    PassengerVehical() : Vehical(new NormalDriveStrategy()) {}
};

class OffRoadVehical : public Vehical
{
public:
    OffRoadVehical() : Vehical(new SportsDriveStrategy()) {}
};

class GoodsVehical : public Vehical
{
public:
    GoodsVehical() : Vehical(new NormalDriveStrategy()) {}
};

// Here Sports and OffRaod vehical need special drive capability and both have same code so its not reusable

int main()
{
    SportVehical sv;
    sv.drive();

    GoodsVehical goodv;
    goodv.drive();

    Vehical *vehical = new SportVehical();
    vehical->drive();

    delete vehical;
    vehical = new GoodsVehical();
    vehical->drive();

    return 0;

    return 0;
}