#include <iostream>
using namespace std;

class Vehical
{
public:
    virtual void drive() const
    {
        cout << "Normal Drive Fucntionality" << endl;
    }
};

class SportVehical : public Vehical
{
public:
    void drive() const override
    {
        cout << "Speacial Drive Fucntionality" << endl;
    }
};

class PassengerVehical : public Vehical
{
};

class OffRoadVehical : public Vehical
{
public:
    void drive() const override
    {
        cout << "Speacial Drive Fucntionality" << endl;
    }
};

class GoodsVehical : public Vehical
{
};

// Here Sports and OffRaod vehical need special drive capability and both have same code so its not reusable

int main()
{

    Vehical *vehical = new SportVehical();
    vehical->drive();

    delete vehical;
    vehical = new GoodsVehical();
    vehical->drive();

    return 0;
}