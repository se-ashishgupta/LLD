#include <iostream>
using namespace std;

// LivingThing interface
class LivingThing
{
public:
    virtual void breathe() = 0;
};

class Dog : public LivingThing
{
public:
    void breathe() override
    {
        cout << "Dog: Breathe through its nose; Lives on land: Respiratory system: 2 Lungs" << endl;
        cout << "Breathing Process: Inhales Oxygen from the air and Exhales Carbon Dioxide" << endl;
    }
};

class Fish : public LivingThing
{
public:
    void breathe() override
    {
        cout << "Fish: Breathe through its gills; Lives in water: Respiratory system: 2 Gills" << endl;
        cout << "Breathing Process: Inhales Oxygen from the water and Exhales Carbon Dioxide" << endl;
    }
};

class Tree : public LivingThing
{
public:
    void breathe() override
    {
        cout << "Tree: Breathe through its leaves; Lives on land: Respiratory system: 2 Lungs" << endl;
        cout << "Breathing Process: Inhales Carbon Dioxide and Exhales Oxygen as a result of photosynthesis." << endl;
    }
};

int main()
{
    cout << "Bridge Design Pattern" << endl;

    LivingThing *dog = new Dog();
    dog->breathe();

    LivingThing *fish = new Fish();
    fish->breathe();

    LivingThing *tree = new Tree();
    tree->breathe();

    return 0;
}

// Problem: The problem with the above code is that it violates the Open/Closed Principle. If we want to add a new living thing, we have to modify the existing code, which is not ideal.
// Code deplication: The code for the breathing mechanism is duplicated across the different living things, which can lead to maintenance issues and inconsistencies in the future.
// Solution: To solve this problem, we can use the Bridge Design Pattern. We can create an abstract class for the breathing mechanism and then create concrete classes for each living thing that implement the breathing mechanism. This way, we can add new living things without modifying the existing code.