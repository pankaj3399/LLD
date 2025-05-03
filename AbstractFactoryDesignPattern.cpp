#include<bits/stdc++.h>
using namespace std;
// Abstract Factory Design Pattern
// Abstract classes for different types of vehicles
class Car {
public:
    virtual void drive() = 0; // pure virtual function
};
class Bike {
public:
    virtual void ride() = 0; // pure virtual function
};
class Truck {
public:
    virtual void haul() = 0; // pure virtual function
};
// Concrete classes for different types of cars
class Sedan : public Car {
public:
    void drive() override {
        cout << "Driving a sedan!" << endl;
    }
};
class SUV : public Car {
public:
    void drive() override {
        cout << "Driving an SUV!" << endl;
    }
};
// Concrete classes for different types of bikes
class MountainBike : public Bike {
public:
    void ride() override {
        cout << "Riding a mountain bike!" << endl;
    }
};
class RoadBike : public Bike {
public:
    void ride() override {
        cout << "Riding a road bike!" << endl;
    }
};
// Concrete classes for different types of trucks
class PickupTruck : public Truck {
public:
    void haul() override {
        cout << "Hauling with a pickup truck!" << endl;
    }
};
class DeliveryTruck : public Truck {
public:
    void haul() override {
        cout << "Hauling with a delivery truck!" << endl;
    }
};
// Abstract Factory class
class VehicleFactory {
public:
    virtual Car* createCar() = 0; // pure virtual function
    virtual Bike* createBike() = 0; // pure virtual function
    virtual Truck* createTruck() = 0; // pure virtual function
};
// Concrete Factory class for creating vehicles
class ConcreteVehicleFactory : public VehicleFactory {
public:
    Car* createCar() override {
        return new Sedan(); // or new SUV();
    }
    Bike* createBike() override {
        return new MountainBike(); // or new RoadBike();
    }
    Truck* createTruck() override {
        return new PickupTruck(); // or new DeliveryTruck();
    }
};
// Client code
int main() {
    VehicleFactory* factory = new ConcreteVehicleFactory();
    
    Car* car = factory->createCar();
    Bike* bike = factory->createBike();
    Truck* truck = factory->createTruck();
    
    car->drive();
    bike->ride();
    truck->haul();
    
    delete car;
    delete bike;
    delete truck;
    delete factory;
    
    return 0;
}