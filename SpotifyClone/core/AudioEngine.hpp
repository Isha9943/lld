#pragma once
#include "../models/Song.hpp"
#include "../device/IAudioOutputDevice.hpp"
#include <string>
#include <iostream>

using namespace std;

class AudioEngine {
    private:
        Song* currentSong;
        bool songIsPaused;
    public:
        AudioEngine() {
            currentSong = nullptr;
            songIsPaused = false;
        }

        string getCurrentSongTitle() const {
            if (currentSong != nullptr) {
                return currentSong->getTitle();
            }
            return "";
        }

        bool isPaused() const {
            return songIsPaused;
        }

        void play(IAudioOutputDevice* aod, Song* song) {
            if(song==nullptr) {
                throw runtime_error("Song cannot be null");
            }
            
            // Resume if same song is passed
            if(songIsPaused && currentSong == song) {
                songIsPaused = false;
                cout<<"Resuming song: "<<currentSong->getTitle()<<endl;
                aod->playAudio(song);
                return;
            }

            currentSong = song;
            songIsPaused = false;
            cout<<"Playing song: "<<currentSong->getTitle()<<endl;
            aod->playAudio(song);
        }

        void pause(){
            if(currentSong==nullptr){
                throw runtime_error("No song is currently playing");
            }

            if(songIsPaused){
                throw runtime_error("Song is already paused");
            }
            songIsPaused = true;
            cout<<"Pausing song: "<<currentSong->getTitle()<<endl;

        }
};

