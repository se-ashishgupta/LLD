#include <iostream>
using namespace std;

class Car
{
protected:
    string brand;
    string model;
    bool isEngineOne;
    int currentSpeed;
    string color;

public:
    Car(string b, string m) : brand(b), model(m), isEngineOne(false), currentSpeed(0), color("blue") {}

    void changeCarColor(string c) // setter method
    {
        color = c;
        cout << brand << " " << model << " : " << "Color changes to: " << color << endl;
    }

    string getCarColor() // getter method
    {
        return color;
    }

    void startEngine()
    {
        if (!isEngineOne)
        {
            isEngineOne = true;
            cout << brand << " " << model << " : " << "Car Started" << endl;
        }
        else
        {

            cout << brand << " " << model << " : " << "Engine already started" << endl;
        }
    }

    void stopEngine()
    {
        currentSpeed = 0;
        isEngineOne = false;
        cout << brand << " " << model << " : " << "Engine turned off" << endl;
    }

    virtual void accelerate() = 0; // Abstract method for dynamic polymorphism
    virtual void accelerate(int speed) = 0;
    virtual void brake() = 0;
    virtual ~Car() {}
};

class MannualCar : public Car
{
private:
    int currentGear;

public:
    MannualCar(string b, string n) : Car(b, n)
    {
        currentGear = 0;
    }

    void shiftGear()
    {

        if (!isEngineOne)
        {
            cout << brand << " " << model << " : " << "Pleae start engine first" << endl;
            return;
        }
        if (currentGear <= 5)
        {
            currentGear++;
            cout << brand << " " << model << " : " << "Gear Shited to: " << currentGear << endl;
        }
        else
        {
            cout << brand << " " << model << " : " << "All gear applied" << endl;
        }
    }

    void accelerate()
    {
        if (!isEngineOne)
        {
            cout << brand << " " << model << " : " << "Pleae start engine first" << endl;
            return;
        }

        currentSpeed += 20;
        cout << brand << " " << model << " : " << "Accelerating to " << currentSpeed << " KM/h" << endl;
    }

    void accelerate(int s)
    {
        if (!isEngineOne)
        {
            cout << brand << " " << model << " : " << "Pleae start engine first" << endl;
            return;
        }

        currentSpeed += s;
        cout << brand << " " << model << " : " << "Accelerating to " << currentSpeed << " KM/h" << endl;
    }

    void brake()
    {

        currentSpeed -= 20;
        if (currentSpeed < 0)
            currentSpeed = 0;

        cout << brand << " " << model << " : " << "Break Applied current speed is " << currentSpeed << endl;
    }
};

class ElectricCar : public Car
{
private:
    int batteryLevel;

public:
    ElectricCar(string b, string m) : Car(b, m)
    {
        batteryLevel = 100;
    }

    void chargeBattery()
    {
        batteryLevel = 100;
        cout << brand << " " << model << " : " << "Battery fully charged!" << endl;
    }

    void accelerate()
    {
        if (!isEngineOne)
        {
            cout << brand << " " << model << " : " << "Pleae start engine first" << endl;
            return;
        }

        if (batteryLevel <= 0)
        {
            cout << brand << " " << model << " : " << "Battery level is 0, Please charge the battery" << endl;
            return;
        }

        batteryLevel -= 10;
        currentSpeed += 15;
        cout << brand << " " << model << " : " << "Accelerating to " << currentSpeed << " KM/h" << endl;
    }
    void accelerate(int s)
    {
        if (!isEngineOne)
        {
            cout << brand << " " << model << " : " << "Pleae start engine first" << endl;
            return;
        }

        if (batteryLevel <= 0)
        {
            cout << brand << " " << model << " : " << "Battery level is 0, Please charge the battery" << endl;
            return;
        }

        batteryLevel -= 5 + s;
        currentSpeed += s;
        cout << brand << " " << model << " : " << "Accelerating to " << currentSpeed << " KM/h" << endl;
    }

    void brake()
    {

        currentSpeed -= 15;
        if (currentSpeed < 0)
            currentSpeed = 0;

        cout << brand << " " << model << " : " << "Break Applied current speed is " << currentSpeed << endl;
    }
};

int main()
{

    MannualCar *mannual = new MannualCar("BMW", "M5");

    mannual->startEngine();
    mannual->shiftGear();
    mannual->accelerate();
    mannual->accelerate(50);
    mannual->brake();
    mannual->accelerate();
    mannual->stopEngine();

    cout << "Color is " << mannual->getCarColor() << endl;
    mannual->changeCarColor("red");
    cout << "Color is " << mannual->getCarColor() << endl;

    ElectricCar *battery = new ElectricCar("Tata", "Harrier EV");

    battery->chargeBattery();
    battery->startEngine();
    battery->accelerate();
    battery->accelerate(10);
    battery->brake();
    battery->accelerate();
    battery->stopEngine();

    cout << "Color is " << battery->getCarColor() << endl;
    battery->changeCarColor("red");
    cout << "Color is " << battery->getCarColor() << endl;

    delete mannual;
    delete battery;

    return 0;
}