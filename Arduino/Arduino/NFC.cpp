#include "NFC.h"

NFC::NFC() {
    COMMAND_TIMEOUT = 400;
    PUSH_TIMEOUT = 2100;
    POLLING_INTERVAL = 500;
    HISTORY_SIZE = 20;
    HISTORY_BYTE = 16;
    PASSNET_SERVICE_CODE = 0x090F;
    AYUCA_SERVICE_CODE = 0x884B;
    /*
    history = (uint8_t **)calloc(HISTORY_SIZE, sizeof(uint8_t *));
    for(int i = 0;i < HISTORY_SIZE;i++)
        history[i] = (uint8_t *)calloc(HISTORY_BYTE, sizeof(uint8_t));
    */
}

void NFC::initDevice() {
    Serial.begin(115200);
    while(!rcs620s.initDevice()) {}
    rcs620s.timeout = COMMAND_TIMEOUT;
}

int NFC::getHistory() {
    if(rcs620s.polling()) {
        uint8_t buf[RCS620S_MAX_CARD_RESPONSE_LEN];
        if(requestService(PASSNET_SERVICE_CODE)){
            for(int i = 0;i < HISTORY_SIZE;i++) {
                if(requestService(PASSNET_SERVICE_CODE)) {
                    if(readEncryption(PASSNET_SERVICE_CODE, i, buf)) {
                        memcpy(history[i], buf + 12, HISTORY_BYTE);
                    }
                }
            }
        }
        else if() {

        }
        return 1;
    }
    return 0;
}

int NFC::getBalance() {
    uint8_t balance = history[0][11];
    balance = (balance << 8) + history[0][10];
    return (int)balance;
}

int NFC::requestService(uint16_t serviceCode) {
    int ret;
    uint8_t buf[RCS620S_MAX_CARD_RESPONSE_LEN];
    uint8_t responseLen = 0;

    buf[0] = 0x02;
    memcpy(buf + 1, rcs620s.idm, 8);
    buf[9] = 0x01;
    buf[10] = (uint8_t)((serviceCode >> 0) & 0xFF);
    buf[11] = (uint8_t)((serviceCode >> 8) & 0xFF);

    ret = rcs620s.cardCommand(buf, 12, buf, &responseLen);

    if(!ret || (responseLen != 12) || (buf[0] != 0x03) || 
    (memcmp(buf + 1, rcs620s.idm, 8) != 0) || ((buf[10] == 0xff) && (buf[11] == 0xff))) {
        return 0;
    }

    return 1;
}

int NFC::readEncryption(uint16_t serviceCode, uint8_t blockNumber, uint8_t *buf) {
    int ret;
    uint8_t responseLen = 0;

    buf[0] = 0x06;
    memcpy(buf + 1, rcs620s.idm, 8);

    buf[9] = 0x01; // サービス数
    buf[10] = (uint8_t)((serviceCode >> 0) & 0xff);
    buf[11] = (uint8_t)((serviceCode >> 8) & 0xff);
    buf[12] = 0x01; // ブロック数
    buf[13] = 0x80;
    buf[14] = blockNumber;
    
    ret = rcs620s.cardCommand(buf, 15, buf, &responseLen);
    
    if (!ret || (responseLen != 28) || (buf[0] != 0x07) ||
        (memcmp(buf + 1, rcs620s.idm, 8) != 0)) {
        return 0;
    }
    
    return 1;
}