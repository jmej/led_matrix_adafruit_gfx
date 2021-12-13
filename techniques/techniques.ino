// Adafruit_NeoMatrix GFX examples for an 8 x 16 neopixel display
//bitmap conversion tool: http://javl.github.io/image2cpp/
//pixel art generation tool: https://www.pixilart.com/draw?ref=home-page

//Jesse Mejia 2021

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 1
int width = 32;
int height = 8;

//global variables for bouncing ball demo
int locX = 0;
int locY = 0;
float xSpeed;
float ySpeed;

// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_GRBW    Pixels are wired for GRBW bitstream (RGB+W NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)


// Example for NeoPixel Shield.  In this application we'd like to use it
// as a 5x8 tall matrix, with the USB port positioned at the top of the
// Arduino.  When held that way, the first pixel is at the top right, and
// lines are arranged in columns, progressive order.  The shield uses
// 800 KHz (v2) pixels that expect GRB color data.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(width, height, PIN,  NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG, NEO_GRB + NEO_KHZ800);


// 'pixilart-drawing', 8x32px
const unsigned char image [] PROGMEM = {
  0xff, 0xff, 0xff, 0xff, 0xf8, 0xff, 0x87, 0xfe, 0xe2, 0x7f, 0x73, 0xfc, 0xef, 0x7e, 0x7b, 0xfd, 
  0xcf, 0x3e, 0xfb, 0xf9, 0xdf, 0xbc, 0xfd, 0xf3, 0x9f, 0xc3, 0xfc, 0x07, 0xbf, 0xff, 0xff, 0xff
};


void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(matrix.Color(0, 0, 255));

  //gives bouncing ball demo a starting position
  locX = random(width);
  locY = random(height);
  xSpeed = random(2);
  ySpeed = 1;
}

int x  = matrix.width();
int pass = 0;

void loop() {
  matrix.fillScreen(0);
  
  //text example
//  matrix.setCursor(x, 0);
//  matrix.print(F("Howdy"));
//  if(--x < -36) {
//    x = matrix.width();
//    if(++pass >= 3) pass = 0;
//    matrix.setTextColor(matrix.Color(0, 0, 255));
//  }

//pink pixel noise
//  for (int i = 0; i < 128; i++){
//    matrix.drawPixel(int(random(width)), int(random(height)), matrix.Color(255, 0, 255));
//  }

//random color lines
//  for (int i = 0; i < 10; i++){
//    matrix.drawLine(int(random(width)), int(random(height)), int(random(width)), int(random(height)), matrix.Color(random(255), random(255), random(255)));
//  }

//random blue/green squares
//  for (int i = 0; i < 10; i++){
//    matrix.drawRect(random(width), random(height), i*1, i*1, matrix.Color(0, random(255), random(255)));
//    //matrix.fillRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t color);
//  }

//bouncing ball 
  locX = locX + xSpeed;
  locY = locY + ySpeed;
  if (locX > width-5 || locX < 0+5){
    xSpeed = xSpeed * -1; //change postive to negative to or vice versa to change directions
  }
  if (locY > height || locY < 0){
    ySpeed = ySpeed * -1; //change postive to negative to or vice versa to change directions
  }
  matrix.drawCircle(locX, locY, 3, matrix.Color(100, 0, 200));
  matrix.fillCircle(locX, locY, 2, matrix.Color(0, 100, 100));

//bitmaps
//  matrix.drawBitmap(0, 0, image, width, height, matrix.Color(255, 0, 255));
  


  matrix.show();
  delay(100);
}
