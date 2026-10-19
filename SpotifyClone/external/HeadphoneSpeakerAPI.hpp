#pragma once
#include <string>
#include <iostream>

using namespace std;

class HeadphoneSpeakerAPI {
    public:
        void playSoundViaJack(const string& data) {
            cout << "Playing via Headphone Jack: " << data << endl;
        }
};