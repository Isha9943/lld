#pragma once

#include "../models/Song.hpp"
#include "IAudioOutputDevice.hpp"
#include "../external/HeadphoneSpeakerAPI.hpp"

using namespace std;

class HeadphoneAdapter : public IAudioOutputDevice {
    private:
        HeadphoneSpeakerAPI* headphoneApi;
    public:
        HeadphoneAdapter(HeadphoneSpeakerAPI* api) {
            headphoneApi = api;
        }

        void playAudio(Song* song) override {
            string payload = song->getTitle()+" by " + song->getArtist();
            headphoneApi->playSoundViaJack(payload);
        }
};