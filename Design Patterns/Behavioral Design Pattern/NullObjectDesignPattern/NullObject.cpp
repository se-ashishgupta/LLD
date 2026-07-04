#include <iostream>
using namespace std;

class Vehicle
{
public:
    virtual int getTankCapacity() = 0;
    virtual int getSeatingCapacity() = 0;
    virtual ~Vehicle() = default;
};

class Car : public Vehicle
{
public:
    int getTankCapacity() override
    {
        return 40;
    }
    int getSeatingCapacity() override
    {
        return 5;
    }
};

class NullVehicle : public Vehicle
{
public:
    int getTankCapacity() override
    {
        return 0;
    }
    int getSeatingCapacity() override
    {
        return 0;
    }
};

class VehicleFactory
{
public:
    static Vehicle *getVehicleObject(string type)
    {
        if (type == "Car")
        {
            return new Car();
        }

        return new NullVehicle();
    }
};

int main()
{

    Vehicle *vehicle = VehicleFactory::getVehicleObject("Car");

    cout << "Tank Capacity: "
         << vehicle->getTankCapacity() << endl;

    cout << "Seating Capacity: "
         << vehicle->getSeatingCapacity() << endl;

    delete vehicle;

    return 0;
}