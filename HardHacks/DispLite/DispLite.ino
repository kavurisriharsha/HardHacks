#include <ss_oled.h>

// Arduino Pro Mini
// Pin 8 (0xb0 = PORTB, bit 0)
// Pin 9 (0xb1 = PORTB, bit 1)
// UnexpectedMaker TinyPICO
#define SDA_PIN A4
#define SCL_PIN A5

#define RESET_PIN -1
#define FLIPPED 1
#define INVERTED 0
// Use bit banging to get higher speed output
#define HARDWARE_I2C 0
#define WIDTH 128
#define HEIGHT 64
int rc;
SSOLED oled;

// Use a 1K back buffer to do access more complex features on systems with
// more RAM available. This can work on AVR, but will use most of the RAM
#ifndef __AVR__
static uint8_t ucBuffer[1024];
#endif // __AVR__



void setup() {
  // put your setup code here, to run once:
  uint8_t uc[8];
    
  rc = oledInit(&oled, OLED_128x64, 0x3c, FLIPPED, INVERTED, HARDWARE_I2C, SDA_PIN, SCL_PIN, RESET_PIN, 1000000L);
  if (rc != OLED_NOT_FOUND)
  {
    #ifndef __AVR__
    oledSetBackBuffer(&oled, ucBuffer);
    #endif
    oledFill(&oled, 0,1);
    oledSetContrast(&oled, 127);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  oledFill(&oled, 0,1);
  oledWriteString(&oled, 0,0,0,(char *)"Now with 5 font sizes", FONT_6x8, 0, 1);
  delay(1000);
}
