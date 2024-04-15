// 2. Using an abstract class with only pure virtual functions, you can specify similar
// behaviors for possibly disparate classes. Governments and companies worldwide are
// becoming increasingly concerned with carbon footprints (annual releases of carbon
// dioxide into the atmosphere) from buildings burning various types of fuels for heat,
// vehicles burning fuels for power, and the like. Many scientists blame these greenhouse
// gases for the phenomenon called global warming. Create three small classes unrelated
// by inheritance -- classes Building, Car and Bicycle. Give each class some unique
// appropriate attributes and behaviors that it does not have in common with other classes.
// Write an abstract class CarbonFootprint with only a pure virtual getCarbonFootprint
// method. Have each of your classes inherit from that abstract class and implement the
// getCarbonFootprint method to calculate an appropriate carbon footprint for that class
// (check out a few websites that explain how to calculate carbon footprints, such as
// https://www.youtube.com/watch?v=wWeI0c1m14Y). Write an application that creates
// objects of each of the three classes, places pointers to those objects in a vector of
// CarbonFootprint pointers, then iterates through the vector, polymorphically invoking
// each object’s getCarbonFootprint method. For each object, print some identifying
// information and the object’s carbon footprint.

Answer:
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Abstract base class
class CarbonFootprint {
public:
    virtual ~CarbonFootprint() = default;
    virtual double getCarbonFootprint() const = 0;
    virtual string getName() const = 0; 
};

// Building class
class Building : public CarbonFootprint {
private:
    double energyUseKWh;
    string name;
public:
    Building(double energy, string n) : energyUseKWh(energy), name(std::move(n)) {}
    virtual double getCarbonFootprint() const override {
        const double CO2_EMISSION_PER_KWH = 0.92; // CO2 emission per kWh
        return energyUseKWh * CO2_EMISSION_PER_KWH;
    }
    virtual string getName() const override { return name; }
};

// Car class
class Car : public CarbonFootprint {
private:
    double fuelGallons;
    string name;
public:
    Car(double gallons, string n) : fuelGallons(gallons), name(std::move(n)) {}
    virtual double getCarbonFootprint() const override {
        const double CO2_EMISSION_PER_GALLON = 19.6; // CO2 emission per gallon of gasoline
        return fuelGallons * CO2_EMISSION_PER_GALLON;
    }
    virtual string getName() const override { return name; }
};

// Bicycle class
class Bicycle : public CarbonFootprint {
private:
    string name;
public:
    Bicycle(string n) : name(std::move(n)) {}
    virtual double getCarbonFootprint() const override {
        return 0; // Bicycles don't emit CO2 directly
    }
    virtual string getName() const override { return name; }
};

int main() {
    // Create objects of each class with identifiers
    Building building(15000, "Building"); // Assume 15,000 kWh annual energy use
    Car car(500, "Car"); // Assume 500 gallons of fuel annually
    Bicycle bicycle("Bicycle");

    // Create a vector of CarbonFootprint pointers
    vector<CarbonFootprint*> carbonFootprints;
    carbonFootprints.push_back(&building);
    carbonFootprints.push_back(&car);
    carbonFootprints.push_back(&bicycle);

    // Iterate through the vector, polymorphically invoking getCarbonFootprint
    for (const CarbonFootprint* cf : carbonFootprints) {
        cout << cf->getName() << " Carbon Footprint: " << cf->getCarbonFootprint() << " kg of CO2" << endl;
    }

    return 0;
}

Output-
Building Carbon Footprint: 13800 kg of CO2
Car Carbon Footprint: 9800 kg of CO2
Bicycle Carbon Footprint: 0 kg of CO2
