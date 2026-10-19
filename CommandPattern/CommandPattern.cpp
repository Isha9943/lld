#include<vector>
#include<string>
#include<iostream>
using namespace std;

// Command Interface
class ICommand {
    public:
        virtual void execute() = 0;
        virtual void undo() = 0;
        virtual ~ICommand() {};
};

// Receivers
class Light {
    public:
        void turnOn() {
            cout << "Light is ON" << endl;
        }

        void turnOff() {
            cout << "Light is OFF" << endl;
        }
};

class Fan {
    public:
        void turnOn() {
            cout << "Fan is ON" << endl;
        }

        void turnOff() {
            cout << "Fan is OFF" << endl;
        }
};

// Concrete Command for Light
class LightCommand : public ICommand {
    private:
        Light* light;
    public:
        LightCommand(Light* l) {
            light = l;
        }

        void execute() override {
            light->turnOn();
        }

        void undo() override {
            light->turnOff();
        }
};

// Concrete Command for Fan 
class FanCommand : public ICommand {
    private:
        Fan* fan;
    public:
        FanCommand(Fan* f) {
            fan = f;
        }

        void execute() override {
            fan->turnOn();
        }

        void undo() override {
            fan->turnOff();
        }
};

// Invoker: RemoteController with 4 buttons 
class RemoteController {
    private:
        static const int numButtons = 4;
        ICommand* buttons[numButtons];
        bool isButtonPressed[numButtons];

    public:
        RemoteController() {
            for(int i = 0; i < numButtons; i++) {
                buttons[i] = nullptr;
                isButtonPressed[i] = false;
            }
        }

        void setCommand(int buttonIndex, ICommand* command) {
            if(buttonIndex >= 0 && buttonIndex < numButtons) {
                if(buttons[buttonIndex] != nullptr) {
                    delete buttons[buttonIndex];
                }
                buttons[buttonIndex] = command;
                isButtonPressed[buttonIndex] = false;
            }
        }

        void pressButton(int buttonIndex) {
            if(buttonIndex >= 0 && buttonIndex < numButtons && buttons[buttonIndex] != nullptr) {
                if(isButtonPressed[buttonIndex]==false){
                    buttons[buttonIndex]->execute();
                } else {
                    buttons[buttonIndex]->undo();
                }
                isButtonPressed[buttonIndex] = !isButtonPressed[buttonIndex];
            } else {
                cout << "Button " << buttonIndex << " is not assigned a command or is out of range." << endl;
            }
        }

          
        
        ~RemoteController() {
            for(int i = 0; i < numButtons; i++) {
                if(buttons[i] != nullptr) {
                    delete buttons[i];
                }
            }
        }
};


int main() {
    Light* livingRoomLight = new Light();
    Fan* ceilingFan = new Fan();

    RemoteController* remote = new RemoteController();

    remote->setCommand(0, new LightCommand(livingRoomLight));
    remote->setCommand(1, new FanCommand(ceilingFan));

    // Simulate button presses
    cout<<"Toggling Light button:" << endl;
    remote->pressButton(0);
    remote->pressButton(0);
    cout<<"Toggling Fan button:" << endl;
    remote->pressButton(1);
    remote->pressButton(1);

    // press unassigned button
    remote->pressButton(2);

    // Clean up
    delete remote;
    delete livingRoomLight;
    delete ceilingFan;
    return 0;
    
}

