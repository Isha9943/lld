#include<iostream>
#include<string>
using namespace std;    

class ManualCar {
    private:
        string brand;
        string model;
        bool isEngineOn;
        int currentSpeed;
        int currentGear;

    public:
        ManualCar(string b, string m) {
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

        void stopEngine() {
            isEngineOn = false;
            currentSpeed = 0;
            currentGear = 0;
            cout << "Engine stopped." << endl;
        }

        // Static polymorphism in action: method overloading for accelerate
        void accelerate() {
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

        void accelerate(int speed) {
            if(!isEngineOn) {
                cout << "Cannot accelerate. Engine is off." << endl;
                return;
            }
            currentSpeed += speed;
            if(currentSpeed / 10 > currentGear) {
                currentGear = currentSpeed / 10;
            }
            cout << "Accelerated to " << currentSpeed << " km/h in gear " << currentGear << "." << endl;
        }

        void brake() {
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

        void shiftGear(int gear) {
            if(!isEngineOn) {
                cout << "Cannot shift gear. Engine is off." << endl;
                return;
            }
            if(gear < 0) gear = 0;
            currentGear = gear;
            cout << "Shifted to gear " << currentGear << "." << endl;
        }

        virtual ~ManualCar() {}
};

int main(){
    ManualCar* car = new ManualCar("Toyota", "Corolla");
    car->startEngine();
    car->accelerate();
    car->accelerate(30);
    car->brake();
    car->shiftGear(3);
    car->stopEngine();

    delete car;
}