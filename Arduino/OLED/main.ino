#include <SoftwareSerial.h>

int master_RX = 8;
int master_TX = 9;
int master_bitRate = 9800;
int balance = 0;
int b = 0;
int lastTime = 0;
int status = 0;
int data;

SoftwareSerial master(master_RX, master_TX);

void setup() {
    master.begin(master_bitRate);
    OLED_init();
}

void loop() {
    if(master.available()) {
        data = master.read();
        if(status == 0) {
            status = data;
        }
        else if(status == 1) {
            if(data < 10) {
                balance = balance * 10 + data;
            }
            else {
                while(balance > 0) {
                    b = b * 10 + (balance % 10);
                    balance /= 10;
                }
                OLED_displayNumber(b);
                delay(10000);
                balance = 0;
                b = 0;
                status = 0;
                OLED_clear();
            }
        }
    }
}