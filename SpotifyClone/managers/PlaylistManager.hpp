#pragma once
#include "../models/Playlist.hpp"
#include <vector>
#include<string>
#include<map>

using namespace std;

class PlaylistManager {
    private:
        static PlaylistManager* instance;
        map<string, Playlist*> playlists;
        PlaylistManager() {}

    public:
        static PlaylistManager* getInstance() {
            if (instance == nullptr) {
                instance = new PlaylistManager();
            }
            return instance;
        }

        void createPlaylist(const string& name) {
            if(playlists.find(name) != playlists.end()) {
                throw runtime_error("Playlist already exists.");
            }
            playlists[name] = new Playlist(name);
        }

        void addSongToPlaylist(const string& playlistName, Song* song) {
            if(!playlists.count(playlistName)) {
                throw runtime_error("Playlist does not exist.");
            }
            playlists[playlistName]->addSongToPlaylist(song);
        }

        Playlist* getPlaylist(const string& playlistName) {
            if(!playlists.count(playlistName)) {
                throw runtime_error("Playlist does not exist.");
            }
            return playlists[playlistName];
        }

};

PlaylistManager* PlaylistManager::instance = nullptr;