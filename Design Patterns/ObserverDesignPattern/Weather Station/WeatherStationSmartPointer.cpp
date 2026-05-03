#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>
#include <string>
using namespace std;

// Observer Interface
class WeatherObserver
{
public:
    virtual void update() = 0;
    virtual ~WeatherObserver() = default;
};

// Observable Interface
class WeatherObservable
{
public:
    virtual void addObserver(shared_ptr<WeatherObserver> observer) = 0;
    virtual void removeObserver(shared_ptr<WeatherObserver> observer) = 0;
    virtual void notifyObservers() = 0;
    virtual void setWeatherReadings(float temp, float humi, float pres) = 0;

    virtual ~WeatherObservable() = default;
};

class WeatherStation : public WeatherObservable
{
private:
    vector<weak_ptr<WeatherObserver>> observers;

    float temperature{};
    float humidity{};
    float pressure{};

public:
    void addObserver(shared_ptr<WeatherObserver> observer) override
    {
        observers.push_back(observer);
        cout << "[+] Observer registered\n";
    }

    void removeObserver(shared_ptr<WeatherObserver> observer) override
    {
        observers.erase(
            remove_if(observers.begin(), observers.end(),
                      [&](weak_ptr<WeatherObserver> &wptr)
                      {
                          auto sp = wptr.lock();
                          return !sp || sp == observer;
                      }),
            observers.end());
        cout << "[-] Observer removed\n";
    }

    void notifyObservers() override
    {
        // Clean expired observers while notifying
        observers.erase(
            remove_if(observers.begin(), observers.end(),
                      [](weak_ptr<WeatherObserver> &wptr)
                      {
                          return wptr.expired();
                      }),
            observers.end());

        for (auto &wptr : observers)
        {
            if (auto observer = wptr.lock())
            {
                observer->update();
            }
        }
    }

    void setWeatherReadings(float temp, float humi, float pres) override
    {
        temperature = temp;
        humidity = humi;
        pressure = pres;

        notifyObservers();
    }

    // Getters
    float getTemperature()
    {
        return temperature;
    }
    float getHumidity()
    {
        return humidity;
    }
    float getPressure()
    {
        return pressure;
    }

    string toString() const
    {
        return "Temp= " + to_string(temperature) + " Himidity= " + to_string(humidity) +
               " Pressure= " + to_string(pressure);
    }
};

class CurrentConditionsDisplay : public WeatherObserver
{
private:
    weak_ptr<WeatherStation> weatherStation;

public:
    CurrentConditionsDisplay(shared_ptr<WeatherStation> ws)
    {
        weatherStation = ws;
    }

    void update()
    {
        if (auto ws = weatherStation.lock())
        {
            cout << "Saving weather data...\n";
            cout << "Current Conditions: " << ws->toString() << endl;
        }
    }
};

class ForecastDisplay : public WeatherObserver
{
public:
    weak_ptr<WeatherStation> weatherStation;

public:
    ForecastDisplay(shared_ptr<WeatherStation> ws)
    {
        weatherStation = ws;
    }
    void update() override
    {
        if (auto ws = weatherStation.lock())
        {
            cout << "Updating analytics: " << ws->toString() << endl;
            cout << "Forecast: Rain trends, events...\n";
        }
    }
};

int main()
{
    cout << "###### Observer Pattern (Smart Pointer Version) ######\n";

    auto station = make_shared<WeatherStation>();

    auto current = make_shared<CurrentConditionsDisplay>(station);
    auto forecast = make_shared<ForecastDisplay>(station);

    station->addObserver(current);
    station->addObserver(forecast);

    cout << "===>>> Initial Update\n";
    station->setWeatherReadings(80, 65, 30.4f);

    cout << "===>>> Second Update\n";
    station->setWeatherReadings(82, 70, 29.2f);

    station->removeObserver(forecast);

    cout << "===>>> Third Update\n";
    station->setWeatherReadings(70, 21, 29.2f);

    return 0;
}