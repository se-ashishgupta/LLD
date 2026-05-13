#include <iostream>
using namespace std;

// Step 1: Abstract Product interfaces - Define product families
class CarExterior
{
public:
    virtual void addExteriorComponents() = 0;

    virtual ~CarExterior() {}
};

class CarInterior
{
public:
    virtual void addInteriorComponents() = 0;
    virtual ~CarInterior() {}
};

// Step 2: Concrete Products for Economy Car Family
class EconomyCarExterior : public CarExterior
{
public:
    void addExteriorComponents() override
    {
        cout << "Adding basic exterior components for Economy Car" << endl;
    }
};

class EconomyCarInterior : public CarInterior
{
public:
    void addInteriorComponents() override
    {
        cout << "Adding basic interior components for Economy Car" << endl;
    }
};

// Step 3: Concrete Products for Luxory Car Family
class LuxuryCarExterior : public CarExterior
{
public:
    void addExteriorComponents() override
    {
        cout << "Adding basic exterior components for Luxury Car" << endl;
    }
};

class LuxuryCarInterior : public CarInterior
{
public:
    void addInteriorComponents() override
    {
        cout << "Adding basic interior components for Luxury Car" << endl;
    }
};

// Abstract Factory
// CarFactory HAS - A CarInterior
// CarFactory HAS - A CarExterior

class CarFactory
{
public:
    virtual CarInterior *createInterior() = 0;
    virtual CarExterior *createExterior() = 0;

    // Template method that uses all factory methods
    void produceCompleteVehical()
    {
        cout << "Starting complete vehical production" << endl;

        CarExterior *exterior = createExterior();
        CarInterior *interior = createInterior();

        interior->addInteriorComponents();
        exterior->addExteriorComponents();

        cout << "Vehical Porduction Complete" << endl;

        delete exterior;
        delete interior;
    }

    virtual ~CarFactory() {}
};

// EconomyCarFactory HAS - A EconomyCarInterior
// EconomyCarFactory HAS - A EconomyCarExterior

// Concrete Factory
class EconomyCarFactory : public CarFactory
{
public:
    CarInterior *createInterior() override
    {
        return new EconomyCarInterior();
    }

    CarExterior *createExterior() override
    {
        return new EconomyCarExterior();
    }
};

class LuxuryCarFactory : public CarFactory
{
public:
    CarInterior *createInterior() override
    {
        return new LuxuryCarInterior();
    }

    CarExterior *createExterior() override
    {
        return new LuxuryCarExterior();
    }
};

int main()
{
    CarFactory *economy = new EconomyCarFactory();
    economy->produceCompleteVehical();

    CarFactory *luxury = new LuxuryCarFactory();
    luxury->produceCompleteVehical();

    return 0;
}