#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     4
#define ADRESS      0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int textSize = 3;

void OLED_init() {
    display.begin(SSD1306_SWITCHCAPVCC, ADRESS);
    display.setTextSize(textSize);
    display.setTextColor(SSD1306_WHITE);
    display.clearDisplay();
}

void OLED_displayNumber(int num) {
    int n = num;
    int m = 1;
    while(n / 10 != 0) {
        n /= 10;
        m++;
    }
    int x = SCREEN_WIDTH / 2 - m * 17 / 2;
    display.clearDisplay();
    display.setCursor(x, 22);
    display.println(num);
    display.display();
}

void OLED_clear() {
    display.clearDisplay();
    display.display();
}