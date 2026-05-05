#include <iostream>
#include <memory>
using namespace std;

class BasePizza
{
public:
    virtual string getDescription() = 0;
    virtual double getCost() = 0;

    virtual ~BasePizza() = default;
};

class PlainPizza : public BasePizza
{
public:
    string getDescription() override
    {
        return "Plain Pizza";
    }

    double getCost() override
    {
        return 100.00;
    }
};

class FarmHousePizza : public BasePizza
{
public:
    string getDescription() override
    {
        return "FormHouse Pizza";
    }

    double getCost() override
    {
        return 300.00;
    }
};

// You can add more pizza type class

class ToppingDecorator : public BasePizza
{
protected:
    shared_ptr<BasePizza> pizza;

public:
    ToppingDecorator(shared_ptr<BasePizza> base) : pizza(base) {}
};

class ExtraCheeseTopping : public ToppingDecorator
{
public:
    ExtraCheeseTopping(shared_ptr<BasePizza> base) : ToppingDecorator(base) {}

    string getDescription()
    {
        return pizza->getDescription() + " + Extra Cheese";
    }

    double getCost()
    {
        return pizza->getCost() + 10;
    }
};

class VeggiesTopping : public ToppingDecorator
{
public:
    VeggiesTopping(shared_ptr<BasePizza> base) : ToppingDecorator(base) {}
    string getDescription()
    {
        return pizza->getDescription() + " + Veggies";
    }

    double getCost()
    {
        return pizza->getCost() + 20;
    }
};

class MushroomTopping : public ToppingDecorator
{
public:
    MushroomTopping(shared_ptr<BasePizza> base) : ToppingDecorator(base) {}
    string getDescription()
    {
        return pizza->getDescription() + " + Mushroom";
    }

    double getCost()
    {
        return pizza->getCost() + 50;
    }
};

// You can ad more toppings

int main()
{
    auto farmPizza = make_shared<FarmHousePizza>();
    cout << farmPizza->getDescription() << " Rs. " << farmPizza->getCost() << endl;

    auto extraCheesePizza = make_shared<ExtraCheeseTopping>(farmPizza);
    cout << extraCheesePizza->getDescription() << " Rs. " << extraCheesePizza->getCost() << endl;

    auto extraMushrromPizza = make_shared<MushroomTopping>(extraCheesePizza);
    cout << extraMushrromPizza->getDescription() << " Rs. " << extraMushrromPizza->getCost() << endl;

    return 0;
}