/* 
 * This code controls a 32 by 32 pixel LED matrix connected to an ESP32 Microcontroller via the ESP32-HUB75-MatrixPanel-I2S-DMA library. The device recieves data via Bluetooth using the ArduinoBLE library. 
 * The AnimatedGIF library is used to display GIFs on the LED matrix, while the NONE, UNCERTAIN, PPD, PRW, PSL, RPL, RRD, RSW, SRL, and SPW libraries are used to display different rock-paper-scissors game options on the LED matrix. 
 * A gesture enum is used to track the user's gesture, while the get_random_hand() method is used to get the computer's hand gesture. The writeGesture() method is used to write the gesture data to the LED matrix. 
 * A deviceServiceUuid and deviceServiceCharacteristicUuid are used for Bluetooth connection. The setup() method configures the LED matrix and Bluetooth connection, while the loop() method runs the rock-paper-scissors game.
*/

#include <Arduino.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <Adafruit_GFX.h>
#include <ArduinoBLE.h>
#include <AnimatedGIF.h>

#include <PPD.h>
#include <PRW.h>
#include <PSL.h>
#include <RPL.h>
#include <RRD.h>
#include <RSW.h>
#include <SPW.h>
#include <SRL.h>
#include <SSD.h>
#include <NONE.h>
#include <UNCERTAIN.h>

/*--------------------- MATRIX LILBRARY CONFIG -------------------------*/
#define PANEL_RES_X 32      // Number of pixels wide of each INDIVIDUAL panel module. 
#define PANEL_RES_Y 32     // Number of pixels tall of each INDIVIDUAL panel module.
#define PANEL_CHAIN 1      // Total number of panels chained one to another
 
MatrixPanel_I2S_DMA *dma_display = nullptr;

// Module configuration
HUB75_I2S_CFG mxconfig(
	PANEL_RES_X,   // module width
	PANEL_RES_Y,   // module height
	PANEL_CHAIN    // Chain length
);

enum gesture{ 
  UNCERT    = 0,
  NOTHING   = 1,
  ROCK      = 2,
  PAPER     = 3,
  SCISSORS  = 4
};

const char* deviceServiceUuid = "00001801-0000-1000-8000-00805f9b34fb";
const char* deviceServiceCharacteristicUuid = "00002af7-0000-1000-8000-00805f9b34fb";

int gesture = -1;

BLEService gestureService(deviceServiceUuid); 
BLEByteCharacteristic gestureCharacteristic(deviceServiceCharacteristicUuid, BLERead | BLEWrite);

int LED_BUILTIN = 2;

AnimatedGIF gif;

// Draw a line of image directly on the LCD (taken from: https://github.com/bitbank2/AnimatedGIF/blob/master/examples/ESP32_LEDMatrix_I2S/ESP32_LEDMatrix_I2S.ino )
void GIFDraw(GIFDRAW *pDraw)
{
  uint8_t *s;
  uint16_t *d, *usPalette, usTemp[320];
  int x, y, iWidth;

  usPalette = pDraw->pPalette;
  y = pDraw->iY + pDraw->y; // current line

  s = pDraw->pPixels;
  if (pDraw->ucDisposalMethod == 2) // restore to background color
  {
    for (x = 0; x < iWidth; x++)
    {
      if (s[x] == pDraw->ucTransparent)
        s[x] = pDraw->ucBackground;
    }
    pDraw->ucHasTransparency = 0;
  }
  // Apply the new pixels to the main image
  if (pDraw->ucHasTransparency) // if transparency used
  {
    uint8_t *pEnd, c, ucTransparent = pDraw->ucTransparent;
    int x, iCount;
    pEnd = s + pDraw->iWidth;
    x = 0;
    iCount = 0; // count non-transparent pixels
    while (x < pDraw->iWidth)
    {
      c = ucTransparent - 1;
      d = usTemp;
      while (c != ucTransparent && s < pEnd)
      {
        c = *s++;
        if (c == ucTransparent) // done, stop
        {
          s--; // back up to treat it like transparent
        }
        else // opaque
        {
          *d++ = usPalette[c];
          iCount++;
        }
      }           // while looking for opaque pixels
      if (iCount) // any opaque pixels?
      {
        for (int xOffset = 0; xOffset < iCount; xOffset++)
        {
          dma_display->drawPixel(x + xOffset, y, usTemp[xOffset]);
        }
        x += iCount;
        iCount = 0;
      }
      // no, look for a run of transparent pixels
      c = ucTransparent;
      while (c == ucTransparent && s < pEnd)
      {
        c = *s++;
        if (c == ucTransparent)
          iCount++;
        else
          s--;
      }
      if (iCount)
      {
        x += iCount; // skip these
        iCount = 0;
      }
    }
  }
  else
  {
    s = pDraw->pPixels;
    // Translate the 8-bit pixels through the RGB565 palette (already byte reversed)
    for (x = 0; x < pDraw->iWidth; x++)
    {
      dma_display->drawPixel(x, y, usPalette[*s++]);
    }
  }
} /* GIFDraw() */

const enum gesture get_random_hand() 
{
    int random = std::rand() % 3;
    switch(random) {
      case 0:
        return ROCK;
      case 1:
        return PAPER;
      case 2:
        return SCISSORS;
      default:
        break;
    }
}

/* Receives a gesture, selected by the user, via bluetooth signal, a random gesture is also chosen by the computer, 
 * and it displays an appropriate animation on the 32x32 LED matrix */
void writeGesture(int gesture) {
  Serial.println("- Characteristic <gesture_type> has changed!");

  const enum gesture computer_hand = get_random_hand();
  
   switch (gesture) {
      case ROCK:
        switch(computer_hand) {
          case ROCK:
            if (gif.open((uint8_t*)RRD, sizeof(RRD), GIFDraw))
            {
              Serial.printf("Successfully opened GIF; Canvas size = %d x %d\n", gif.getCanvasWidth(), gif.getCanvasHeight());
              while (gif.playFrame(true, NULL)){}
              gif.close();
            }
            break;
          case PAPER:
            if (gif.open((uint8_t*)RPL, sizeof(RPL), GIFDraw))
            {
              Serial.printf("Successfully opened GIF; Canvas size = %d x %d\n", gif.getCanvasWidth(), gif.getCanvasHeight());
              while (gif.playFrame(true, NULL)){}
              gif.close();
            }
            break;
          case SCISSORS:
            if (gif.open((uint8_t*)RSW, sizeof(RSW), GIFDraw))
            {
              Serial.printf("Successfully opened GIF; Canvas size = %d x %d\n", gif.getCanvasWidth(), gif.getCanvasHeight());
              while (gif.playFrame(true, NULL)){}
              gif.close();
            }
            break;
        }
        Serial.println("* Actual value: ROCK");
        Serial.println(" ");
        break;
      case PAPER:
        switch(computer_hand) {
          case ROCK:
            if (gif.open((uint8_t*)PRW, sizeof(PRW), GIFDraw))
            {
              Serial.printf("Successfully opened GIF; Canvas size = %d x %d\n", gif.getCanvasWidth(), gif.getCanvasHeight());
              while (gif.playFrame(true, NULL)){}
              gif.close();
            }
            break;
          case PAPER:
            if (gif.open((uint8_t*)PPD, sizeof(PPD), GIFDraw))
            {
              Serial.printf("Successfully opened GIF; Canvas size = %d x %d\n", gif.getCanvasWidth(), gif.getCanvasHeight());
              while (gif.playFrame(true, NULL)){}
              gif.close();
            }
            break;
          case SCISSORS:
            if (gif.open((uint8_t*)PSL, sizeof(PSL), GIFDraw))
            {
              Serial.printf("Successfully opened GIF; Canvas size = %d x %d\n", gif.getCanvasWidth(), gif.getCanvasHeight());
              while (gif.playFrame(true, NULL)){}
              gif.close();
            }
            break;
        }
        Serial.println("* Actual value: PAPER");
        Serial.println(" ");
        break;
      case SCISSORS:
        switch(computer_hand) {
          case ROCK:
            if (gif.open((uint8_t*)SRL, sizeof(SRL), GIFDraw))
            {
              Serial.printf("Successfully opened GIF; Canvas size = %d x %d\n", gif.getCanvasWidth(), gif.getCanvasHeight());
              while (gif.playFrame(true, NULL)){}
              gif.close();
            }
            break;
          case PAPER:
            if (gif.open((uint8_t*)SPW, sizeof(SPW), GIFDraw))
            {
              Serial.printf("Successfully opened GIF; Canvas size = %d x %d\n", gif.getCanvasWidth(), gif.getCanvasHeight());
              while (gif.playFrame(true, NULL)){}
              gif.close();
            }
            break;
          case SCISSORS:
            if (gif.open((uint8_t*)SSD, sizeof(SSD), GIFDraw))
            {
              Serial.printf("Successfully opened GIF; Canvas size = %d x %d\n", gif.getCanvasWidth(), gif.getCanvasHeight());
              while (gif.playFrame(true, NULL)){}
              gif.close();
            }
            break;
        }
        Serial.println("* Actual value: SCISSORS");
        Serial.println(" ");
        break;
      case UNCERT:
          if (gif.open((uint8_t*)UNCERTAIN, sizeof(UNCERTAIN), GIFDraw))
          {
            Serial.printf("Successfully opened GIF; Canvas size = %d x %d\n", gif.getCanvasWidth(), gif.getCanvasHeight());
            while (gif.playFrame(true, NULL)){}
            gif.close();
          }
        Serial.println("* Actual value: UNCERTAIN");
        Serial.println(" ");
        break;
      case NOTHING:
        dma_display->clearScreen();
        if (gif.open((uint8_t*)NONE, sizeof(NONE), GIFDraw))
        {
          Serial.printf("Successfully opened GIF; Canvas size = %d x %d\n", gif.getCanvasWidth(), gif.getCanvasHeight());
          while (gif.playFrame(true, NULL)){}
          gif.close();
        }
        Serial.println("* Actual value: NOTHING");
        Serial.println(" ");
        break;
      default:
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(300);                       // wait
        digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
        delay(300);
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(300);                       // wait
        digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
        delay(300);
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(600);                       // wait
        digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
        delay(600);
        break;
    }    
}

/* Initializes the serial connection, displays, gifs, LEDs, and BLE connection. */
void setup() {
  Serial.begin(9600);

  /************** DISPLAY **************/
  Serial.println("...Starting Display");
  dma_display = new MatrixPanel_I2S_DMA(mxconfig);
  dma_display->begin();
  dma_display->setBrightness8(255); //0-255

  gif.begin(LITTLE_ENDIAN_PIXELS);

  while (!Serial);  
  
  pinMode(LED_BUILTIN, OUTPUT);
  
  digitalWrite(LED_BUILTIN, LOW);

  
  if (!BLE.begin()) {
    Serial.println("- Starting Bluetooth® Low Energy module failed!");
    while (1);
  }

  BLE.setLocalName("ESP32 BLE (Peripheral)");
  BLE.setAdvertisedService(gestureService);
  gestureService.addCharacteristic(gestureCharacteristic);
  BLE.addService(gestureService);
  gestureCharacteristic.writeValue(-1);
  BLE.advertise();

  Serial.println("ESP32 BLE (Peripheral Device)");
  Serial.println(" ");
}

/* Continuously polls for a BLE connection and reads the value of the gestureCharacteristic. */
void loop() {
  BLEDevice central = BLE.central();
  Serial.println("- Discovering central device...");
  delay(500);

  if (central) {
    Serial.println("* Connected to central device!");
    Serial.print("* Device MAC address: ");
    Serial.println(central.address());
    Serial.println(" ");

    while (central.connected()) {
      if (gestureCharacteristic.written()) {
         gesture = gestureCharacteristic.value();
         writeGesture(gesture);
       }
    }
    
    Serial.println("* Disconnected to central device!");
  }
}