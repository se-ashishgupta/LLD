#include <iostream>
#include <mutex>

using namespace std;

enum class SeatCategory
{
    SILVER,
    GOLD,
    PLATINUM
};

enum class SeatStatus
{
    AVAILABLE,
    LOCKED,
    BOOKED
};

enum class City
{
    BANGALORE,
    DELHI
};

enum class PaymentStatus
{
    SUCCESS,
    FAILED
};

class Seat
{
private:
    int seatId;
    SeatCategory category;

public:
    Seat(int seatId, SeatCategory category)
    {
        this->seatId = seatId;
        this->category = category;
    }

    int getSeatId() const
    {
        return this->seatId;
    }
};

class Movie
{
private:
    string name;

public:
    Movie(string name)
    {
        this->name = name;
    }

    string getMovieName()
    {
        return this->name;
    }
};

class Show
{
private:
    shared_ptr<Movie> movie;
    string showDate;
    string startTime;

    unordered_map<int, SeatStatus> seatStatusMap;
    unordered_map<int, unique_ptr<mutex>> seatLocks;

public:
    Show(shared_ptr<Movie> movie, const Screen &screen, const string &date, const string &time)
    {
        this->movie = movie;
        this->showDate = date;
        this->startTime = time;

        for (const auto &seat : screen.getSeats())
        {
            int seatId = seat->getSeatId();

            seatStatusMap[seatId] = SeatStatus::AVAILABLE;
            seatLocks[seatId] = make_unique<mutex>();
        }
    }

    shared_ptr<Movie> getMovie() const
    {
        return movie;
    }

    string getShowDate() const
    {
        return showDate;
    }

    string getStartTime() const
    {
        return startTime;
    }

    bool lockSeats(const vector<int> &seatIds)
    {
        vector<int> sortedSeats = seatIds;

        // To avoid deadlock
        sort(sortedSeats.begin(), sortedSeats.end());

        vector<mutex *> acquiredLocks;

        try
        {
            // Phase 1: Acuire all locks
            for (int seatId : sortedSeats)
            {
                mutex *mtx = seatLocks[seatId].get();
                mtx->lock();
                acquiredLocks.push_back(mtx);
            }

            // Phase 2: Validate availability
            for (int seatdId : sortedSeats)
            {
                if (seatStatusMap[seatdId] != SeatStatus::AVAILABLE)
                {
                    return false;
                }
            }

            // Phase 3: Mark seats LOCKED
            for (int seatId : sortedSeats)
            {
                seatStatusMap[seatId] = SeatStatus::LOCKED;
            }

            return true;
        }
        catch (...)
        {
            // Release acquired locks
            for (mutex *mtx : acquiredLocks)
            {
                mtx->unlock();
            }

            throw;
        }

        // Release acquired locks
        for (mutex *mtx : acquiredLocks)
        {
            mtx->unlock();
        }
    }

    void confirmSeat(const vector<int> &seatIds)
    {
        for (int seatId : seatIds)
        {
            seatStatusMap[seatId] = SeatStatus::BOOKED;
        }
    }

    void releaseSeats(const vector<int> &seatIds)
    {
        for (int seatId : seatIds)
        {
            seatStatusMap[seatId] = SeatStatus::AVAILABLE;
        }
    }
};

class Screen
{
private:
    int screenId;
    vector<shared_ptr<Seat>> seats;

    // date->list of shoes
    unordered_map<string, vector<shared_ptr<Show>>> showsByDate;

public:
    Screen(int screenId, const vector<shared_ptr<Seat>> &seats)
    {
        this->screenId = screenId;
        this->seats = seats;
    }

    const vector<shared_ptr<Seat>> &getSeats() const
    {
        return this->seats;
    }

    void addShow(shared_ptr<Show> show)
    {
        showsByDate[show->getShowDate()].push_back(show);
    }

    vector<shared_ptr<Show>> getShows(const string &date) const
    {
        auto it = showsByDate.find(date);

        if (it != showsByDate.end())
        {
            return it->second;
        }

        return {};
    }
};

class Theater
{
private:
    string name;
    City city;
    vector<shared_ptr<Screen>> screens;
    // address info etc

public:
    Theater(string name, City city, vector<shared_ptr<Screen>> &screens)
    {
        this->name = name;
        this->city = city;
        this->screens = screens;
    }

    City getCity() const
    {
        return this->city;
    }

    string getName() const
    {
        return this->name;
    }

    vector<shared_ptr<Screen>> &getScreens()
    {
        return this->screens;
    }
};

class User
{
private:
    string userId;
    string name;

public:
    User(string userid, string name)
    {
        this->userId = userId;
        this->name = name;
    }
};

class Payment
{
private:
    static int counter;
    string paymentId;
    PaymentStatus status;

public:
    Payment(PaymentStatus status)
    {
        this->paymentId = "PAY_" + to_string(++counter);
        this->status = status;
    }

    string getPaymentId() const
    {
        return paymentId;
    }

    PaymentStatus getStatus() const
    {
        return status;
    }
};

int Payment::counter = 0;

class Booking
{
private:
    static int counter;
    string bookingId;
    User user;
};

int Booking::counter = 0;