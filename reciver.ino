#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

Servo servo1; 
Servo servo2; 
Servo servo3; 

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

struct Data_Package {
  byte VRX1;      //joystick 1
  byte VRY1;
  byte SW1;
  byte VRX2;      //joystick 2
  byte VRY2;
  byte SW2;
  byte SWITCH1;   //toggle switch 1
  byte SWITCH2;   // toggle switch 2
  byte POT;       //potentiometer
  byte MENUdata;  //variable from menu
 
};
Data_Package data; //Create a variable with the above structure

 int pos1=90;
 int pos2=90;
 int pos3=90;
int button=1;
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  data.VRX1 = 127; 
  data.VRY1 = 127;
  data.VRX2 = 127; 
  data.VRY2 = 127;

  servo1.attach(3);
  servo2.attach(4);
  servo3.attach(5);


}
void loop() {
  
  if (radio.available()) {
    byte SW1;
    radio.read(&data, sizeof(Data_Package));
    
    Serial.print("VRX1: ");
    Serial.print(data.VRX1);
    pos1=map(data.VRX1, 0, 255, 0, 180);
   
    servo1.write(pos1);
    
    Serial.print("; VRY1: ");
    Serial.print(data.VRY1);
    pos2=map(data.VRY1, 0, 255, 0, 180);
    servo2.write(pos2);
    
    Serial.print("VRX2: ");
    Serial.print(data.VRX2);
    pos3=map(data.VRX2, 0, 255, 0, 180);
    servo3.write(pos3);
    
    Serial.print("; VRY2: ");
    Serial.println(data.VRY2);
    delay(100);
  }
}
