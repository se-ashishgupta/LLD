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

    bool isACOn()
    {
        return isOn;
    }

    void setOn(bool on)
    {
        this->isOn = on;
    }

    int getTemperature()
    {
        return temp;
    }

    void setTemperature(int temp)
    {
        this->temp = temp;
        cout << "Ac temperature set to: " << temp << endl;
    }
};

class ICommand
{
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class TurnOnCommand : public ICommand
{
private:
    AirConditioner *ac;
    bool prevState;

public:
    TurnOnCommand(AirConditioner *ac)
    {
        this->ac = ac;
    }

    void execute() override
    {
        prevState = ac->isACOn();
        ac->turnOn();
    }

    void undo() override
    {
        cout << "Undo: Turn On command." << endl;
        if (!prevState)
        {
            ac->turnOff();
        }
    }
};

class TurnOffCommand : public ICommand
{
private:
    AirConditioner *ac;
    bool prevState;

public:
    TurnOffCommand(AirConditioner *ac)
    {
        this->ac = ac;
    }

    void execute() override
    {
        prevState = ac->isACOn();
        ac->turnOff();
    }

    void undo() override
    {
        cout << "Undo: Turn Off command." << endl;
        if (prevState)
        {
            ac->turnOn();
        }
    }
};

class SetTemperatureCommand : public ICommand
{
private:
    AirConditioner *ac;
    int newTemp;
    int prevTemp;

public:
    SetTemperatureCommand(AirConditioner *ac, int newTemp)
    {
        this->ac = ac;
        this->newTemp = newTemp;
    }

    void execute() override
    {
        prevTemp = ac->getTemperature();
        ac->setTemperature(newTemp);
    }

    void undo() override
    {
        cout << "Undo: Set Temperature command." << endl;
        ac->setTemperature(prevTemp);
    }
};

class RemoteController
{
private:
    ICommand *cmd;
    stack<ICommand *> cmdHistory;

public:
    RemoteController() {}

    void setCommand(ICommand *cmd)
    {
        this->cmd = cmd;
    }

    void pressButton()
    {
        cmd->execute();
        cmdHistory.push(cmd);
    }

    void undo()
    {
        if (!cmdHistory.empty())
        {
            ICommand *lastCmd = cmdHistory.top();
            lastCmd->undo();
            cmdHistory.pop();
        }
    }
};

int main()
{
    cout << "Command Design Pattern: Solution" << endl;

    // Create Receiver: AC
    AirConditioner *ac = new AirConditioner();

    // Create Invoker
    RemoteController *remoteObj = new RemoteController();

    // Execute Command
    remoteObj->setCommand(new TurnOnCommand(ac));
    remoteObj->pressButton();

    remoteObj->setCommand(new SetTemperatureCommand(ac, 25));
    remoteObj->pressButton();

    remoteObj->setCommand(new SetTemperatureCommand(ac, 18));
    remoteObj->pressButton();

    remoteObj->setCommand(new TurnOffCommand(ac));
    remoteObj->pressButton();

    // Undo Command
    remoteObj->undo(); // Turn off command -> Ac is now ON

    remoteObj->undo(); // Undo: Set Temperature Command. AC temperature is now 25°C

    remoteObj->undo(); //  Undo: Set Temperature Command. AC temperature is now 0°C

    remoteObj->undo(); // Undo: Turn On command => AC is now off

    return 0;
}
