#include <iostream>
using namespace std;

// Implementor interface
class BreathingProcess
{
public:
    virtual void breathe() = 0;
};

class GillsBreathingProcess : public BreathingProcess
{
public:
    void breathe() override
    {
        cout << "Breathing Process: Inhales Oxygen from the water and Exhales Carbon Dioxide" << endl;
    }
};

class LungsBreathingProcess : public BreathingProcess
{
public:
    void breathe() override
    {
        cout << "Breathing Process: Inhales Oxygen from the air and Exhales Carbon Dioxide" << endl;
    }
};

class PhotosynthesisBreathingProcess : public BreathingProcess
{
public:
    void breathe() override
    {
        cout << "Breathing Process: Inhales Carbon Dioxide and Exhales Oxygen as a result of photosynthesis." << endl;
    }
};

// Abstract class for LivingThing
class LivingThings
{
protected:
    BreathingProcess *breathingProcess;

public:
    LivingThings(BreathingProcess *breathingProcess) : breathingProcess(breathingProcess) {}
    virtual void breathe() = 0;
};

class Dog : public LivingThings
{
public:
    Dog(BreathingProcess *breathingProcess) : LivingThings(breathingProcess) {}
    void breathe() override
    {

        breathingProcess->breathe();
    }
};

class Fish : public LivingThings
{
public:
    Fish(BreathingProcess *breathingProcess) : LivingThings(breathingProcess) {}
    void breathe() override
    {
        breathingProcess->breathe();
    }
};

class Tree : public LivingThings
{
public:
    Tree(BreathingProcess *breathingProcess) : LivingThings(breathingProcess) {}
    void breathe() override
    {
        breathingProcess->breathe();
    }
};

int main()
{
    cout << "Bridge Design Pattern" << endl;

    LivingThings *dog = new Dog(new LungsBreathingProcess());
    LivingThings *fish = new Fish(new GillsBreathingProcess());
    LivingThings *tree = new Tree(new PhotosynthesisBreathingProcess());

    dog->breathe();
    fish->breathe();
    tree->breathe();

    return 0;
}