#pragma once
#include "MusicPlayerFacade.hpp"
#include "models/Song.hpp"
#include "managers/PlaylistManager.hpp"
#include "models/Playlist.hpp"
#include "managers/DeviceManager.hpp"
#include "MusicPlayerFacade.hpp"
using namespace std;

class MusicPlayerApplication {
    private:
        static MusicPlayerApplication* instance;
        vector<Song*> songLibrary;
        MusicPlayerApplication() {};

    public:
        static MusicPlayerApplication* getInstance() {
            if (!instance) {
                instance = new MusicPlayerApplication();
            }
            return instance;
        }

        void createSongInLibrary(const string& title, const string& artist, const string&path) {
            Song* newSong = new Song(title, artist, path);
            songLibrary.push_back(newSong);
        }

        Song* findSongByTitle(const string& title) {
            for(Song* song : songLibrary) {
                if(song->getTitle() == title) {
                    cout << "Found song: " << song->getTitle() << " by " << song->getArtist() << endl;
                    return song;
                }
            }
            cout << "Song with title \"" << title << "\" not found in library." << endl;
            return nullptr;
        }

        void createPlaylist(const string& playlistName) {
            PlaylistManager::getInstance()->createPlaylist(playlistName);
        }

        void addSongToPlaylist(const string& playlistName, const string& songTitle) {
            Song *song = findSongByTitle(songTitle);
            if (!song) {
                throw runtime_error("Cannot add song. Song with title \"" + songTitle + "\" not found in library.");
            }
            PlaylistManager::getInstance()->addSongToPlaylist(playlistName, song);
        }

        void connectAudioDevice(DeviceType deviceType) {
            MusicPlayerFacade::getInstance()->connectDevice(deviceType);
        }

        void selectPlayStrategy(PlayStrategyType strategyType) {
            MusicPlayerFacade::getInstance()->setPlayStrategy(strategyType);
        }

        void loadPlaylist(const string& playlistName) {
            MusicPlayerFacade::getInstance()->loadPlaylist(playlistName);
        }

        void playSingleSong(const string& songTitle) {
            Song* song = findSongByTitle(songTitle);
            if (!song) {
                throw runtime_error("Cannot play song. Song with title \"" + songTitle + "\" not found in library.");
            }
            MusicPlayerFacade::getInstance()->playSong(song);
        }

        void pauseCurrentSong(const string& songTitle) {
            Song* song = findSongByTitle(songTitle);
            if (!song) {
                throw runtime_error("Cannot pause song. Song with title \"" + songTitle + "\" not found in library.");
            }
            MusicPlayerFacade::getInstance()->pauseSong(song);
        }

        void playAllTracksInPlaylist() {
            MusicPlayerFacade::getInstance()->playAllTracks();
        }

        void playPreviousTrackInPlaylist() {
            MusicPlayerFacade::getInstance()->playPreviousTrack();
        }

        void queueSongNext(const string& songTitle) {
            Song* song = findSongByTitle(songTitle);
            if (!song) {
                throw runtime_error("Cannot queue song. Song with title \"" + songTitle + "\" not found in library.");
            }
            MusicPlayerFacade::getInstance()->enqueueNext(song);
        }
};

MusicPlayerApplication* MusicPlayerApplication::instance = nullptr;