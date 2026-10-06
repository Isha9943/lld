#include<iostream>
#include<string>
using namespace std;    

// Base CAR class   
class Car{
    protected:
        string brand;
        string model;
        bool isEngineOn;
        int currentSpeed; 

    public:
        Car(string b, string m) {
            this->brand = b;
            this->model = m;
            isEngineOn = false;
            currentSpeed = 0;
        }

        void startEngine() {
            isEngineOn = true;
            cout << "Engine started." << endl;
        }

        void stopEngine() {
            isEngineOn = false;
            currentSpeed = 0;
            cout << "Engine stopped." << endl;
        }   

        virtual void accelerate() = 0;
        virtual void accelerate(int speed) = 0;
        virtual void brake() = 0;

        virtual ~Car() {}   
};

class ManualCar: public Car {
    private:
        int currentGear; 
    public:
        ManualCar(string b, string m) : Car(b, m) {
            currentGear = 0;
        }

        void accelerate() {
            if(isEngineOn) {
                currentSpeed += 10;
                cout << "Manual car accelerated to " << currentSpeed << " km/h." << endl;
            } else {
                cout << "Start the engine first." << endl;
            }
        }

        void accelerate(int speed) {
            if(isEngineOn) {
                currentSpeed += speed;
                cout << "Manual car accelerated to " << currentSpeed << " km/h." << endl;
            } else {
                cout << "Start the engine first." << endl;
            }
        }

        void brake() {
            if(currentSpeed > 0) {
                currentSpeed -= 10;
                if(currentSpeed < 0) currentSpeed = 0;
                cout << "Manual car slowed down to " << currentSpeed << " km/h." << endl;
            } else {
                cout << "Car is already stopped." << endl;
            }
        }
};

class ElectricCar: public Car{
    private:
        int batteryLevel;

    public:
        ElectricCar(string b, string m) : Car(b, m) {
            batteryLevel = 100;
        }

        void accelerate() {
            if(isEngineOn) {
                currentSpeed += 10;
                batteryLevel -= 1;
                cout << "Electric car accelerated to " << currentSpeed << " km/h." << endl;
            } else {
                cout << "Start the engine first." << endl;
            }
        }

        void accelerate(int speed) {
            if(isEngineOn) {
                currentSpeed += speed;
                batteryLevel -= speed / 10;
                cout << "Electric car accelerated to " << currentSpeed << " km/h." << endl;
            } else {
                cout << "Start the engine first." << endl;
            }
        }

        void brake() {
            if(currentSpeed > 0) {
                currentSpeed -= 10;
                if(currentSpeed < 0) currentSpeed = 0;
                cout << "Electric car slowed down to " << currentSpeed << " km/h." << endl;
            } else {
                cout << "Car is already stopped." << endl;
            }
        } 
};

int main(){
    ManualCar* myManualCar = new ManualCar("Toyota", "Corolla");
    ElectricCar* myElectricCar = new ElectricCar("Tesla", "Model S");

    myManualCar->startEngine();
    myManualCar->accelerate();
    myManualCar->accelerate(20);
    myManualCar->brake();

    myElectricCar->startEngine();
    myElectricCar->accelerate();
    myElectricCar->accelerate(30);
    myElectricCar->brake();

    delete myManualCar;
    delete myElectricCar;
}