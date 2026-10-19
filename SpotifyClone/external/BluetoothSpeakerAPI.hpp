#pragma once
#include <string>
#include <iostream>

using namespace std;

class BluetoothSpeakerAPI {
    public:
        void playSoundViaBluetooth(const string& data) {
            cout << "Playing via Bluetooth: " << data << endl;
        }
};

