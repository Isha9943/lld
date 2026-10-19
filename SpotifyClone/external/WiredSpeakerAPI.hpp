#pragma once
#include <string>
#include <iostream>

using namespace std;

class WiredSpeakerAPI {
    public:
        void playSoundViaCable(const string& data) {
            cout << "Playing via Wired Cable: " << data << endl;
        }
};