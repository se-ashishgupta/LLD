#include <iostream>
using namespace std;

// Bloated Element calss with mutltiple operation

class SuiteHotelRoom
{
private:
    string roomNumber;
    string numberOfRooms;

public:
    SuiteHotelRoom(string roomNumber, string numberOfRooms)
    {
        this->numberOfRooms = numberOfRooms;
        this->roomNumber = roomNumber;
    }

    void clean()
    {
        cout << "Housekeeping: Cleaning suite " << this->roomNumber << " with " << this->numberOfRooms << " rooms(90 minutes)" << endl;
    }

    void deliverRoomService(string orderDetails)
    {
        cout << "Room Service: VIP delivery of " << orderDetails << " to Suit " << this->roomNumber << " woth full dining" << endl;
    }

    double calculatePrice()
    {
        cout << "Pricing: Suite " << this->roomNumber << " - Rs. 2000/night" << endl;
        return 500.0;
    }

    // many more operation came here over time
};

int main()
{
    cout << "##### Visitor Pattern: Problem Demo #####" << endl;

    SuiteHotelRoom *suite = new SuiteHotelRoom("301", "2");
    suite->clean();
    suite->deliverRoomService("Breakfast");
    suite->calculatePrice();

    return 0;
}

// The Key Problems Without Visitor Pattern
// 1. Violates the Open / Closed Principle and the Single Responsibility Principle, making it unextensible.
// 2. Scattered Operation Logic leading to redundant code.
// 3. Difficult Testing
// 4. Tight coupling &Poor Reusability of code