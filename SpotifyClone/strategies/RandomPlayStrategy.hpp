#pragma once
#include<iostream>
#include<vector>
#include<stack>
#include "PlayStrategy.hpp"
#include "../models/Playlist.hpp"

using namespace std;

class RandomPlayStrategy : public PlayStrategy {
    private:
        Playlist* currentPlaylist;
        vector<Song*> remainingSongs;
        stack<Song*> history;


    public:
        RandomPlayStrategy() {
            currentPlaylist = nullptr;
            srand((unsigned)time(nullptr));
        }

        void setPlaylist(Playlist* playlist) override {
            this->currentPlaylist = playlist;

            if(!currentPlaylist || currentPlaylist->getSize() == 0) {
                return;
            } 

            remainingSongs = currentPlaylist->getSongs();
            history = stack<Song*>();
        }

        bool hasNext() override {
            return currentPlaylist && !remainingSongs.empty();
        }

        Song* next() override {
            if(!currentPlaylist || currentPlaylist->getSize()==0){ 
                throw runtime_error("No next song available");
            }
            if(remainingSongs.empty()) {
                throw runtime_error("No next song available");
            }
            int randomIndex = rand() % remainingSongs.size();
            Song* selectedSong = remainingSongs[randomIndex];
            

            // Remove the selected song from the remaining songs and add it to the history
            swap(remainingSongs[randomIndex], remainingSongs.back());
            remainingSongs.pop_back();
            history.push(selectedSong);
            return selectedSong;
        }

        bool hasPrevious() override {
            return !history.empty();
        }

        Song* previous() override {
            if(history.empty()) {
                throw runtime_error("No previous song available");
            }
            Song* previousSong = history.top();
            history.pop();
            remainingSongs.push_back(previousSong);
            return previousSong;
        }
};