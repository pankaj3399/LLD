#include<bits/stdc++.h>
using namespace std;

class Vehicle {
public:
    virtual void drive() = 0; // pure virtual function
};

class Car : public Vehicle {
public:
    void drive() override {
        cout << "Driving a car!" << endl;
    }
};
class Bike : public Vehicle {
public:
    void drive() override {
        cout << "Riding a bike!" << endl;
    }
};
class Truck : public Vehicle {
public:
    void drive() override {
        cout << "Driving a truck!" << endl;
    }
};
class VehicleFactory {
public:
    static Vehicle* createVehicle(const string& type) {
        if (type == "car") {
            return new Car();
        } else if (type == "bike") {
            return new Bike();
        } else if (type == "truck") {
            return new Truck();
        } else {
            return nullptr;
        }
    }
};
int main() {
    Vehicle* vehicle1 = VehicleFactory::createVehicle("car");
    Vehicle* vehicle2 = VehicleFactory::createVehicle("bike");
    Vehicle* vehicle3 = VehicleFactory::createVehicle("truck");

    if (vehicle1) {
        vehicle1->drive();
    }
    if (vehicle2) {
        vehicle2->drive();
    }
    if (vehicle3) {
        vehicle3->drive();
    }

    delete vehicle1;
    delete vehicle2;
    delete vehicle3;

    return 0;
}