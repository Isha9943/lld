#pragma once
#include<iostream>
#include "../factories/DeviceFactory.hpp"
#include "../enums/DeviceType.hpp"
#include "../device/IAudioOutputDevice.hpp"
using namespace std;

class DeviceManager {
    private:
        static DeviceManager* instance;
        IAudioOutputDevice* currentOutputDevice;
        DeviceManager(){
            currentOutputDevice = nullptr;
        }
    public:


        static DeviceManager* getInstance() {
            if (instance == nullptr) {
                instance = new DeviceManager();
            }
            return instance;
        }

        void connect(DeviceType type) {
            if(currentOutputDevice != nullptr) {
                delete currentOutputDevice;
            }
            currentOutputDevice = DeviceFactory::createDevice(type);

            switch(type) {
                case DeviceType::BLUETOOTH:
                    cout << "Connected to Bluetooth speaker." << endl;
                    break;
                case DeviceType::WIRED:
                    cout << "Connected to Wired speaker." << endl;
                    break;
                case DeviceType::HEADPHONES:
                    cout << "Connected to Headphones." << endl;
                    break;
                default:
                    cout << "Connected to Headphones." << endl;
                    break;
            }
        }

        IAudioOutputDevice* getCurrentDevice() {
            if(currentOutputDevice == nullptr) {
                cout << "No device connected." << endl;
            }
            return currentOutputDevice;
        }

        bool hasOutputDevice() {
            return currentOutputDevice != nullptr;
        }
};

DeviceManager* DeviceManager::instance = nullptr;