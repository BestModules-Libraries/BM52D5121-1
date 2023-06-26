/*****************************************************************
File:             BM52D5121-1.h
Author:           BESTMODULES
Description:      Define classes and required variables
History：         
V1.0.1-- initial version；2023-03-08；Arduino IDE : v1.8.13
******************************************************************/

#ifndef  BM52D5121_1_h_
#define  BM52D5121_1_h_
#include <Arduino.h>
#include <SoftwareSerial.h>

#define  UART_BAUD 9600
#define  ADDRESSHIGH  0X31
#define  ADDRESSLOW  0X02
#define  READ_OK   0
#define  READ_ERROR   1
#define  HEADER  0X55
#define  CHECK_OK        0
#define  CHECK_ERROR     1
#define  TIMEOUT_ERROR   2

//fan Power
#define  FAN_POWER_FULL 0X00
#define  FAN_POWER_HALF 0X01
#define  FAN_POWER_OFF  0X20

//read data command
#define  COMMAND_READWATERLEVEL 0X81
#define  COMMAND_READWATERCALBRATION  0X82
#define  COMMAND_READPOWERSTATUS  0X83
#define  COMMAND_READFANSTATUS   0X84
#define  COMMAND_READRGBDATA     0X86
#define  COMMAND_READTIMER       0X87
#define  COMMAND_READVERSION      0X89
#define  COMMAND_READMODULAR      0X8A


//write data command
#define  COMMAND_WRITEWATERCALBRATION  0X02
#define  COMMAND_WRITEPOWERSTATUS  0X03
#define  COMMAND_WRITEFANSTATUS   0X04
#define  COMMAND_WRITESCANFREQUENCY    0X05
#define  COMMAND_WRITERGBDATA     0X06
#define  COMMAND_WRITETIMER       0X07
#define  COMMAND_SLEEP         0X08
#define  COMMAND_RESET         0X0b
#define  EMPTYCUP_CALIBRATION     0X01
#define  TENMILLIMETERSCUP_CALIBRATION     0X02

 class BM52D5121_1
 {
    public:
    BM52D5121_1(HardwareSerial*theSerial=&Serial);
    BM52D5121_1(uint8_t rxPin,uint8_t txPin);
    void begin(uint32_t baud=UART_BAUD); 
    //read  
    uint8_t readWaterValue();
    uint8_t readWaterThreshold();
    uint8_t getAtoPower();
    uint8_t getFanPower();
    uint8_t getRGB(uint8_t buff[]);
    uint16_t getTimer();
	  uint16_t getFWVer();
	  uint8_t getModuleStatus();
     
    //write
    uint8_t calibrateWaterLevel(uint8_t cmd);
    uint8_t setAtoPower(uint8_t power);
    uint8_t setFanPower(uint8_t power);
    uint8_t setScanFrequency();
    uint8_t setRGB(uint8_t buff[]);
    uint8_t setTimer(uint16_t time);    
    //set
    uint8_t sleep();  
	uint8_t reset(); 

    
   private:
    void writeBytes(uint8_t wbuf[], uint8_t wlen);
    uint8_t readBytes(uint8_t rbuf[], uint8_t rlen, uint16_t timeout);
    uint8_t readData(uint8_t *buff, uint8_t command,uint8_t datalen);
    void writeData(uint8_t *buff, uint8_t command, uint8_t datalength);
    void writeData(uint8_t buff, uint8_t command);
	  void writeData( uint8_t command);
    uint8_t checksum;
    uint8_t data1;
    uint8_t cycletimes;
    uint8_t _rxPin;
    uint8_t _txPin;
    HardwareSerial*_serial =NULL;
    SoftwareSerial *_softSerial =NULL;
 };
#endif
