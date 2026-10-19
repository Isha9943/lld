#pragma once
#include<string>
#include<iostream>
#include<vector>
#include"Song.hpp"

using namespace std;

class Playlist {
    private:
        string playlistName;
        vector<Song*> songList;

    public:
        Playlist(string n) {
            playlistName = n;
        }

        string getPlaylistName() {
            return playlistName;
        }

        void addSongToPlaylist(Song* song) {
            if(song==nullptr){
                throw runtime_error("Cannot add a null song to the playlist.");
            }
                
            songList.push_back(song);
        }

        vector<Song*> getSongs() {
            return songList;
        }

        int getSize(){
            return (int) songList.size();
        }
};