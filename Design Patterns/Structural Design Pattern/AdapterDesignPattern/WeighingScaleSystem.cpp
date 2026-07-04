#include <iostream>
using namespace std;

// Adaptee Interface -
class ImperialWeighingMachine
{
public:
    virtual double getWeightPounds() = 0;
    virtual ~ImperialWeighingMachine() = default;
};

// Adaptee Implementation
class ImperialWeighingMachineImpl : public ImperialWeighingMachine
{
private:
    double weightPounds;

public:
    ImperialWeighingMachineImpl(double weight)
        : weightPounds(weight) {}

    double getWeightPounds() override
    {
        return weightPounds;
    }
};

// Target or Adapter Interface
class MetricWeighingMachineAdapter
{
public:
    virtual double getWeightKilograms() = 0;
    virtual ~MetricWeighingMachineAdapter() = default;
};

// Adapter Implementation
class MetricWeighingMachineAdapterImpl : public MetricWeighingMachineAdapter
{
private:
    ImperialWeighingMachine *imperialWeighingMachine;

public:
    MetricWeighingMachineAdapterImpl(ImperialWeighingMachine *imperialWeighingMachine)
    {
        this->imperialWeighingMachine = imperialWeighingMachine;
    }

    double getWeightKilograms() override
    {
        double weightInPound = this->imperialWeighingMachine->getWeightPounds();
        // Conversion formula: 1 pound = 0.453592 kg
        return weightInPound * 0.45;
    }
};

int main()
{
    cout << "======= Adapter Design Pattern ======" << endl;

    double weighingScaleReading = 25.0;

    // Existing Interface - Adapte
    ImperialWeighingMachine *imperialWeighingMachine = new ImperialWeighingMachineImpl(weighingScaleReading);

    // Adapter
    MetricWeighingMachineAdapter *adapter = new MetricWeighingMachineAdapterImpl(imperialWeighingMachine);

    cout << "WEIGHT IN KG: " << adapter->getWeightKilograms() << endl;

    return 0;
}