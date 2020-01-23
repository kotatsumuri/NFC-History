#ifndef SOUND_H_
#define SOUND_H_

#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

class Sound {
    public:
        int CAN_READ;
        int CANT_READ;
        int RX;
        int TX;
        int bitrate;
        Sound(int _RX, int _TX, int _bitrate, int _volume);
        void setSerial(SoftwareSerial *_player);
        void canRead();
        void canNotRead();
    private:
        SoftwareSerial *player;
        DFRobotDFPlayerMini MusicPlayer;
        int volume;
};

#endif //SOUND_H_