#include <iostream>
#include <map>
#include <mutex>
#include <chrono>

using namespace std;

// ======================= VEHICLE =======================
enum class VehicleType
{
    TWO_WHEELER,
    FOUR_WHELLER
};

class Vehicle
{
protected:
    string vehicleNumber;
    VehicleType vehicleType;

public:
    string getVehicleNumber()
    {
        return vehicleNumber;
    }

    VehicleType getVehicleType()
    {
        return vehicleType;
    }
};

// ======================= PARKING SPOT =======================
class ParkingSpot
{
private:
    string spotId;
    bool free;

public:
    bool isSpotFree()
    {
        return free;
    }

    void occupySpot()
    {
        free = false;
    }

    void relaseSpot()
    {
        free = true;
    }

    string getSpotId()
    {
        return spotId;
    }
};

// ======================= PARKING LOOKUP STRATEGY =======================
class ParkingSpotLookupStrategy
{
public:
    virtual ParkingSpot *selectSpot(vector<ParkingSpot *> &spots) = 0;
};

class RandomSpotLookupStrategy : public ParkingSpotLookupStrategy
{
public:
    ParkingSpot *selectSpot(vector<ParkingSpot *> &spots)
    {
        for (ParkingSpot *spot : spots)
        {
            if (spot->isSpotFree())
            {
                return spot;
            }
        }

        return nullptr;
    }
};

class NearestToEntryGateLookupStrategy : public ParkingSpotLookupStrategy
{
public:
};

// ======================= PARKING SPOT MANAGER =======================
class ParkingSpotManager
{
private:
    vector<ParkingSpot *> spots;
    ParkingSpotLookupStrategy *strategy;
    mutex mtx; // lock macahnism

public:
    ParkingSpotManager(vector<ParkingSpot *> spots, ParkingSpotLookupStrategy *strategy)
    {
        this->spots = spots;
        this->strategy = strategy;
    }

    ParkingSpot *park()
    {
        lock_guard<mutex> lock(mtx);

        ParkingSpot *spot = strategy->selectSpot(spots);

        if (spot == nullptr)
        {
            return nullptr;
        }

        spot->occupySpot();
        return spot;
    }

    virtual void unPark(ParkingSpot *spot)
    {
        lock_guard<mutex> lock(mtx);

        if (spot == nullptr)
        {
            cout << "Not Spot Founc" << endl;
        }

        spot->relaseSpot();
    }

    virtual bool hasFreeSport()
    {
        lock_guard<mutex> lock(mtx);
        for (ParkingSpot *spot : spots)
        {
            if (spot->isSpotFree())
            {
                return true;
            }
        }

        return false;
    }
};

class TwoWheelerSpotManager : public ParkingSpotManager
{
    // 1. Maintains a list of Four Wheeler Spots only
    //  2. Has its own lookup strategy
    //  3. Has its own lock, to avoid conflicts with other spot managers

public:
    TwoWheelerSpotManager(vector<ParkingSpot *> spots, ParkingSpotLookupStrategy *strategy) : ParkingSpotManager(spots, strategy) {}
};

class FourWheelerSpotManager : public ParkingSpotManager
{
    // 1. Maintains a list of Four Wheeler Spots only
    //  2. Has its own lookup strategy
    //  3. Has its own lock, to avoid conflicts with other spot managers
public:
    FourWheelerSpotManager(vector<ParkingSpot *> spots, ParkingSpotLookupStrategy *strategy) : ParkingSpotManager(spots, strategy) {}
};

// ======================= PAYMENT =======================
class Payment
{
public:
    virtual bool pay(double amount) = 0;
};

class UPIPayment : public Payment
{
public:
    bool pay(double amount)
    {
        cout << "Payment done via UPI: Rs " << amount << endl;
        return true;
    }
};

class CashPayment : public Payment
{
public:
    bool pay(double amount)
    {
        cout << "Payment done via Cash: Rs " << amount << endl;
        return true;
    }
};

// ======================= PARKING LEVEL =======================
class ParkingLevel
{
private:
    int levelNumber;
    map<VehicleType, ParkingSpotManager *> managers;

public:
    ParkingLevel(int levelNumber, map<VehicleType, ParkingSpotManager *> managers)
    {
        this->levelNumber = levelNumber;
        this->managers = managers;
    }

    bool hasAvailability(VehicleType type)
    {
        ParkingSpotManager *manager = managers[type];
        return manager != nullptr && manager->hasFreeSport();
    }

    ParkingSpot *park(VehicleType type)
    {
        ParkingSpotManager *manager = managers[type];
        if (manager == nullptr)
        {
            throw invalid_argument(
                "No parking manager found");
        }

        return manager->park();
    }

    void unPark(VehicleType type, ParkingSpot *spot)
    {
        ParkingSpotManager *manager = managers[type];

        if (manager != nullptr)
        {
            manager->unPark(spot);
        }
    }

    int getLevelNumber()
    {
        return levelNumber;
    }
};

// ======================= TICKET  =======================
class Ticket
{
private:
    Vehicle *vehicle;
    ParkingLevel *level;
    ParkingSpot *spot;
    chrono::system_clock::time_point entryTime;

public:
    Ticket(
        Vehicle *vehicle,
        ParkingLevel *level,
        ParkingSpot *spot)
    {
        this->vehicle = vehicle;
        this->level = level;
        this->spot = spot;
        this->entryTime =
            chrono::system_clock::now();
    }

    Vehicle *getVehicle()
    {
        return vehicle;
    }

    ParkingLevel *getLevel()
    {
        return level;
    }

    ParkingSpot *getSpot()
    {
        return spot;
    }

    chrono::system_clock::time_point getEntryTime()
    {
        return entryTime;
    }
};

// ======================= PRICING STRATEGY  =======================
class PricingStrategy
{
public:
    virtual double calculate(Ticket *ticket) = 0;
};

class FixedPricingStrategy : public PricingStrategy
{
public:
    double calculate(Ticket *ticket) override
    {
        return 100;
    };
};

// ======================= COST COMPUTATION  =======================
class CostComputation
{
private:
    PricingStrategy *pricingStrategy;

public:
    CostComputation(PricingStrategy *pricingStrategy)
    {
        this->pricingStrategy = pricingStrategy;
    }

    double compute(Ticket *ticket)
    {
        return pricingStrategy->calculate(ticket);
    }
};

// ======================= Parking Building  =======================
class ParkingBuilding
{
private:
    vector<ParkingLevel *> levels;

public:
    ParkingBuilding(vector<ParkingLevel *> levels)
    {
        this->levels = levels;
    }

    Ticket *allocate(Vehicle *vehical)
    {
        for (ParkingLevel *level : levels)
        {
            if (level->hasAvailability(vehical->getVehicleType()))
            {
                ParkingSpot *spot = level->park(vehical->getVehicleType());
                if (spot != nullptr)
                {
                    Ticket *ticket = new Ticket(vehical, level, spot);
                    cout << "Parking allocated at level: " << level->getLevelNumber() << " spot: " << spot->getSpotId() << endl;
                    return ticket;
                }
            }
        }
    }

    void release(Ticket *ticket)
    {
        ticket->getLevel()->unPark(
            ticket->getVehicle()->getVehicleType(),
            ticket->getSpot());
    }
};

// ======================= ENTRANCE GATE   =======================
class EntranceGate
{
public:
    Ticket *enter(ParkingBuilding *building, Vehicle *vehicle)
    {
        return building->allocate(vehicle);
    }
};

// ======================= EXIT GATE   =======================
class ExitGate
{
private:
    CostComputation *costComputation;

public:
    ExitGate(CostComputation *costComputation)
    {
        this->costComputation = costComputation;
    }

    void completeExit(ParkingBuilding *building, Ticket *ticket, Payment *payment)
    {
        double amount = costComputation->compute(ticket);

        bool success = payment->pay(amount);
        if (!success)
        {
            __throw_failure(
                "Payment failed. Exit denied");
        }

        building->release(ticket);
        cout << "Exit Successfull. Gate opened" << endl;
    }

    double calculatePrice(Ticket *ticket)
    {
        return costComputation->compute(ticket);
    }
};

int main()
{
    return 0;
}