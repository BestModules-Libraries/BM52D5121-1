/*****************************************************************
File:         setRGB
Description:  After configuring atomization and fan power, 
              use the serial monitor to send corresponding instructions to control the mode and brightness of RGB.
******************************************************************/
#include <BM52D5121-1.h>
BM52D5121_1 Atomize(7,6);//rxPin 7 , txPin 6, Please comment out this line of code if you don't use software Serial
//BM52D5121_1 Atomize(&Serial1);//Please uncomment out this line of code if you use HW Serial1 on BMduino
//BM52D5121_1 Atomize(&Serial2);//Please uncomment out this line of code if you use HW Serial2 on BMduino
//BM52D5121_1 Atomize(&Serial3);//Please uncomment out this line of code if you use HW Serial3 on BMduino
//BM52D5121_1 Atomize(&Serial4);//Please uncomment out this line of code if you use HW Serial4 on BMduino
uint8_t normal[4]={0x03,0x00, 0x80,0x80};//Normal RGB data
uint8_t breathe[4]={0x32,0x80,0x40,0x00};//Breathing lamp RGB data
uint8_t streamer[4]={0x01,0x00,0x74,0x00};//Streamer RGB data
void setup() {
    Atomize.begin(9600);
    Serial.begin(9600);
    if(Atomize.setAtoPower(0x11)==0)
    {/*Write atomization power data,atomize power is 7.5W*/
      Serial.println("atomize power is 7.5W  ");    
    }
     delay(3200);
    if(Atomize.setFanPower(0x01)==0)
    { /*Write fan data,fan power is half power*/
     Serial.println("fan power is half power  ");   
    }
}
void loop() 
{
  if(Atomize.setRGB(normal)==0)
  { 
     Serial.println("Start normal light mode");
  }
  delay(30000);
  if(Atomize.setRGB(breathe)==0)
  {
    Serial.println("Start breathing light Mode");
  }
  delay(30000);
  if(Atomize.setRGB(streamer)==0)
  {
    Serial.println("Start Streaming light Mode");
  }
  delay(30000);
}
     
