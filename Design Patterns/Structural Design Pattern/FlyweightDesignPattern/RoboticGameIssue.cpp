#include <iostream>
using namespace std;

class Sprites
{
public:
    virtual void draw() = 0;
};

class Robot
{
    int coordinateX;
    int coordinateY;
    string type;
    Sprites *sprite;

public:
    Robot(int x, int y, string t, Sprites *s) : coordinateX(x), coordinateY(y), type(t), sprite(s) {}

    // getter and setter methods
    int getCoordinateX() { return coordinateX; }
    int getCoordinateY() { return coordinateY; }
    string getType() { return type; }
    Sprites *getSprite() { return sprite; }
};

int main()
{
    cout << "===== Robotic Game Issue =====" << endl;
    int x = 0, y = 0;

    for (int i = 0; i < 500000; i++)
    {
        Robot *robot = new Robot(x, y, "Humanoid", nullptr);
        x += 10;
        y += 10;
    }

    for (int i = 0; i < 500000; i++)
    {
        Robot *robot = new Robot(x, y, "Robotics_Dogs", nullptr);
        x += 10;
        y += 10;
    }

    // Takes a lot of memory because we are creating 1 million objects and each object has its own copy of the sprite.

    return 0;
}