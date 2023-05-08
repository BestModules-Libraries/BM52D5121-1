/*****************************************************************
File:         calibrateWaterLevel
Description:  
              loop：poll to obtain serial port data
              Enter 0201 in the Serial monitor and bmduino sends the empty cup calibration command.
              After empty cup calibration, input 0202 in the serial port monitor, bmduino sends the full cup calibration command, 
              and then delay for 1s to read the water detection calibration value
              
              Tip：To send commands using the serial port monitor.  
******************************************************************/
#include <BM52D5121-1.h>
BM52D5121_1 Atomize(7,6);//rxPin 7 , txPin 6, Please comment out this line of code if you don't use software Serial
//BM52D5121_1 Atomize(&Serial1);//Please uncomment out this line of code if you use HW Serial1 on BMduino
//BM52D5121_1 Atomize(&Serial2);//Please uncomment out this line of code if you use HW Serial2 on BMduino
//BM52D5121_1 Atomize(&Serial3);//Please uncomment out this line of code if you use HW Serial3 on BMduino
//BM52D5121_1 Atomize(&Serial4);//Please uncomment out this line of code if you use HW Serial4 on BMduino
  uint8_t i=2;
  uint8_t flag=0;
void setup() {
    Atomize.begin(9600);
    Serial.begin(9600);
    pinMode(8,INPUT_PULLUP);
}
void loop() {
  i=pinRead(8);
  if((i==0)&&(flag!=1))
  {
    if(Atomize.calibrateWaterLevel(0x01)==0)
    {
      Serial.println("Empty cup calibration complete");
      flag=1;
    }
  }
  if((i==1)&&(flag==1)){
    Atomize.calibrateWaterLevel(0x02);
    flag=2;
    Serial.println("Full cup calibration complete");
    delay(1000);
    i=Atomize.getModuleStatus();
    uint8_t a=bitRead(i,1);
    if(a==1){
      Serial.println("Calibration failed");
    } 
    else {
      Serial.println("Calibration success");
    }
  }
 }   

uint8_t pinRead(uint8_t pin)
{
  uint8_t pinnow;
  uint8_t p;
  pinnow=digitalRead(pin);
   for(uint8_t k=0;k<10;){
       delay(6);
       p=digitalRead(pin);
       if(pinnow==p)
       {
          k++;
       }
       else
       {
          k=0;
          pinnow=p;
       }  
   }
   return pinnow;
}

  
