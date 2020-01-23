#ifndef NFC_H_
#define NFC_H_

#include <RCS620S.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>

class NFC {
    public:
        int COMMAND_TIMEOUT;
        int PUSH_TIMEOUT;
        int POLLING_INTERVAL;
        int HISTORY_SIZE;
        int HISTORY_BYTE;
        int ayucaFlag;
        int ayucaBalance;
        uint16_t PASSNET_SERVICE_CODE;
        uint16_t AYUCA_SERVICE_CODE;
        uint8_t history[20][16];
        uint8_t ayucaBalanceInfo[16];
        RCS620S rcs620s;
        NFC();
        int getHistory();
        void initDevice();
        int getBalance();
    private:
        int requestService(uint16_t serviceCode);
        int readEncryption(uint16_t serviceCode, uint8_t blockNumber, uint8_t *buf);
};

#endif //NFC_H_