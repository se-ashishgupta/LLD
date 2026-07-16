#include <iostream>
using namespace std;

class AirConditioner
{

private:
    bool isOn;
    int temp;

public:
    void turnOn()
    {
        this->isOn = true;
        cout << "AC is on" << endl;
    }

    void turnOff()
    {
        this->isOn = false;
        cout << "AC is off" << endl;
    }

    void setTemperature(int temp)
    {
        this->temp = temp;
        cout << "Ac temperature set to: " << temp << endl;
    }
};

class Bulb
{
private:
    bool isOn;

public:
    void turnOn()
    {
        this->isOn = true;
        cout << "Bulb is on" << endl;
    }

    void turnOff()
    {
        this->isOn = false;
        cout << "Bulb is off" << endl;
    }
};

int main()
{
    cout << "Command Design Pattern: Problem" << endl;

    // Device: AC
    AirConditioner *ac = new AirConditioner();
    ac->turnOn();
    ac->setTemperature(25);
    ac->turnOff();

    // Device: Bulb
    Bulb *bulb = new Bulb();
    bulb->turnOn();
    bulb->turnOff();

    return 0;
}

// The problems with the above implementation are:
// 1. Lack of Abstraction: The remote control is directly dependent on specific device classes. Tomorrow, when we want
// to scale to a smart controller by adding new devices, we will need to modify the remote control code. This will lead
// to more redundant code, which is not a good design practice.

// 2. Undo/Redo Functionality: What if we want to add the undo/redo capability? How it will be handled. If we provide
// the implementation in client code (without command objects storing previous state), implementing undo becomes
// clumsy, requiring the invoker to track state for all possible operations.

// 3. Difficulty in Code Maintenance: What if in the future, we have to support more commands for more devices
// example Bulb. Supporting multiple device types leads to complex, monolithic, bloated remote control classes,
// leading to violation of SOLID Principles and difficulty in Testing.

// Without this pattern, you end up with tightly coupled, inflexible code that's hard to maintain, test, and extend.