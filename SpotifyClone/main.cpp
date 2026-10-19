#include "MusicPlayerApplication.hpp"

using namespace std;

int main() {
    try {
        auto app = MusicPlayerApplication::getInstance();

        // Populate song library
        app->createSongInLibrary("Kesariya", "Arijit Singh", "/music/kesariya.mp3");
        app->createSongInLibrary("Chaiyya Chaiyya", "Sukhwinder Singh", "/music/chaiyya_chaiyya.mp3");
        app->createSongInLibrary("Tum Hi Ho", "Arijit Singh", "/music/tum_hi_ho.mp3");
        app->createSongInLibrary("Jai Ho", "A. R. Rahman", "/music/jai_ho.mp3");
        app->createSongInLibrary("Barbadiyan", "Arijit Singh", "/music/barbadiyan.mp3");

        // Create playlist and all songs
        app->createPlaylist("My Favorite Songs");
        app->addSongToPlaylist("My Favorite Songs", "Kesariya");
        app->addSongToPlaylist("My Favorite Songs", "Chaiyya Chaiyya");
        app->addSongToPlaylist("My Favorite Songs", "Tum Hi Ho");
        app->addSongToPlaylist("My Favorite Songs", "Barbadiyan");

        // Connect audio device
        app->connectAudioDevice(DeviceType::BLUETOOTH);

        // Play/pause a single song
        app->playSingleSong("Kesariya");
        app->pauseCurrentSong("Kesariya");
        app->playSingleSong("Kesariya");


        // Sequential Play
        app->selectPlayStrategy(PlayStrategyType::SEQUENTIAL);
        app->loadPlaylist("My Favorite Songs");
        app->playAllTracksInPlaylist();

        // Random Play
        app->selectPlayStrategy(PlayStrategyType::RANDOM);
        app->loadPlaylist("My Favorite Songs");
        app->playAllTracksInPlaylist();


        // Custom Queue Play
        app->selectPlayStrategy(PlayStrategyType::CUSTOM_QUEUE);
        app->loadPlaylist("My Favorite Songs");
        app->queueSongNext("Chaiyya Chaiyya");
        app->queueSongNext("Tum Hi Ho");
        app->playAllTracksInPlaylist();

        // Play prev song in sequential order
        app->selectPlayStrategy(PlayStrategyType::SEQUENTIAL);
        app->loadPlaylist("My Favorite Songs");
        app->playAllTracksInPlaylist();
        app->playPreviousTrackInPlaylist();
        app->playPreviousTrackInPlaylist();
        app->playPreviousTrackInPlaylist();

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}