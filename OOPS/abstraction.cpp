#include<iostream>
#include<string>
using namespace std;

// virtual means this function is just declared in the base class and must be implemented by derived classes.
// ~Car() is the destructor method for the Car class.
class Car{
    public:
        virtual void startEngine()=0;
        virtual void stopEngine()=0;
        virtual void shiftGear(int gear) = 0;
        virtual void accelerate()=0;
        virtual void brake()=0;
        virtual ~Car(){};
};

// Sports car extends Car and hence is the child class of Car.
class SportsCar : public Car{
    public: 
    string brand;
    string model;
    bool isEngineOn;
    int currentSpeed;
    int currentGear;

    SportsCar(string b, string m){
        this->brand = b;
        this->model = m;
        isEngineOn = false;
        currentSpeed = 0;
        currentGear = 0;
    }

    void startEngine() {
        isEngineOn = true;
        cout << "Engine started." << endl;
    }

    void shiftGear(int gear) {
        if(!isEngineOn) {
            cout<<"Cannot shift gear. Engine is off." << endl;
            return;
        }
        currentGear = gear;
        cout << "Gear shifted to " << currentGear << "." << endl;
    }

    void accelerate(){
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

    void stopEngine() {
        isEngineOn = false;
        currentSpeed = 0;
        currentGear = 0;
        cout << "Engine stopped." << endl;
    }
};


int main() {
    // Parent Class pointer is used for runtime polymorphism.
    // Using the Car pointer, we can call the methods of the SportsCar class at runtime.
    Car* myCar = new SportsCar("Ford", "Mustang");
    myCar->startEngine();
    myCar->shiftGear(1);
    myCar->accelerate();
    myCar->brake();
    myCar->stopEngine();

    delete myCar;
    return 0;
}