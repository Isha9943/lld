#pragma once
#include<iostream>
#include"../models/Playlist.hpp"
#include "PlayStrategy.hpp"

using namespace std;

class CustomQueueStrategy : public PlayStrategy {
    private:
        Playlist* currentPlaylist;
        int currentIndex;
        queue<Song*> nextQueue;
        stack<Song*> history;

        Song* nextSequential() {
            if(!currentPlaylist || currentPlaylist->getSize() == 0) {
                throw runtime_error("No songs available in the current playlist.");
            }
            currentIndex = currentIndex+1;
            return currentPlaylist->getSongs()[currentIndex];
        }

        Song* previousSequential() {
            if(!currentPlaylist || currentPlaylist->getSize() == 0) {
                throw runtime_error("No songs available in the current playlist.");
            }
            currentIndex = currentIndex-1;
            return currentPlaylist->getSongs()[currentIndex];
        }

    public:
        CustomQueueStrategy() {
            currentPlaylist = nullptr;
            currentIndex = -1;
        }

        void setPlaylist(Playlist* playlist) {
            currentPlaylist = playlist;
            currentIndex = -1;
            while(!nextQueue.empty()) {
                nextQueue.pop();
            }

            while(!history.empty()) {
                history.pop();
            }
        }

        bool hasNext() override {
            return !nextQueue.empty() || (currentPlaylist && currentIndex + 1 < currentPlaylist->getSize());
        }

        Song* next() override {
            if(!currentPlaylist || currentPlaylist->getSize() == 0) {
                throw runtime_error("No songs available in the current playlist.");
            }
            if(!nextQueue.empty()) {
                Song* nextSong = nextQueue.front();
                nextQueue.pop();
                history.push(nextSong);
                
                // auto update idx to match the queue idx
                const auto& list = currentPlaylist->getSongs();
                for(int i=0;i<list.size();i++){
                    if(list[i] == nextSong){
                        currentIndex = i;
                        break;
                    }
                }
                return nextSong;
            }
            return nextSequential();
        }

        bool hasPrevious() override {
            return !history.empty() || (currentPlaylist && currentIndex - 1 >= 0);
        }

        Song* previous() override {
            if(!history.empty()){
                Song* prevSong = history.top();
                // auto update idx to match stacked song
                const auto& list = currentPlaylist->getSongs();
                for(int i=0;i<list.size();i++){
                    if(list[i] == prevSong){
                        currentIndex = i;
                        break;
                    }
                }
                history.pop();
                return prevSong;
            }

            return previousSequential();
        }

        void addToNext(Song* song) {
            if(!song){
                throw runtime_error("Cannot add a null song to the next queue.");
            }

            nextQueue.push(song);
        }
};
