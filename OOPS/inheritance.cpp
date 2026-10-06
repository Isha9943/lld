#include<iostream>
#include<string>
using namespace std;

class Car{
    // Can be inherited by derived classes
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
        
        // public methods for controlling the car will be used by all derived classes
        void startEngine() {
            isEngineOn = true;
            cout << "Engine started." << endl;
        }

        void stopEngine() {
            isEngineOn = false;
            currentSpeed = 0;
            cout << "Engine stopped." << endl;
        }

        void accelerate() {
            if(!isEngineOn) {
                cout << "Cannot accelerate. Engine is off." << endl;
                return;
            }
            currentSpeed += 10;
            cout << "Accelerated to " << currentSpeed << " km/h." << endl;
        }

        void brake() {
            if(!isEngineOn) {
                cout << "Cannot brake. Engine is off." << endl;
                return;
            }
            currentSpeed -= 10;
            if(currentSpeed < 0) currentSpeed = 0;
            cout << "Slowed down to " << currentSpeed << " km/h." << endl;
        }

        virtual ~Car() {}

};

// ManualCar class inherits from Car class
class ManualCar: public Car{
    // ManualCar specific attributes and methods
    private:
        int currentGear;

    public:
        ManualCar(string b, string m): Car(b, m) {
            currentGear =0;
        }

        void changeGear(int gear) {
            if(!isEngineOn) {
                cout << "Cannot change gear. Engine is off." << endl;
                return;
            }
            currentGear = gear;
            cout << "Gear changed to " << currentGear << "." << endl;
        }

};

// ElectricCar class inherits from Car class
class ElectricCar: public Car{
    // ElectricCar specific attributes and methods
    private:
        int batteryLevel;

    public:
        ElectricCar(string b, string m): Car(b, m) {
            batteryLevel = 100;
        }

        void chargeBattery(int amount) {
            batteryLevel += amount;
            if(batteryLevel > 100) batteryLevel = 100;
            cout << "Battery charged to " << batteryLevel << "%." << endl;
        }

};


int main(){
    ManualCar myManualCar("Toyota", "Corolla");
    myManualCar.startEngine();
    myManualCar.changeGear(1);
    myManualCar.accelerate();
    myManualCar.brake();
    myManualCar.stopEngine();

    ElectricCar myElectricCar("Tesla", "Model S");
    myElectricCar.startEngine();
    myElectricCar.accelerate();
    myElectricCar.brake();
    myElectricCar.chargeBattery(20);
    myElectricCar.stopEngine();
}