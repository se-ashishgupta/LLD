#include <iostream>
#include <map>
#include <mutex>
#include <vector>
#include <memory>
#include <stdexcept>
#include <chrono>

using namespace std;

// ======================= VEHICLE TYPE =======================
enum class VehicleType
{
    TWO_WHEELER,
    FOUR_WHEELER
};

// ======================= VEHICLE =======================
class Vehicle
{
private:
    string vehicleNumber;
    VehicleType vehicleType;

public:
    Vehicle(const string &vehicleNumber, VehicleType vehicleType)
        : vehicleNumber(vehicleNumber), vehicleType(vehicleType) {}

    string getVehicleNumber() const { return vehicleNumber; }
    VehicleType getVehicleType() const { return vehicleType; }
};

// ======================= PARKING SPOT =======================
class ParkingSpot
{
private:
    string spotId;
    bool free;

public:
    ParkingSpot(const string &spotId)
        : spotId(spotId), free(true) {}

    bool isSpotFree() const { return free; }
    void occupySpot() { free = false; }
    void releaseSpot() { free = true; }
    string getSpotId() const { return spotId; }
};

// ======================= PARKING SPOT LOOKUP STRATEGY =======================
class ParkingSpotLookupStrategy
{
public:
    virtual ParkingSpot *selectSpot(vector<ParkingSpot *> &spots) = 0;
    virtual ~ParkingSpotLookupStrategy() = default;
};

// Scans sequentially — first free spot wins (simple & predictable for interviews)
class SequentialSpotLookupStrategy : public ParkingSpotLookupStrategy
{
public:
    ParkingSpot *selectSpot(vector<ParkingSpot *> &spots) override
    {
        for (ParkingSpot *spot : spots)
        {
            if (spot->isSpotFree())
                return spot;
        }
        return nullptr;
    }
};

// Nearest to entry gate: same as sequential when spots are ordered by proximity
class NearestToEntryGateLookupStrategy : public ParkingSpotLookupStrategy
{
public:
    // Assumes spots vector is pre-ordered from nearest to farthest from entry gate
    ParkingSpot *selectSpot(vector<ParkingSpot *> &spots) override
    {
        for (ParkingSpot *spot : spots)
        {
            if (spot->isSpotFree())
                return spot;
        }
        return nullptr;
    }
};

// ======================= PARKING SPOT MANAGER =======================
class ParkingSpotManager
{
private:
    vector<ParkingSpot *> spots;
    ParkingSpotLookupStrategy *strategy;
    mutex mtx;

public:
    ParkingSpotManager(vector<ParkingSpot *> spots, ParkingSpotLookupStrategy *strategy)
        : spots(spots), strategy(strategy) {}

    virtual ~ParkingSpotManager() = default;

    ParkingSpot *park()
    {
        lock_guard<mutex> lock(mtx);
        ParkingSpot *spot = strategy->selectSpot(spots);
        if (spot == nullptr)
            return nullptr;
        spot->occupySpot();
        return spot;
    }

    void unPark(ParkingSpot *spot)
    {
        lock_guard<mutex> lock(mtx);
        if (spot == nullptr)
        {
            cout << "[WARNING] Attempted to unpark a null spot." << endl;
            return;
        }
        spot->releaseSpot();
    }

    bool hasFreeSpot()
    {
        lock_guard<mutex> lock(mtx);
        for (ParkingSpot *spot : spots)
        {
            if (spot->isSpotFree())
                return true;
        }
        return false;
    }
};

class TwoWheelerSpotManager : public ParkingSpotManager
{
public:
    TwoWheelerSpotManager(vector<ParkingSpot *> spots, ParkingSpotLookupStrategy *strategy)
        : ParkingSpotManager(spots, strategy) {}
};

class FourWheelerSpotManager : public ParkingSpotManager
{
public:
    FourWheelerSpotManager(vector<ParkingSpot *> spots, ParkingSpotLookupStrategy *strategy)
        : ParkingSpotManager(spots, strategy) {}
};

// ======================= PAYMENT =======================
class Payment
{
public:
    virtual bool pay(double amount) = 0;
    virtual ~Payment() = default;
};

class UPIPayment : public Payment
{
public:
    bool pay(double amount) override
    {
        cout << "[PAYMENT] Paid Rs " << amount << " via UPI." << endl;
        return true;
    }
};

class CashPayment : public Payment
{
public:
    bool pay(double amount) override
    {
        cout << "[PAYMENT] Paid Rs " << amount << " via Cash." << endl;
        return true;
    }
};

class CardPayment : public Payment
{
public:
    bool pay(double amount) override
    {
        cout << "[PAYMENT] Paid Rs " << amount << " via Card." << endl;
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
        : levelNumber(levelNumber), managers(managers) {}

    bool hasAvailability(VehicleType type)
    {
        auto it = managers.find(type);
        return it != managers.end() && it->second->hasFreeSpot();
    }

    ParkingSpot *park(VehicleType type)
    {
        auto it = managers.find(type);
        if (it == managers.end() || it->second == nullptr)
            throw invalid_argument("No parking manager found for this vehicle type.");
        return it->second->park();
    }

    void unPark(VehicleType type, ParkingSpot *spot)
    {
        auto it = managers.find(type);
        if (it != managers.end() && it->second != nullptr)
            it->second->unPark(spot);
    }

    int getLevelNumber() const { return levelNumber; }
};

// ======================= TICKET =======================
class Ticket
{
private:
    Vehicle *vehicle;
    ParkingLevel *level;
    ParkingSpot *spot;
    chrono::system_clock::time_point entryTime;

public:
    Ticket(Vehicle *vehicle, ParkingLevel *level, ParkingSpot *spot)
        : vehicle(vehicle), level(level), spot(spot),
          entryTime(chrono::system_clock::now()) {}

    Vehicle *getVehicle() const { return vehicle; }
    ParkingLevel *getLevel() const { return level; }
    ParkingSpot *getSpot() const { return spot; }
    chrono::system_clock::time_point getEntryTime() const { return entryTime; }
};

// ======================= PRICING STRATEGY =======================
class PricingStrategy
{
public:
    virtual double calculate(Ticket *ticket) = 0;
    virtual ~PricingStrategy() = default;
};

class FixedPricingStrategy : public PricingStrategy
{
private:
    double fixedRate;

public:
    FixedPricingStrategy(double rate = 50.0) : fixedRate(rate) {}

    double calculate(Ticket *ticket) override
    {
        return fixedRate;
    }
};

class HourlyPricingStrategy : public PricingStrategy
{
private:
    double ratePerHour;

public:
    HourlyPricingStrategy(double ratePerHour = 30.0) : ratePerHour(ratePerHour) {}

    double calculate(Ticket *ticket) override
    {
        auto now = chrono::system_clock::now();
        long long duration = chrono::duration_cast<chrono::hours>(now - ticket->getEntryTime()).count();
        long long hours = max(1LL, duration); // minimum 1 hour charge
        return hours * ratePerHour;
    }
};

// ======================= COST COMPUTATION =======================
class CostComputation
{
private:
    PricingStrategy *pricingStrategy;

public:
    CostComputation(PricingStrategy *pricingStrategy)
        : pricingStrategy(pricingStrategy) {}

    double compute(Ticket *ticket)
    {
        return pricingStrategy->calculate(ticket);
    }
};

// ======================= PARKING BUILDING =======================
class ParkingBuilding
{
private:
    vector<ParkingLevel *> levels;
    CostComputation *costComputation;

public:
    ParkingBuilding(vector<ParkingLevel *> levels, CostComputation *costComputation)
        : levels(levels), costComputation(costComputation) {}

    Ticket *allocate(Vehicle *vehicle)
    {
        for (ParkingLevel *level : levels)
        {
            if (level->hasAvailability(vehicle->getVehicleType()))
            {
                ParkingSpot *spot = level->park(vehicle->getVehicleType());
                if (spot != nullptr)
                {
                    Ticket *ticket = new Ticket(vehicle, level, spot);
                    cout << "[ENTRY] Vehicle " << vehicle->getVehicleNumber()
                         << " parked at Level " << level->getLevelNumber()
                         << ", Spot " << spot->getSpotId() << endl;
                    return ticket;
                }
            }
        }
        throw runtime_error("Parking is full. Cannot allocate spot.");
    }

    void release(Ticket *ticket)
    {
        ticket->getLevel()->unPark(
            ticket->getVehicle()->getVehicleType(),
            ticket->getSpot());
    }
};

// ======================= ENTRANCE GATE =======================
class EntranceGate
{
public:
    Ticket *enter(ParkingBuilding *building, Vehicle *vehicle)
    {
        return building->allocate(vehicle);
    }
};

// ======================= EXIT GATE =======================
class ExitGate
{
private:
    CostComputation *costComputation;

public:
    ExitGate(CostComputation *costComputation)
        : costComputation(costComputation) {}

    void completeExit(ParkingBuilding *building, Ticket *ticket, Payment *payment)
    {
        double amount = costComputation->compute(ticket);
        cout << "[EXIT] Amount due for vehicle "
             << ticket->getVehicle()->getVehicleNumber()
             << ": Rs " << amount << endl;

        bool success = payment->pay(amount);
        if (!success)
            throw runtime_error("Payment failed. Exit denied.");

        building->release(ticket);
        cout << "[EXIT] Gate opened. Have a safe journey!" << endl;
    }

    double calculatePrice(Ticket *ticket)
    {
        return costComputation->compute(ticket);
    }
};

// ======================= PARKING LOT (Facade) =======================
class ParkingLot
{
private:
    ParkingBuilding *building;
    EntranceGate *entranceGate;
    ExitGate *exitGate;

public:
    ParkingLot(ParkingBuilding *building, EntranceGate *entranceGate, ExitGate *exitGate)
        : building(building), entranceGate(entranceGate), exitGate(exitGate) {}

    Ticket *vehicleArrives(Vehicle *vehicle)
    {
        return entranceGate->enter(building, vehicle);
    }

    void vehicleExits(Ticket *ticket, Payment *payment)
    {
        exitGate->completeExit(building, ticket, payment);
    }
};

// ======================= MAIN =======================
int main()
{
    ParkingSpotLookupStrategy *strategy = new SequentialSpotLookupStrategy();

    // --- Level 1 Setup ---
    map<VehicleType, ParkingSpotManager *> levelOneManagers;
    levelOneManagers[VehicleType::TWO_WHEELER] = new TwoWheelerSpotManager(
        {new ParkingSpot("L1-2W-S1"), new ParkingSpot("L1-2W-S2")}, strategy);
    levelOneManagers[VehicleType::FOUR_WHEELER] = new FourWheelerSpotManager(
        {new ParkingSpot("L1-4W-S1"), new ParkingSpot("L1-4W-S2")}, strategy);

    ParkingLevel *level1 = new ParkingLevel(1, levelOneManagers);

    // --- Level 2 Setup ---
    map<VehicleType, ParkingSpotManager *> levelTwoManagers;
    levelTwoManagers[VehicleType::TWO_WHEELER] = new TwoWheelerSpotManager(
        {new ParkingSpot("L2-2W-S1")}, strategy);
    levelTwoManagers[VehicleType::FOUR_WHEELER] = new FourWheelerSpotManager(
        {new ParkingSpot("L2-4W-S1"), new ParkingSpot("L2-4W-S2")}, strategy);

    ParkingLevel *level2 = new ParkingLevel(2, levelTwoManagers);

    // --- Pricing & Cost ---
    PricingStrategy *pricingStrategy = new FixedPricingStrategy(50.0);
    CostComputation *costComputation = new CostComputation(pricingStrategy);

    // --- Building & Gates ---
    ParkingBuilding *building = new ParkingBuilding({level1, level2}, costComputation);
    EntranceGate *entranceGate = new EntranceGate();
    ExitGate *exitGate = new ExitGate(costComputation);

    ParkingLot *parkingLot = new ParkingLot(building, entranceGate, exitGate);

    // --- Simulation ---
    cout << "\n===== PARKING LOT SIMULATION =====" << endl;

    Vehicle *bike1 = new Vehicle("BIKE-101", VehicleType::TWO_WHEELER);
    Vehicle *bike2 = new Vehicle("BIKE-202", VehicleType::TWO_WHEELER);
    Vehicle *car1 = new Vehicle("CAR-303", VehicleType::FOUR_WHEELER);
    Vehicle *car2 = new Vehicle("CAR-404", VehicleType::FOUR_WHEELER);
    Vehicle *car3 = new Vehicle("CAR-505", VehicleType::FOUR_WHEELER);

    cout << "\n-- Vehicles Arriving --" << endl;
    Ticket *t1 = parkingLot->vehicleArrives(bike1);
    Ticket *t2 = parkingLot->vehicleArrives(bike2);
    Ticket *t3 = parkingLot->vehicleArrives(car1);
    Ticket *t4 = parkingLot->vehicleArrives(car2);
    Ticket *t5 = parkingLot->vehicleArrives(car3);

    cout << "\n-- Vehicles Exiting --" << endl;
    parkingLot->vehicleExits(t1, new CashPayment());
    parkingLot->vehicleExits(t2, new UPIPayment());
    parkingLot->vehicleExits(t3, new CardPayment());
    parkingLot->vehicleExits(t4, new UPIPayment());
    parkingLot->vehicleExits(t5, new UPIPayment());

    cout << "\n===== SIMULATION COMPLETE =====" << endl;

    return 0;
}