#include<iostream>
#include<string>
using namespace std;

class SportsCar {
    // Private attributes of the SportsCar class.
    private: 
        string brand;
        string model;
        bool isEngineOn;
        int currentSpeed;
        int currentGear;
        string tyre;

    // Public methods of the SportsCar class.
    public: 
        // Constructor for the SportsCar class. Initializes the brand, model, and default values for engine status, speed, and gear.
        SportsCar(string b, string m){
            this->brand = b;
            this->model = m;
            isEngineOn = false;
            currentSpeed = 0;
            currentGear = 0;
            tyre = "default";
        }

        // getters and setters
        int getCurrentSpeed(){
            return currentSpeed;
        }

        string getTyre(){
            return tyre;
        }   
        void setTyre(string t){
            // validations can be added before setting.
            tyre = t;
        }

        // Method to start the engine of the sports car. Sets the engine status to on and prints a message.
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
    SportsCar* myCar = new SportsCar("Ford", "Mustang");
    myCar->startEngine();
    myCar->shiftGear(1);
    myCar->accelerate();
    myCar->brake();
    myCar->stopEngine();

    // Directly modifying the current speed of the car which should ideally be done through the accelerate or brake methods.
    // to avoid this, make the attributes as private.
    // myCar->currentSpeed = 100;
    cout << "Current speed directly set to " << myCar->getCurrentSpeed() << " km/h." << endl;

    myCar->setTyre("MRF");

    delete myCar;
    return 0;
}