#include <Arduino.h>

/*
 *
 * 1. SAVE BITMAP AS 1BIT COLOUR in paint.net
 * 2. Run: bmp2hex.py -i -x <BITMAP FILE>
 * 3. Copy paste output into sketch.
 * 
 */

const uint8_t arrow_left[] PROGMEM   =  {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xc7, 0xff, 0xff,
    0xff, 0x87, 0xff, 0xff, 0xff, 0x07, 0xff, 0xff, 0xfe, 0x07, 0xff, 0xff, 0xfc, 0x07, 0xff, 0xff,
    0xf8, 0x07, 0xff, 0xff, 0xf0, 0x07, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x03,
    0xc0, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x03, 0xf0, 0x07, 0xff, 0xff, 0xf8, 0x07, 0xff, 0xff,
    0xfc, 0x07, 0xff, 0xff, 0xfe, 0x07, 0xff, 0xff, 0xff, 0x07, 0xff, 0xff, 0xff, 0x87, 0xff, 0xff,
    0xff, 0xc7, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

const uint8_t arrow_right[] PROGMEM   =  {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xe3, 0xff,
    0xff, 0xff, 0xe1, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xe0, 0x7f, 0xff, 0xff, 0xe0, 0x3f,
    0xff, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xe0, 0x0f, 0xc0, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x03,
    0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x07, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xe0, 0x1f,
    0xff, 0xff, 0xe0, 0x3f, 0xff, 0xff, 0xe0, 0x7f, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xe1, 0xff,
    0xff, 0xff, 0xe3, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

const uint8_t arrow_up[] PROGMEM   =  {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xfc, 0x3f, 0xff,
    0xff, 0xf8, 0x1f, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xe0, 0x07, 0xff, 0xff, 0xc0, 0x03, 0xff,
    0xff, 0x80, 0x01, 0xff, 0xff, 0x00, 0x00, 0xff, 0xfe, 0x00, 0x00, 0x7f, 0xfc, 0x00, 0x00, 0x3f,
    0xf8, 0x00, 0x00, 0x1f, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff,
    0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff,
    0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff,
    0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff,
    0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

const uint8_t arrow_down[] PROGMEM   =  {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff,
    0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff,
    0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff,
    0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff,
    0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xf8, 0x00, 0x00, 0x1f,
    0xfc, 0x00, 0x00, 0x3f, 0xfe, 0x00, 0x00, 0x7f, 0xff, 0x00, 0x00, 0xff, 0xff, 0x80, 0x01, 0xff,
    0xff, 0xc0, 0x03, 0xff, 0xff, 0xe0, 0x07, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xf8, 0x1f, 0xff,
    0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

const uint8_t default_screen[] PROGMEM   =  {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x07, 0xff,
    0xff, 0xe0, 0x07, 0xff, 0xff, 0xe0, 0x07, 0xff, 0xff, 0xe0, 0x07, 0xff, 0xff, 0xe0, 0x07, 0xff,
    0xff, 0xe0, 0x07, 0xff, 0xff, 0xe0, 0x07, 0xff, 0xff, 0xe0, 0x07, 0xff, 0xff, 0xe0, 0x07, 0xff,
    0xff, 0xe0, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};