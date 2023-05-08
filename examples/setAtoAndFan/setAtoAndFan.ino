/*****************************************************************
File:        setAtoAndFan
Description:  Before power on, turn the two digit dial switch of the module to water detection disable. 
              After initializing the module, configure the atomization power as 10W. After the completion of sacning frequency  (3.2s) ,
              configure the fan as half power
******************************************************************/
#include <BM52D5121-1.h>
BM52D5121_1 Atomize(7,6);//rxPin 7 , txPin 6, Please comment out this line of code if you don't use software Serial
//BM52D5121_1 Atomize(&Serial1);//Please uncomment out this line of code if you use HW Serial1 on BMduino
//BM52D5121_1 Atomize(&Serial2);//Please uncomment out this line of code if you use HW Serial2 on BMduino
//BM52D5121_1 Atomize(&Serial3);//Please uncomment out this line of code if you use HW Serial3 on BMduino
//BM52D5121_1 Atomize(&Serial4);//Please uncomment out this line of code if you use HW Serial4 on BMduino
void setup() {
    Atomize.begin(9600);
    Serial.begin(9600);
    if(Atomize.setAtoPower(0x20)==0)//设置雾化功率
    {
      Serial.println("atomize power is 10W");
    }
    delay(3200);
    if(Atomize.setFanPower(0x01)==0)//设置风扇功率
    {
    Serial.println("fan power is half power");
    }
}

void loop() {
 
}

  

  
