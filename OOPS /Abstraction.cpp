#include <iostream>
using namespace std;

class Car
{
protected:
    string brand;
    string model;
    bool isEngineOne;
    int currentSpeed;
    int currentGear;
    string color;

public:
    Car(string b, string m) : brand(b), model(m), isEngineOne(false), currentSpeed(0), currentGear(0), color("blue") {}

    virtual void changeCarColor(string c) = 0;
    virtual string getCarColor() = 0;
    virtual void startEngine() = 0;
    virtual void shiftGear() = 0;
    virtual void accelerate() = 0;
    virtual void brake() = 0;
    virtual void stopEngine() = 0;
    virtual ~Car() {}
};

class SportsCar : public Car
{

public:
    // SportsCar(string b, string m) : Car(b, m) {}
    SportsCar(string b, string m) : Car(b, m)
    {
        // we can init current class data var or characters
    }

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

        if (currentGear == 0)
        {
            cout << brand << " " << model << " : " << "Pleae shift gear to accelerate" << endl;
            return;
        }

        currentSpeed += 20;
        cout << brand << " " << model << " : " << "Accelerating to " << currentSpeed << " KM/h" << endl;
    }

    void brake()
    {

        currentSpeed -= 20;
        if (currentSpeed < 0)
            currentSpeed = 0;

        cout << brand << " " << model << " : " << "Break Applied current speed is " << currentSpeed << endl;
    }

    void stopEngine()
    {
        currentSpeed = 0;
        currentGear = 0;
        isEngineOne = false;
        cout << brand << " " << model << " : " << "Engine turned off" << endl;
    }
};

int main()
{

    Car *car = new SportsCar("BMW", "M5");

    car->startEngine();
    car->shiftGear();
    car->accelerate();
    car->shiftGear();
    car->accelerate();
    car->brake();
    car->accelerate();
    car->stopEngine();

    cout << "Color is " << car->getCarColor() << endl;
    car->changeCarColor("red");
    cout << "Color is " << car->getCarColor() << endl;

    delete car;

    return 0;
}