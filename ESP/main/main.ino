#include <WiFi.h>
#include <HTTPClient.h>
#include <inttypes.h>
#include <stdio.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>

HardwareSerial arduino(2);

const char URL[] = "https://nfc-history.herokuapp.com/";
uint64_t chipID;
int status = 0;
int idm[8];
int idm_counter = 0;
int history[20][16];
int history_counter_i = 0;
int history_counter_j = 0;
int balance = 0;
int b_counter = 0;


/*
void InitializeWiFi() {
    WiFi.begin(SSID, PASSWORD);
    Serial.printf("Connecting to the WiFi AP: %s\n", SSID);

    while(WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(100);
    }

    Serial.println("connected.");
    Serial.print("IP address:");
    Serial.println(WiFi.localIP());
}
*/


void configModeCallback(WiFiManager *wifiManager) {
    Serial.println(WiFi.softAPIP());
    Serial.println(wifiManager->getConfigPortalSSID());
    Serial.println(wifiManager->getConfigPortalPSWD());
}


void setChipID(uint64_t _chipID) {
    chipID = _chipID;
    Serial.printf("ESP32 Chip ID = %04X",(uint16_t)(chipID>>32));//print High 2 bytes
	Serial.printf("%08X\n",(uint32_t)chipID);//print Low 4bytes.
}

void setup() {
    Serial.begin(115200);
    arduino.begin(9600);

    
    WiFiManager wifiManager;
    WiFiManagerParameter customEmailAddress("emailAddress", "e-mail", "", 30);
    wifiManager.setAPCallback(configModeCallback);
    wifiManager.addParameter(&customEmailAddress);
    wifiManager.autoConnect("nfchistory", "415411");
    
    setChipID(ESP.getEfuseMac());

    char email[30];
    strcpy(email, customEmailAddress.getValue());
    Serial.printf("%s\n", email);
    char cpy_url[1024];
    sprintf(cpy_url, "%s?chipID=%04X%08X&email=%s&dataID=2", URL, (uint16_t)(chipID>>32), (uint32_t)chipID, email);
    HTTPClient http;
    http.begin(cpy_url);
    Serial.printf("%s\n", cpy_url);
    Serial.printf("Response: %d\n", http.GET());
    //InitializeWiFi();

    
}

void loop() {
    if(arduino.available()) {
        int data = arduino.read();
        if(status == 0)
            status = data;
        else if(status == 1) {
            if(idm_counter == 0)
                Serial.println("IDM");
            idm[idm_counter] = data;
            Serial.printf("%x ",data);
            idm_counter++;
            if(idm_counter > 7) {
                Serial.println();
                idm_counter = 0;
                status = 0;
            }
        }
        else if(status == 2) {
            Serial.println(data);
            if(data < 10) {
                int c = 1;
                for(int i = 0;i < b_counter;i++) {
                    c = c * 10;
                }
                b_counter++;
                balance += c * data;
            }
            else {
                /*char str_idm[265] = "";
                for(int i = 0;i < 8;i++) {
                    sprintf(str_idm, "%s%02X", str_idm, idm[i]);
                }
                char cpy_url[1024];
                sprintf(cpy_url, "%s?chipID=%04X%08X&idm=%s&balance=%d&dataID=0", URL, (uint16_t)(chipID>>32), (uint32_t)chipID, str_idm, balance);
                HTTPClient http;
                http.begin(cpy_url);
                Serial.printf("%s\n", cpy_url);
                Serial.printf("Response: %d\n", http.GET());
                arduino.write(1);*/
                //balance = 0;
                status = 0;
                b_counter = 0;
            }
        }
        else if(status == 3) {
            history[history_counter_i][history_counter_j] = data;
            Serial.printf("%x ",data);
            history_counter_j++;
            if(history_counter_j > 15) {
                Serial.println();
                history_counter_i++;
                history_counter_j = 0;
            }
            if(history_counter_i > 19) {
                char str_idm[265] = "";
                for(int i = 0;i < 8;i++) {
                    sprintf(str_idm, "%s%02X", str_idm, idm[i]);
                }
                if(1) {
                    char cpy_url[1024];
                    sprintf(cpy_url, "%s?chipID=%04X%08X&idm=%s&balance=%d&dataID=0", URL, (uint16_t)(chipID>>32), (uint32_t)chipID, str_idm, balance);
                    HTTPClient http;
                    http.begin(cpy_url);
                    Serial.printf("%s\n", cpy_url);
                    Serial.printf("Response: %d\n", http.GET());
                    balance = 0;
                }
                
                for(int i = 0;i < 20;i++) {
                    char str_history[256] = "";
                    for(int j = 0;j < 16;j++) {
                        sprintf(str_history, "%s%02X", str_history, history[i][j]);
                    }
                    char cpy_url[1024];
                    sprintf(cpy_url, "%s?chipID=%04X%08X&idm=%s&history=%s&dataID=1", URL, (uint16_t)(chipID>>32), (uint32_t)chipID, str_idm, str_history);
                    HTTPClient http;
                    http.begin(cpy_url);
                    Serial.printf("%s\n", cpy_url);
                    Serial.printf("Response: %d\n", http.GET());
                }
                //arduino.write(1);
                idm_counter = 0;
                history_counter_i = 0;
                status = 0;
            }
        }
        
    }
}