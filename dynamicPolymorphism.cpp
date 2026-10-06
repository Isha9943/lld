#include<iostream>
#include<string>
using namespace std;

// Base class for cars
class Car{
    protected:
        string brand;
        string model;
        bool isEngineOn;
        int currentSpeed;

    public:
        Car(string b, string m){
            this->brand = b;
            this->model = m;
            isEngineOn = false;
            currentSpeed = 0;
        }   

        //Common methods for all cars
        void startEngine() {
            isEngineOn = true;
            cout << "Engine started." << endl;
        }

        void stopEngine() {
            isEngineOn = false;
            currentSpeed = 0;
            cout << "Engine stopped." << endl;
        }

        virtual void accelerate() =0;

        virtual void brake() =0;

        virtual ~Car() {}
};

class ManualCar: public Car{
    private:
        int currentGear;

    public: 
        ManualCar(string b, string m): Car(b, m) {
            currentGear = 0;
        }

        // Dynamic polymorphism in action: overriding the accelerate and brake methods
        void accelerate() override {
            if(!isEngineOn) {
                cout << "Cannot accelerate. Engine is off." << endl;
                return;
            }
            currentSpeed += 20;
            if(currentSpeed / 10 > currentGear) {
                currentGear = currentSpeed / 10;
            }
            cout << "Accelerated to " << currentSpeed << " km/h in gear " << currentGear << "." << endl;
        }

        void brake() override {
            if(!isEngineOn) {
                cout << "Cannot brake. Engine is off." << endl;
                return;
            }
            currentSpeed -= 20;
            if(currentSpeed < 0) currentSpeed = 0;
            if(currentSpeed / 10 < currentGear) {
                currentGear = currentSpeed / 10;
            }
            cout << "Slowed down to " << currentSpeed << " km/h in gear " << currentGear << "." << endl;
        }
};

class ElectricCar: public Car {
    private:
        int batteryLevel;

    public:
        ElectricCar(string b, string m): Car(b, m) {
            batteryLevel = 100;
        }

        // Dynamic polymorphism in action: overriding the accelerate and brake methods
        void accelerate() override {
            if(!isEngineOn) {
                cout << "Cannot accelerate. Engine is off." << endl;
                return;
            }
            if(batteryLevel <= 0) {
                cout << "Cannot accelerate. Battery is empty." << endl;
                return;
            }
            currentSpeed += 15;
            batteryLevel -= 5;
            if(batteryLevel < 0) batteryLevel = 0;
            cout << "Accelerated to " << currentSpeed << " km/h. Battery level: " << batteryLevel << "%." << endl;
        }

        void brake() override {
            if(!isEngineOn) {
                cout << "Cannot brake. Engine is off." << endl;
                return;
            }
            currentSpeed -= 15;
            if(currentSpeed < 0) currentSpeed = 0;
            cout << "Slowed down to " << currentSpeed << " km/h. Battery level: " << batteryLevel << "%." << endl;
        }
};


int main(){
    Car* myCar = new ManualCar("Toyota", "Corolla");
    myCar->startEngine();
    myCar->accelerate();
    myCar->accelerate();
    myCar->brake();
    myCar->stopEngine();
    delete myCar;   

    Car* myElectricCar = new ElectricCar("Tesla", "Model S");
    myElectricCar->startEngine();
    myElectricCar->accelerate();
    myElectricCar->accelerate();
    myElectricCar->brake();
    myElectricCar->stopEngine();
    delete myElectricCar;

    return 0;
}