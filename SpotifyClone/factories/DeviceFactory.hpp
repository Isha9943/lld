#pragma once
#include<iostream>
#include "../enums/DeviceType.hpp"
#include"../device/IAudioOutputDevice.hpp"
#include "../device/BluetoothSpeakerAdapter.hpp"
#include "../device/WiredSpeakerAdapter.hpp"
#include "../device/HeadphoneAdapter.hpp"

using namespace std;

class DeviceFactory {
    public:
        static IAudioOutputDevice* createDevice(DeviceType type) {
            switch(type) {
                case DeviceType::BLUETOOTH:
                    return new BluetoothSpeakerAdapter(new BluetoothSpeakerAPI());
                case DeviceType::WIRED:
                    return new WiredSpeakerAdapter(new WiredSpeakerAPI());
                case DeviceType::HEADPHONES:
                    return new HeadphoneAdapter(new HeadphoneSpeakerAPI());
                default:
                    return new HeadphoneAdapter(new HeadphoneSpeakerAPI());
            }
        }
};
