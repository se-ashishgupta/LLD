#include <iostream>
using namespace std;

// Condtional bassis pe jab hame object chiaye

class Shape
{
public:
    virtual void computeArea() = 0;
    virtual void draw() = 0;

    virtual ~Shape() {}
};

class Circle : public Shape
{
public:
    void computeArea() override
    {
        cout << "inside Circle computeArea() method" << endl;
    }

    void draw() override
    {
        cout << "inside Circle draw() method" << endl;
    }
};

class Rectangle : public Shape
{
public:
    void computeArea() override
    {
        cout << "inside Rectangle computeArea() method" << endl;
    }

    void draw() override
    {
        cout << "inside Rectangle draw() method" << endl;
    }
};

class Square : public Shape
{
public:
    void computeArea() override
    {
        cout << "inside Square computeArea() method" << endl;
    }

    void draw() override
    {
        cout << "inside Square draw() method" << endl;
    }
};

enum class ShapeType
{
    CIRCLE,
    RECTANGLE,
    SQUARE

};

// Simple Factory
class ShapeFactorySimple
{
public:
    static Shape *createShapeInstance(ShapeType type)
    {
        switch (type)
        {
        case ShapeType::CIRCLE:
            return new Circle();
        case ShapeType::RECTANGLE:
            return new Rectangle();
        case ShapeType::SQUARE:
            return new Square();
        default:
            return nullptr;
        }
    }
};

// Factory Method

// Abstract Class
class ShapeFactoryMethod
{
public:
    virtual Shape *createShape() = 0;

    virtual ~ShapeFactoryMethod() {}
};

// Concrete Class
class CircleFactory : public ShapeFactoryMethod
{
public:
    Shape *createShape() override
    {
        return new Circle();
    }
};

class SquareFactory : public ShapeFactoryMethod
{
public:
    Shape *createShape() override
    {
        return new Square();
    }
};

class RectangleFactory : public ShapeFactoryMethod
{
public:
    Shape *createShape() override
    {
        return new Rectangle();
    }
};

int main()
{

    // Simple factory
    // ShapeFactorySimple *shapeFactory = new ShapeFactorySimple();
    // Shape *shape = shapeFactory->createShapeInstance(ShapeType::CIRCLE);
    // shape->draw();

    // delete shape;
    // delete shapeFactory;

    // Factory Method
    ShapeFactoryMethod *factory = new CircleFactory();
    Shape *shape = factory->createShape();
    shape->draw();

    delete shape;
    delete factory;

    return 0;
}