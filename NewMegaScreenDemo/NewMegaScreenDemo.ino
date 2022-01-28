#include <EEPROM.h>
#include <memorysaver.h>
#include <UTFT.h>
#include "URCFont.c"
// ------------------------------------------------------------
#define BAUD  9600
#define EEPROMSTART 256
#define SIG1  '5'
#define SIG2  'A'                   //Set to other than 'A' to force re-config
// ------------------------------------------------------------
// Declare which fonts we will be using
extern uint8_t SmallFont[];         //Almost everything
extern uint8_t BigFont[];           //Splash screen
//extern uint8_t URCLCDFont[];        //Frequency display
// ------------------------------------------------------------
int       eeAddr = 256;               //EEPROM address to start reading from
// ------------------------------------------------------------
//  Function prototypes
void splash(void);                //Show splash screen on startup
void drawLabels();                //Draw the outlines of the controls
void drawControls(void);          //Draw all the various widgets
void lblInBuf(void);              //Draw a box for displaying the Serial input buffer
void lblOutBuf(void);             //Draw a box for displaying the Serial output buffer
// ------------------------------------------------------------
//  Initialize the LCD
//
// Set the pins to the correct ones for your development shield
// ------------------------------------------------------------
// Standard Arduino Uno/2009 shield            : <display model>,A5,A4,A3,A2
// Standard Arduino Mega/Due shield            : <display model>,38,39,40,41
//UTFT LCD(ITDB32S,38,39,40,41);
//UTFT LCD(TYPE    ,RS,WR,CS,RST);
UTFT LCD(ILI9341_16,38,39,40,41);
// ------------------------------------------------------------

void setup() {
  LCD.InitLCD(LANDSCAPE);               // Setup the LCD
  LCD.setFont(SmallFont);

  Serial.begin(BAUD, SERIAL_8N1);       // Setup the Serial port

  while(!Serial) {
    //Wait for serial port to be available
  }

   randomSeed(analogRead(0));           // Seed random number generator

   splash();                            // Show splash screen with delay
   
  Serial.flush();                       // Discard any spurious serial input
}

void loop() {
  int x = LCD.getDisplayXSize();
  int y = LCD.getDisplayYSize();
  Serial.print("X = "); Serial.println(x);
  Serial.print("Y = "); Serial.println(y);
  
  LCD.clrScr();                         // Clear the screen and draw the frame

  drawLabels();
  
  LCD.setColor(VGA_TEAL);
  LCD.setBackColor(VGA_TRANSPARENT);
  LCD.setFont(SmallFont);
  LCD.print("X:", 0, 50);
  LCD.print("Y:", 0, 65); 
  LCD.setFont(LCDSmall);              // This font has only numerics
  LCD.printNumI(x, 35, 50);
  LCD.printNumI(y, 35, 65);
  

  while (1) {
  }
}

//  void splash(void)
//  show a little splash screen on startup
void splash(void)
{
  uint8_t* cf = LCD.getFont();
  LCD.setFont(BigFont);
  LCD.clrScr();
  LCD.setColor(VGA_WHITE);        //Print some white text on a black background
  LCD.setBackColor(VGA_BLACK);
  
  LCD.print("Mega2560 Up", CENTER, 115);

  LCD.setFont(cf);
  delay(2000);
}

//Draw the various graphic elements on the screen along with their contents
void drawControls(void)
{
  //Display the preset Rx/Tx frequencies
  //showChannel();
  //showSqLevel();    //Show current squelch level set by remote
  //showTxMode();     //Show current Tx mode AM/FM
  //showBeacon();     //Indicate if radio is in beacon mode
  //showSpkr();       //Show speaker enabled/disabled
  //showOnScan();     //Show whether current channel is on scan list
  //showMode();       //Show current Rx mode (AM/FM)
  //showRxTx();       //Show Tx/Rx state
  //showPwr();        //Show current transmit power level
  //showCTPT();       //Show Plain/Cipher Text mode
  //showKey();        //Indicate tranceiver RF state
}

//Draw the labels for the various controls
void drawLabels(void)
{
  lblInBuf();         //Box to show command sent from host
  lblOutBuf();        //Box to show our response (if any)
  //lblSqLevel();       //Draw a box showing current squelch level
  //lblSql();           //Draw a box to show current squelch state (SQL/UNSQL)
  //lblPwr();           //Draw a box to show current power level
  //lblSpkr();          //Draw a box to show current spkr state (enabled/disabled)
  //lblMode();          //Draw a box showing the current Rx mode (AM/FM)
  //lblTxMode();        //Draw a box showing the current Tx mode (AM/FM)
  //lblRxTx();          //Draw a box indicating displayed freq is Rx or Tx
  //lblKey();           //Draw a round button showing RF state (green = RX, red = TX)
  //lblCTPT();          //Draw a box to show cipher state
  //lblScan();          //Draw a box to show scan mode active/inactive
  //lblOnScan();        //Draw a box showing whether or not the current channel is in the scan list
  //lblBeacon();        //Draw a box to show beacon mode (active/inactive)
}

//Draw a box for displaying the Serial input buffer
//Labelled 'inBuf' in above diagram
void lblInBuf(void) {
  word obc = LCD.getBackColor();        // get current background color
  word ofc = LCD.getBackColor();        // get current foreground color
  LCD.setColor(VGA_GREEN);              // Draw box in green
  LCD.setBackColor(VGA_BLACK);
  LCD.drawRect(0, 0, 158, 25);          // Draw a long rectangle at the top
  LCD.setColor(ofc);                    // Restore foreground color
  LCD.setBackColor(obc);                // Restore background color
}

//Draw a box for displaying the Serial output buffer
//Labelled 'outBuf' in above diagram
void lblOutBuf(void) {
  word obc = LCD.getBackColor();        // get current background color
  word ofc = LCD.getBackColor();        // get current foreground color
  LCD.setColor(VGA_RED);                // Draw box in green
  LCD.setBackColor(VGA_BLACK);
  LCD.drawRect(160, 0, 319, 25);        // Draw a long rectangle at the top
  LCD.setColor(ofc);                    // Restore foreground color
  LCD.setBackColor(obc);                // Restore background color
}
