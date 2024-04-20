// Source: https://www.disk91.com/2021/projects/iot/use-wio-terminal-as-a-serial-logger/
// Setup prerequisites: https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/
#include "TFT_eSPI.h"
#include "Free_Fonts.h"
TFT_eSPI tft = TFT_eSPI();
 
#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD
#define MAXLINE     1024
#define TFTLINE       18  // number of lines
#define TFTLINEHEIGHT 13  // pixel per line
#define MAXCOLUMN     42  // number of columns + 1 for the buffer
#define TFTCOLUMN (MAXCOLUMN-1) // number of column on TFT screen
#define TFT_XMIN       4 // first char offset
#define TFT_YMIN       3 // first char offset
 
#define INCPTR(v) v = (v+1) & (MAXLINE-1)
#define DECPTR(v) v = (v>0)?(v-1):(MAXLINE-1);
 
 
 
char lineBuffer[MAXLINE][MAXCOLUMN];
int  rdLine;
int  wrLine;
int  cColumn;
unsigned long  totalLineReceived;
boolean scroll;
boolean tftOn;
 
void setup() {
  pinMode(LCD_BACKLIGHT,OUTPUT);
  pinMode(WIO_5S_UP, INPUT_PULLUP);
  pinMode(WIO_5S_DOWN, INPUT_PULLUP);
  pinMode(WIO_5S_LEFT, INPUT_PULLUP);
  pinMode(WIO_5S_RIGHT, INPUT_PULLUP);
  pinMode(WIO_5S_PRESS, INPUT_PULLUP);
  pinMode(WIO_KEY_C, INPUT_PULLUP);
   
  Serial.begin(9600);
   
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK); 
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(1);
  digitalWrite(LCD_BACKLIGHT, HIGH); // TFT on
 
  bzero(lineBuffer,sizeof(lineBuffer));
  rdLine=0;
  wrLine=0;
  cColumn=0;
  totalLineReceived=0;
  scroll=true;
  tftOn=true;
   
}
 
 
// redraw the screen
void printScreen() {
  tft.fillScreen(TFT_BLACK);
  if (!scroll) {
    tft.drawRect(0,0,320,240,TFT_RED);
    tft.drawRect(1,1,319,239,TFT_RED);    
  }
  //tft.fillRect(0, 0, 320, 240, TFT_BLACK);
  int cline=rdLine;
  int yPos = TFT_YMIN;
  for ( int y = 0 ; (y < TFTLINE) && (cline != wrLine) ; y++ ) {
    int x = 0;
    int xPos = TFT_XMIN;
    char c = lineBuffer[cline][x];
    while ( c != '\0' && x <= TFTCOLUMN ) {
      xPos += tft.drawChar(c,xPos,yPos,2);
      x++;
      c = lineBuffer[cline][x];
    }
    yPos+=TFTLINEHEIGHT;
    INCPTR(cline);
  }
}
 
// Return the number of lines to print according to the buffer data
int lineToPrint() {
  if ( wrLine >= rdLine ) {
      // normal case wr is before
      return wrLine - rdLine;
  }
  // wrLine has overflowed but rdLine not Yet
  return ( MAXLINE + wrLine ) - rdLine;
}
 
 
void loop() {
  boolean refresh = false;
  boolean keyPressed = false;
  boolean hasChar = false;
 
  if ( digitalRead(WIO_5S_PRESS) == LOW ) {
    scroll = ! scroll;
    if ( scroll ) {
      rdLine = wrLine;
      // back to the right index (quick & dirty)
      for ( int i = 0 ; i < TFTLINE && i < totalLineReceived ; i++ ) {
        DECPTR(rdLine);
      }
    }
    keyPressed = true;
  } else if ( digitalRead(WIO_5S_UP) == LOW ) {
    if ( rdLine != wrLine ) {
      INCPTR(rdLine);
    }
    keyPressed = true;
  } else if ( digitalRead(WIO_5S_DOWN) == LOW ) {
    if ( rdLine != wrLine ) {
      DECPTR(rdLine);
    }
    keyPressed = true;
  }
  if ( digitalRead(WIO_KEY_C) == LOW ) {
    tftOn = ! tftOn;
    digitalWrite(LCD_BACKLIGHT, ((tftOn)?HIGH:LOW));
    delay(500);
  }
   
  if (keyPressed) {
    refresh=true;
    delay(200);    
  }
 
  if (Serial.available()) {
    hasChar = true;
    tft.fillCircle(310,10,3,TFT_GREEN);
  }
  while (Serial.available()) {
    char c = Serial.read();
    if ( c == '\n' ) {
      lineBuffer[wrLine][cColumn]='\0';
      totalLineReceived++;
      INCPTR(wrLine);
      if ( scroll && lineToPrint() > TFTLINE ) INCPTR(rdLine);
      cColumn = 0;
      if (scroll) refresh=true;
    } else {
      if ( c != '\r' ) {
        lineBuffer[wrLine][cColumn] = c;
        cColumn++;
        if ( cColumn == TFTCOLUMN ) {
          lineBuffer[wrLine][cColumn] = '\0';
          totalLineReceived++;
          INCPTR(wrLine);
          if ( scroll && lineToPrint() > TFTLINE ) INCPTR(rdLine);
          cColumn = 0;
          if (scroll) refresh=true;
        }
      }
    }
  }
  if ( hasChar ) {
    delay(50);
    tft.fillCircle(310,10,3,TFT_BLACK);    
  }
 
  if (refresh && tftOn ) {
    printScreen();
  }
 
}
