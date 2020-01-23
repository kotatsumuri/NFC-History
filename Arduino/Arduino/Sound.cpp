#include "Sound.h"

Sound::Sound(int _RX, int _TX, int _bitrate, int _volume) {
    RX = _RX;
    TX = _TX;
    bitrate = _bitrate;
    volume = _volume;
    CAN_READ = 1;
    CANT_READ = 2;
}

void Sound::setSerial(SoftwareSerial *_player) {
    player = _player;
    MusicPlayer.begin(*player);
    MusicPlayer.volume(volume);
}

void Sound::canRead() {
    MusicPlayer.play(CAN_READ);
}

void Sound::canNotRead() {
    MusicPlayer.play(CANT_READ);
}