#include "core/AudioEngine.hpp"
#include "models/Playlist.hpp"
#include "managers/PlaylistManager.hpp"
#include "strategies/PlayStrategy.hpp"
#include "enums/DeviceType.hpp"
#include "managers/DeviceManager.hpp"
#include "managers/StrategyManager.hpp"
#include "enums/PlayStrategyType.hpp"
using namespace std;

class MusicPlayerFacade {
    private:
        static MusicPlayerFacade* instance;
        AudioEngine* audioEngine;
        Playlist* loadedPlaylist;
        PlayStrategy* playStrategy;

        MusicPlayerFacade() {
            loadedPlaylist = nullptr;
            audioEngine = new AudioEngine();
            playStrategy = nullptr;
        }

    public: 
        static MusicPlayerFacade* getInstance() {
            if (!instance) {
                instance = new MusicPlayerFacade();
            }
            return instance;
        }

        void connectDevice(DeviceType deviceType) {
            DeviceManager::getInstance()->connect(deviceType);
        }

        void setPlayStrategy(PlayStrategyType strategy) {
            playStrategy = StrategyManager::getInstance()->getStrategy(strategy);
        }

        void loadPlaylist(const string& playlistName) {
            loadedPlaylist = PlaylistManager::getInstance()->getPlaylist(playlistName);
            if(!playStrategy) {
                throw runtime_error("Play strategy not set");
            }
            playStrategy->setPlaylist(loadedPlaylist);
        }

        void playSong(Song* song) {
            if(!DeviceManager::getInstance()->hasOutputDevice()){
                throw runtime_error("No output device connected");
            }

            IAudioOutputDevice* outputDevice = DeviceManager::getInstance()->getCurrentDevice();
            audioEngine->play(outputDevice, song);

        }

        void pauseSong(Song* song) {
            if(audioEngine->getCurrentSongTitle()!=song->getTitle()) {
                throw runtime_error("The song to pause is not currently playing");
            }
            audioEngine->pause();
        }

        void playAllTracks() {
            if(!loadedPlaylist) {
                throw runtime_error("No playlist loaded");
            }
            while(playStrategy->hasNext()) {
                Song* nextSong = playStrategy->next();
                playSong(nextSong);
            }
            cout<<"Completed Playlist: "<<loadedPlaylist->getPlaylistName()<<endl;
        }

        void playNextTrack() {
            if(!loadedPlaylist) {
                throw runtime_error("No playlist loaded");
            }
            if(!playStrategy) {
                throw runtime_error("Play strategy not set");
            }
            if(!playStrategy->hasNext()) {
                throw runtime_error("No next track available");
            }
            Song* nextSong = playStrategy->next();
            playSong(nextSong);
        }

        void playPreviousTrack() {
            if(!loadedPlaylist) {
                throw runtime_error("No playlist loaded");
            }
            if(!playStrategy) {
                throw runtime_error("Play strategy not set");
            }
            if(!playStrategy->hasPrevious()) {
                throw runtime_error("No previous track available");
            }
            Song* previousSong = playStrategy->previous();
            playSong(previousSong);
        }

        void enqueueNext(Song* song) {
            playStrategy->addToNext(song);
        }
    
};

MusicPlayerFacade* MusicPlayerFacade::instance = nullptr;