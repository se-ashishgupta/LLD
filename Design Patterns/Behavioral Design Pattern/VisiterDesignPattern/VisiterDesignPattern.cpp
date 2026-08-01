#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Forward declarations
class StandardRoom;
class DeluxeRoom;
class SuiteRoom;

class IRoomVisitor
{
public:
    virtual void visitStandardRoom(StandardRoom *room) = 0;
    virtual void visitDeluxeRoom(DeluxeRoom *room) = 0;
    virtual void visitSuiteRoom(SuiteRoom *room) = 0;
    virtual ~IRoomVisitor() = default;
};

class IRoom
{
public:
    virtual void accept(IRoomVisitor *visitor) = 0;
    virtual ~IRoom() = default;
};

class StandardRoom : public IRoom
{
private:
    string roomNumber;

public:
    StandardRoom(string roomNumber)
    {
        this->roomNumber = roomNumber;
    }

    void accept(IRoomVisitor *visitor) override
    {
        visitor->visitStandardRoom(this);
    }

    string getRoomNumber()
    {
        return this->roomNumber;
    }
};

class DeluxeRoom : public IRoom
{
private:
    string roomNumber;
    bool jacuzzi;

public:
    DeluxeRoom(string roomNumber, bool jacuzzi)
    {
        this->roomNumber = roomNumber;
        this->jacuzzi = jacuzzi;
    }

    void accept(IRoomVisitor *visitor) override
    {
        visitor->visitDeluxeRoom(this);
    }

    string getRoomNumber()
    {
        return this->roomNumber;
    }

    bool hasJacuzzi()
    {
        return this->jacuzzi;
    }
};

class SuiteRoom : public IRoom
{
private:
    string roomNumber;
    int numberOfRooms;

public:
    SuiteRoom(string roomNumber, int numberOfRooms)
    {
        this->roomNumber = roomNumber;
        this->numberOfRooms = numberOfRooms;
    }

    void accept(IRoomVisitor *visitor) override
    {
        visitor->visitSuiteRoom(this);
    }

    string getRoomNumber()
    {
        return this->roomNumber;
    }

    int getNumberOfRooms()
    {
        return this->numberOfRooms;
    }
};

class HousekeepingVisitor : public IRoomVisitor
{
public:
    void visitStandardRoom(StandardRoom *room) override
    {
        cout << "Housekeeping: Cleaning standard room " << room->getRoomNumber() << " (30 minutes)" << endl;
    }

    void visitDeluxeRoom(DeluxeRoom *room) override
    {
        cout << "Housekeeping: Cleaning deluxe room " << room->getRoomNumber() << endl;
    }

    void visitSuiteRoom(SuiteRoom *room) override
    {

        cout << "Housekeeping: Cleaning suite " << room->getRoomNumber() << " with " << room->getNumberOfRooms() << " rooms (90 minutes)" << endl;
    }
};

class RoomServiceVisitor : public IRoomVisitor
{
private:
    string orderDetails;

public:
    RoomServiceVisitor(string orderDetails)
    {
        this->orderDetails = orderDetails;
    }

    void visitStandardRoom(StandardRoom *room) override
    {
        cout << "Room Service: Delivering " << this->orderDetails << " to the standard room " << room->getRoomNumber() << endl;
    }

    void visitDeluxeRoom(DeluxeRoom *room) override
    {
        cout << "Room Service: Delivering " << this->orderDetails << " to the delus room " << room->getRoomNumber() << endl;
    }

    void visitSuiteRoom(SuiteRoom *room) override
    {
        cout << "Room Service: Delivering " << this->orderDetails << " to the suite " << room->getRoomNumber() << endl;
    }
};

class PricingVisitor : public IRoomVisitor
{
private:
    double totalRevenue = 0;

public:
    void visitStandardRoom(StandardRoom *room) override
    {
        double price = 1000.0;
        this->totalRevenue += price;
        cout << "Pricing: Standard room " << room->getRoomNumber() << " - Rs. " << price << " /night" << endl;
    }

    void visitDeluxeRoom(DeluxeRoom *room) override
    {
        double price = 2000.0;
        this->totalRevenue += price;
        cout << "Pricing: Delus room " << room->getRoomNumber() << " - Rs. " << price << " /night" << endl;
    }

    void visitSuiteRoom(SuiteRoom *room) override
    {
        double price = 5000.0;
        this->totalRevenue += price;
        cout << "Pricing: Suite " << room->getRoomNumber() << " - Rs. " << price << " /night" << endl;
    }

    double getTotalRevenue()
    {
        return this->totalRevenue;
    }
};

int main()
{
    cout << "##### Visitor Pattern Demo #####" << endl;

    vector<IRoom *> rooms = {
        new StandardRoom("101"),
        new DeluxeRoom("201", true),
        new SuiteRoom("301", 3),
        new StandardRoom("102"),
        new DeluxeRoom("202", false)};

    // Calling visitor in elements
    cout << "HouseKeeping Service" << endl;
    IRoomVisitor *houseKeeping = new HousekeepingVisitor();
    for (IRoom *room : rooms)
    {
        room->accept(houseKeeping);
    }

    // Calling visitor in elements
    cout << "Room Service" << endl;
    IRoomVisitor *roomService = new RoomServiceVisitor("Breakfast");
    for (IRoom *room : rooms)
    {
        room->accept(roomService);
    }

    // Calling visitor in elements
    cout << "Revenue Calculator" << endl;
    PricingVisitor *revenue = new PricingVisitor();
    for (IRoom *room : rooms)
    {
        room->accept(revenue);
    }
    cout << "Total Revenue: Rs. " << revenue->getTotalRevenue() << endl;

    return 0;
}
