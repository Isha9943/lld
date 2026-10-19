#pragma once
#include<iostream>
#include "PlayStrategy.hpp"
#include "../models/Playlist.hpp"
using namespace std;

class SequentialPlayStrategy : public PlayStrategy {
    private:
        Playlist* currentPlaylist;
        int currentIndex;

    public:
        SequentialPlayStrategy() {
            currentPlaylist = nullptr;
            currentIndex = -1;
        }

        void setPlaylist(Playlist* playlist) override {
            this->currentPlaylist = playlist;
            this->currentIndex = -1;
        }


        bool hasNext() override {
            return (currentPlaylist && currentIndex + 1 < currentPlaylist->getSize());
        }

        Song* next() override {
            if(!currentPlaylist || currentPlaylist->getSize()==0){
                throw runtime_error("No next song available");
            }
            currentIndex++;
            return currentPlaylist->getSongs()[currentIndex];
        }

        bool hasPrevious() override {
            return (currentIndex - 1 >= 0);

        }

        Song* previous() override {
            if(!currentPlaylist || currentPlaylist->getSize()==0){
                throw runtime_error("No previous song available");
            }
            currentIndex--;
            return currentPlaylist->getSongs()[currentIndex];
        }

        
};  
