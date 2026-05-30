#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <mutex>
#include <optional>
#include <algorithm>

using namespace std;

enum class VehicleType
{
    FOUR_WHEELER,
    TWO_WHEELER
};

enum class VehicleStatus
{
    AVAILABLE,
    BOOKED,
    MAINTENANCE
};

struct Date
{
    int year;
    int month;
    int day;

    bool operator<(const Date &other) const
    {
        if (year != other.year)
            return year < other.year;
        if (month != other.month)
            return month < other.month;
        return day < other.day;
    }

    bool operator<=(const Date &other) const
    {
        return (*this < other) || (*this == other);
    }

    bool operator==(const Date &other) const
    {
        return year == other.year &&
               month == other.month &&
               day == other.day;
    }
};

// ---------------- DateInterval ----------------

class DateInterval
{
private:
    Date from;
    Date to;

public:
    DateInterval(Date f, Date t) : from(f), to(t) {}

    bool overlaps(const DateInterval &other) const
    {
        return !(to < other.from || other.to < from);
    }
};

class Vehicle
{
private:
    int vehicleId;
    string vehicleNumber;
    VehicleType vehicleType;
    double dailyRentalCost;
    VehicleStatus vehicleStatus;

    /* we can add more properties like below if required
        private String companyName;
        private String modelName;
        private int kmDriven;
        private int average;
        private int cc;
        private int noOfSeat;
    */

public:
    Vehicle(int vehicleId, string vehicleNumber, VehicleType vehicleType, VehicleStatus vehicleStatu)
    {
        this->vehicleId = vehicleId;
        this->vehicleNumber = vehicleNumber;
        this->vehicleType = vehicleType;
        this->vehicleStatus = VehicleStatus::AVAILABLE;
    }

    // Getters
    int getVehicleId()
    {
        return vehicleId;
    }

    VehicleType getVehicleType()
    {
        return vehicleType;
    }

    VehicleStatus getVehicleStatus()
    {
        return vehicleStatus;
    }

    double getDailyRentalCost()
    {
        return dailyRentalCost;
    }

    string getVehicleNumber()
    {
        return vehicleNumber;
    }

    // Setters
    void setDailyRentalCost(double dailyRentalCost)
    {
        this->dailyRentalCost = dailyRentalCost;
    }

    void setStatus(VehicleStatus vehicleStatus)
    {
        this->vehicleStatus = vehicleStatus;
    }
};

// We can use startegy pattern to extend if car or bike want some specific data or method;

enum class ReservationType
{
    HOURLY,
    DAILY
};

enum class ReservationStatus
{
    SCHEDULED,
    IN_USE,
    COMPLETED,
    CANCELLED
};

class Reservation
{
private:
    int reservationId;
    int vehicleId;
    int userId;
    Date bookedFrom;
    Date bookedTo;
    ReservationStatus reservationStatus;
    ReservationType reservationType;

public:
    Reservation(int id, int vehicleId, int userId, Date from, Date to, ReservationType type)
    {
        this->userId = userId;
        this->reservationId = id;
        this->vehicleId = vehicleId;
        this->bookedFrom = from;
        this->bookedTo = to;
        this->reservationType = type;
        this->reservationStatus = ReservationStatus::SCHEDULED;
    }

    int getReservationID() const
    {
        return reservationId;
    }

    int getVehicleId() const
    {
        return vehicleId;
    }

    int getUserId() const
    {
        return userId;
    }

    Date getDateBookedFrom() const
    {
        return bookedFrom;
    }

    Date getDateBookedTo() const
    {
        return bookedTo;
    }

    ReservationType getReservationType()
    {
        return reservationType;
    }

    ReservationStatus getReservationStatus()
    {
        return reservationStatus;
    }

    void setReservationStatus(ReservationStatus status)
    {
        this->reservationStatus = status;
    }
};

class ReservationRepository
{
private:
    // reservationId -> Reservation
    unordered_map<int, shared_ptr<Reservation>> reservations;

public:
    // Save or Update
    void save(shared_ptr<Reservation> reservation)
    {
        reservations[reservation->getReservationID()] = reservation;
    }

    // Find by ID
    shared_ptr<Reservation> findById(int reservationId)
    {
        auto it = reservations.find(reservationId);

        if (it == reservations.end())
            return nullptr;

        return it->second;
    }

    // Remove
    void remove(int reservationId)
    {
        reservations.erase(reservationId);
    }

    // Get All
    const unordered_map<int, shared_ptr<Reservation>> &getAll() const
    {
        return reservations;
    }
};

class VehicleInventoryManager
{
private:
    // vehicleId -> Vehicle
    unordered_map<int, shared_ptr<Vehicle>> vehicles;

    // vehicleId -> reserveationId
    unordered_map<int, vector<int>> vehicleBookingIds;

    // vehicleId -> mutex
    unordered_map<int, unique_ptr<mutex>> vehicleLocks;

    ReservationRepository *rservationRepository = nullptr;

    mutex globalMutex;

    mutex &lockForVehicle(int vehicleId)
    {
        lock_guard<mutex> guard(globalMutex);

        if (vehicleLocks.find(vehicleId) == vehicleLocks.end())
        {
            vehicleLocks[vehicleId] = make_unique<mutex>();
        }

        return *vehicleLocks[vehicleId];
    }

public:
    void addVehicle(shared_ptr<Vehicle> vehicle)
    {
        vehicles[vehicle->getVehicleId()] = vehicle;
    }
};