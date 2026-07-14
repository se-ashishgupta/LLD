#include <iostream>
using namespace std;

class Sprites
{
public:
};

class IRobot
{
public:
    virtual void display(int x, int y) = 0;
};

class HumanoidRobot : public IRobot
{
    string type;
    Sprites *sprite;

public:
    HumanoidRobot(string t, Sprites *s) : type(t), sprite(s) {}

    string getType() { return type; }
    Sprites *getSprite() { return sprite; }

    void display(int x, int y) override
    {
        cout << "Displaying Humanoid Robot of type: " << type
             << " Coordinate: " << x << ", " << y << endl;
    }
};

class RoboticsDog : public IRobot
{
    string type;
    Sprites *sprite;

public:
    RoboticsDog(string t, Sprites *s) : type(t), sprite(s) {}

    string getType() { return type; }
    Sprites *getSprite() { return sprite; }

    void display(int x, int y) override
    {
        cout << "Displaying Robotics Dog of type: " << type
             << " Coordinate: " << x << ", " << y << endl;
    }
};

class RobotFactory
{
private:
    static unordered_map<string, IRobot *> robotMap;

public:
    RobotFactory() {}

    static IRobot *getRobot(string type)
    {
        if (robotMap.find(type) != robotMap.end())
        {
            return robotMap[type];
        }
        else
        {
            if (type == "Humanoid")
            {
                Sprites *sprite = new Sprites(); // Load sprite for Humanoid robot
                IRobot *robot = new HumanoidRobot(type, sprite);
                robotMap[type] = robot;
                return robot;
            }
            else if (type == "Robotics_Dogs")
            {
                Sprites *sprite = new Sprites(); // Load sprite for Robotics Dog
                IRobot *robot = new RoboticsDog(type, sprite);
                robotMap[type] = robot;
                return robot;
            }
        }

        return nullptr;
    }
};

unordered_map<string, IRobot *> RobotFactory::robotMap;

int main()
{
    cout << "===== Robotic Game Issue - Flyweight Pattern =====" << endl;
    int x = 0, y = 0;

    IRobot *robot = RobotFactory::getRobot("Humanoid");
    robot->display(x, y);

    IRobot *robot1 = RobotFactory::getRobot("Humanoid");
    robot1->display(++x, ++y);

    IRobot *robot2 = RobotFactory::getRobot("Robotics_Dogs");
    robot2->display(++x, ++y);

    IRobot *robot3 = RobotFactory::getRobot("Robotics_Dogs");
    robot3->display(++x, ++y);

    return 0;
}