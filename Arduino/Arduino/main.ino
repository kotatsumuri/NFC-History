#include <SoftwareSerial.h>

#include "NFC.h"
#include "Sound.h"

int toPC_RX = 11;
int toPC_TX = 10;
int toPC_bitRate = 9600;
int oled_RX = 9;
int oled_TX = 8;
int oled_bitRate = 9800;
int toESP_RX = 12;
int toESP_TX = 13;
int toESP_bitRate = 9600;
int balance;
int lasttime = 0;

SoftwareSerial toPC(toPC_RX, toPC_TX); //RX, TX
SoftwareSerial toESP(toESP_RX, toESP_TX);
SoftwareSerial oled(oled_RX, oled_TX);
Sound sound(4,3,9600,30);
SoftwareSerial player(sound.RX, sound.TX);
NFC nfc;

void sendNFCIDM() {
    toPC.print("IDM:");
    toESP.write(1);
    for(int i = 0;i < 8;i++) {
        toPC.print(nfc.rcs620s.idm[i], HEX);
        toPC.print(' ');
        toESP.write(nfc.rcs620s.idm[i]);
    }
    toPC.print('\n');
}

void sendNFCBalance() {
    toPC.print("Balance:");
    toESP.write(2);
    oled.write(1);
    int cpbalance = balance;
    while(cpbalance > 0) {
        toPC.write(cpbalance % 10);
        toESP.write(cpbalance % 10);
        oled.write(cpbalance % 10);
        cpbalance /= 10;
    }
    toPC.print('\n');
    toESP.write(10);
    oled.write(10);
}

void sendNFCHistory() {
    toESP.write(3);
    for(int i = 0;i < nfc.HISTORY_SIZE;i++) {
        for(int j = 0;j < nfc.HISTORY_BYTE;j++) {
            toPC.print(nfc.history[i][j], HEX);
            toPC.print(' ');
            toESP.write(nfc.history[i][j]);
        }
        toPC.print('\n');
    }
}

void setup() {
    toPC.begin(toPC_bitRate);
    oled.begin(oled_bitRate);
    toESP.begin(toESP_bitRate);
    player.begin(sound.bitrate);
    sound.setSerial(&player);
    pinMode(LED_BUILTIN, OUTPUT);
    nfc.initDevice();
    toPC.println("RCS620S was initialized.");
}

void loop() {
    if(nfc.getHistory()) {
        toPC.println("Can read NFC history info");
        digitalWrite(LED_BUILTIN, HIGH);
        sound.canRead();
        balance = nfc.getBalance();
        sendNFCIDM();
        sendNFCBalance();
        sendNFCHistory();
    }
    else {
        digitalWrite(LED_BUILTIN, LOW);
        delay(100);
    }
}

