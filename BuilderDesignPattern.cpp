#include <iostream>
#include <string>
using namespace std;

class Car
{
public:
    string engine;
    string wheels;
    string color;

    void showDetails() const
    {
        cout << "Car Details:\n";
        cout << "Engine: " << engine << "\n";
        cout << "Wheels: " << wheels << "\n";
        cout << "Color: " << color << "\n";
    }
};
class CarBuilder
{
public:
    virtual ~CarBuilder() = default;
    virtual CarBuilder &setEngine(const string &engine) = 0;
    virtual CarBuilder &setWheels(const string &wheels) = 0;
    virtual CarBuilder &setColor(const string &color) = 0;
    virtual Car getResult() = 0;
};
class ConcreteCarBuilder : public CarBuilder
{
private:
    Car car;

public:
    ConcreteCarBuilder &setEngine(const string &engine) override
    {
        car.engine = engine;
        return *this; // Return the builder object itself for chaining
    }

    ConcreteCarBuilder &setWheels(const string &wheels) override
    {
        car.wheels = wheels;
        return *this; // Return the builder object itself for chaining
    }

    ConcreteCarBuilder &setColor(const string &color) override
    {
        car.color = color;
        return *this; // Return the builder object itself for chaining
    }

    Car getResult() override
    {
        return car;
    }
};
int main()
{
    ConcreteCarBuilder builder;

    // Use method chaining to set the car properties
    Car car = builder.setEngine("V8")
                  .setWheels("Alloy")
                  .setColor("Red")
                  .getResult();

    // Display the details of the constructed car
    car.showDetails();

    return 0;
}
