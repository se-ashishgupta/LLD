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
    virtual ~WeatherObserver() {}
};

// Observable Interface
class WeatherObservable
{
public:
    virtual void addObserver(WeatherObserver *observer) = 0;
    virtual void removeObserver(WeatherObserver *observer) = 0;
    virtual void notifyObservers() = 0;
    virtual void setWeatherReadings(float temp, float humi, float pres) = 0;

    virtual ~WeatherObservable() {};
};

class WeatherStation : public WeatherObservable
{
private:
    vector<WeatherObserver *> observers;

    float temperature;
    float humidity;
    float pressure;

public:
    void addObserver(WeatherObserver *observer) override
    {
        observers.push_back(observer);
        cout << "[+] Observer registered\n";
    }

    void removeObserver(WeatherObserver *observer) override
    {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
        cout << "[-] Observer removed\n";
    }

    void notifyObservers() override
    {
        for (auto observer : observers)
        {
            observer->update();
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
    WeatherStation *weatherStation;

public:
    CurrentConditionsDisplay(WeatherStation *ws)
    {
        weatherStation = ws;
        weatherStation->addObserver(this);
    }

    void update()
    {
        cout << "Saving weather data...\n";
        cout << "Current Conditions: " << weatherStation->toString() << endl;
    }
};

class ForecastDisplay : public WeatherObserver
{
public:
    WeatherStation *weatherStation;

public:
    ForecastDisplay(WeatherStation *ws)
    {
        weatherStation = ws;
        weatherStation->addObserver(this);
    }

    void update() override
    {

        cout << "Updating analytics: " << weatherStation->toString() << endl;
        cout << "Forecast: Rain trends, events...\n";
    }
};

int main()
{
    cout << "###### Observer Pattern  ######\n";

    WeatherStation *station = new WeatherStation();

    CurrentConditionsDisplay *current = new CurrentConditionsDisplay(station);
    ForecastDisplay *forecast = new ForecastDisplay(station);

    cout << "===>>> Initial Update\n";
    station->setWeatherReadings(80, 65, 30.4f);

    cout << "===>>> Second Update\n";
    station->setWeatherReadings(82, 70, 29.2f);

    station->removeObserver(forecast);

    cout << "===>>> Third Update\n";
    station->setWeatherReadings(70, 21, 29.2f);

    delete station;
    delete current;
    delete forecast;

    return 0;
}