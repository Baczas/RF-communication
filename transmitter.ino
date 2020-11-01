#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

unsigned long current_time = 0;
unsigned long prev_time = 0;
unsigned long delta_time = 0;
// MENU BUTTON pin is D0

// Software SPI
//Adafruit_PCD8544 display = Adafruit_PCD8544(CLK, DIN, DC, L.CE, RST);
Adafruit_PCD8544 display = Adafruit_PCD8544(4,5,6,7,8);

//Radio activiation
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

//data which will be sended
struct Data_Package {
  byte VRX1;      //joystick 1 (top/down)
  byte VRY1;      //joystick 1 (left/right)
  byte SW1;       //JS 1 button
  byte VRX2;      //joystick 2 (top/down)
  byte VRY2;      //joystick 2 (left/right)
  byte SW2;       //JS 2 button
  byte SWITCH1;   //toggle switch 1 
  byte SWITCH2;   // toggle switch 2
  byte POT;       //potentiometer
  byte MENUdata;  //variable from menu
};
Data_Package data;


void setup() {
  //Serial.begin(9600);
  display.begin();                          //turn on display
  display.setContrast(30);                  //set contrast from 0 to 127
  display.clearDisplay();                   //clear display
  
  radio.begin();
  radio.openWritingPipe(address); 
  radio.setPALevel(RF24_PA_MAX);        //set RF gain as high  
  radio.stopListening();

  
 //digital pins setup
  pinMode(3, OUTPUT); //LCD BRIGHTNESS
  pinMode(0, INPUT); //MENU BUTTON
  pinMode(A5, INPUT_PULLUP); //SW2
  
  // Set initial default values
  data.VRX1=127;       //joystick 1
  data.VRY1=127;
  data.SW1=1;
  data.VRX2=127;       //joystick 2
  data.VRY2=127;  
  data.SW2=1;
  data.SWITCH1=1;    //toggle switch 1
  data.SWITCH2=1;    // toggle switch 2
  data.POT=127;        //potentiometer
  data.MENUdata=0;   //variable from menu

}

void loop() {
  data.VRX1 = map(analogRead(A3), 0, 1023, 255, 0); // Convert from 0 to 1023 into a BYTE value from 0 to 255
  data.VRY1 = map(analogRead(A2), 0, 1023, 0, 255);
  data.VRX2 = map(analogRead(A6), 0, 1023, 0, 255); 
  data.VRY2 = map(analogRead(A7), 0, 1023, 0, 255);
  data.POT = map(analogRead(A4), 0, 1023, 0, 255);

  data.SW1=digitalRead(A1);
  data.SW2=digitalRead(A5);

  radio.write(&data, sizeof(Data_Package));


  //DISPLAY  
  display.setTextSize(1);                   //set font size 
  display.setTextColor(BLACK);              //set font color 
  display.setCursor(5,0);                   //set currsor in position (5,0)
  display.print("VRX1: ");
  display.print(data.VRX1);
  
  display.setCursor(5,10);                   
  display.print("VRY1: ");
  display.print(data.VRY1);

  display.setCursor(5,20); 
  display.print("VRX2: ");    
  display.print(data.VRX2);

  display.setCursor(5,30);
  display.print("VRY2: ");   
  display.print(data.VRY2);
  
  
  display.display();
  delay(100);  //this schould be changed to millis 
   
  display.clearDisplay();                   //clear display
}

void startup_screen() {

}
