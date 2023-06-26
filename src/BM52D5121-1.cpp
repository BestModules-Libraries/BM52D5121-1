/*****************************************************************
  File:             BM52D5121-1.cpp
  Author:           BESTMODULES
  Description:      Function to communicate with the module
  History：
  V1.0.1-- initial version；2023-03-08；Arduino IDE : v1.8.13
******************************************************************/
#include  "BM52D5121-1.h"
/**********************************************************
  Description: Select the hardware serial port you need to use
  Parameters:       *theSerial：hardware serial
             BMduino optional:serial(default) serial1/seria2/seria3/seria4
             UNO optional:serial(default)
  Return:      none
  Others:
**********************************************************/
BM52D5121_1::BM52D5121_1(HardwareSerial*theSerial)
{
  _serial = theSerial;
  _softSerial = NULL;
  checksum = 0;
  data1 = 0;
}
/**********************************************************
  Description: Select the software serial port RX TX you need to use
  Parameters:       rxPin:RX pin on the development board
             txPin:TX pin on the development board
      none
  Return:      none
  Others:
**********************************************************/
BM52D5121_1::BM52D5121_1(uint8_t rxPin, uint8_t txPin)
{
  _serial = NULL;
  _rxPin = rxPin;
  _txPin = txPin;
  _softSerial = new SoftwareSerial(_rxPin, _txPin);
  checksum = 0;
  data1 = 0;
}
/**********************************************************
  Description: Set serial baud rate
  Parameters:       uartBaud：9600(default)
  Return:      none
  Others:
**********************************************************/
void BM52D5121_1::begin(uint32_t baud)
{
  if (_softSerial != NULL)
  {
    _softSerial->begin(baud);
    _softSerial->setTimeout(30);
  }
  else
  {
    _serial->begin(baud);
    _serial->setTimeout(30);
  }
}
/**********************************************************
  Description: Send the command to read the current water detection value
  Parameters:  buff:Store the read water sensing value(range: 00h~80h)
             warter value:0x00~0x80
  Return:      0: no data read
             1: Successfully read data
  Others:
**********************************************************/

uint8_t BM52D5121_1::readWaterValue()
{
  uint8_t receivedata[7];
  uint8_t i=readData(receivedata, COMMAND_READWATERLEVEL, 2);
  if ((receivedata[4] == 0x00)&&(i==0x00))
  {
    return receivedata[5];
  }
  else
  {
    return READ_ERROR;
  }
}

/**********************************************************
  Description: Send command to read the current water calibration value
  Parameters:  Buff: used to store the read current water detection calibration value (range: 00h~80h)
  Return:      0: no data read
             1: Successfully read data
  Others:
**********************************************************/
uint8_t BM52D5121_1::readWaterThreshold()
{
  uint8_t receivedata[7];
  uint8_t i=readData(receivedata, COMMAND_READWATERCALBRATION, 2);
  if ((receivedata[4] == 0x00)&&(i==0x00))
  {
    return receivedata[5];
  }
  else
  {
    return READ_ERROR;
  }
}
/**********************************************************
  Description: Send an instruction to read the current atomization power
  Parameters:  buff:Array to store the read power
             Atomization power
             power status:32Level
             5W~10w
  Return:      0: no data read
             1: Successfully read data
  Others:
**********************************************************/
uint8_t BM52D5121_1::getAtoPower()
{
  uint8_t receivedata[7];
  uint8_t i=readData(receivedata,COMMAND_READPOWERSTATUS, 2);
  if ((receivedata[4] == 0x00)&&(i==0x00))
  {
    return receivedata[5];
  }
  else
  {
    return READ_ERROR;
  }
}
/**********************************************************
  Description: Read the current fan operating power
  Parameters:  buff:Store the read fan power
             fan power
             FAN_POWER_FULL (0X00)
             FAN_POWER_HALF (0X01)
             FAN_POWER_OFF  (0X20)
  Return:      0: no data read
             1: Successfully read data
  Others:
**********************************************************/
uint8_t BM52D5121_1::getFanPower()
{
  uint8_t receivedata[7];
  uint8_t i=readData(receivedata, COMMAND_READFANSTATUS, 2);
  if ((receivedata[4] == 0x00)&&(i==0x00))
  {
    return receivedata[5];
  }
  else
  {
    return READ_ERROR;
  }
}
/**********************************************************
  Description: Read the current RGB working mode and the brightness of the three RGB lamps
  Parameters:  buff:RGB mode and data
             buff[0]:
             Bit1, Bit0 are 00: the light is off
             Bit1, Bit0 is 01: streamer light mode
             Bit1, Bit0 is 10: breathing light mode
             Bit1, Bit0 are 11: normal light mode
             buff[1]:R;buff[2]:G;buff[3]:B
  Return:      0: no data read
             1: Successfully read data
  Others:
**********************************************************/
uint8_t BM52D5121_1::getRGB(uint8_t buff[])
{
  uint8_t receivedata[10];
  uint8_t i=readData(receivedata, COMMAND_READRGBDATA, 5);
    if ((receivedata[4] == 0x00)&&(i==0x00))
  {
      buff[0] = receivedata[5];
      buff[1] = receivedata[6];
      buff[2] = receivedata[7];
      buff[3] = receivedata[8];
      return READ_OK;
  }
  else
  {
    return READ_ERROR;
  }
}
/**********************************************************
  Description: Read the remaining timing
  Parameters:  buff:Remaining timing time
  Return:      0: no data read
             1: Successfully read data
  Others:
**********************************************************/

uint16_t BM52D5121_1::getTimer()
{
  uint8_t receivedata[8];
  uint16_t time=0;
  uint8_t i=readData(receivedata, COMMAND_READTIMER, 8);
  if ((receivedata[4] == 0x00)&&(i==0x00))
  {
    time=((receivedata[5] << 8) + receivedata[6]);
    return time;
  }
  else
  {
    return READ_ERROR;
  }
}
/**********************************************************
  Description: Read the current FWver number
  Parameters:  buff:Store the read version number
               FWver number
  Return:      0: no data read
             1: Successfully read data
  Others:
**********************************************************/
uint16_t BM52D5121_1::getFWVer()
{
  uint16_t FWVer=0;
  uint8_t receivedata[8];
  uint8_t i=readData(receivedata, COMMAND_READVERSION , 3);
  if ((receivedata[4] == 0x00)&&(i==0x00))
  {
    FWVer=((receivedata[5] << 8) + receivedata[6]);
    return FWVer;
  }
  else
  {
    return READ_ERROR;
  }
}
/**********************************************************
  Description: Read the module status
  Parameters:  buff:Store the read modular status
  Return:      0: no data read
             1: Successfully read data
  Others:
**********************************************************/
uint8_t BM52D5121_1::getModuleStatus()
{
  uint8_t receivedata[7];
  uint8_t i=readData(receivedata, COMMAND_READMODULAR, 2);
  if ((receivedata[4] == 0x00)&&(i==0x00))
  {
    return receivedata[5];
  }
  else
  {
    return READ_ERROR;
  }
}
/**********************************************************
  Description: write water calibration data
  Parameters:  Buff:0x01/0x02
             0x01: empty cup calibration
             0x02: full cup calibration
  Return:      0: module failed to receive command
             1: Module received command successfully
  Others:
**********************************************************/
uint8_t BM52D5121_1::calibrateWaterLevel(uint8_t cmd)
{
  uint8_t receivedata[6];

  writeData(cmd, COMMAND_WRITEWATERCALBRATION);
  uint8_t i=readBytes(receivedata, 6,10);
  if ((receivedata[4] == 0x00)&&(i==0x00))
  {
    return  READ_OK;
  }
  else
  {
    return  READ_ERROR;
  }
}
/**********************************************************
  Description: write power status
  Parameters:  buff: range 0~32
             Atomization power
             power status:32 Level 5W~10w
  Return:      0: module failed to receive command
             1: Module received command successfully
  Others:
**********************************************************/
uint8_t BM52D5121_1::setAtoPower(uint8_t power)
{
  uint8_t receivedata[6];

  writeData(power, COMMAND_WRITEPOWERSTATUS);
  uint8_t i=readBytes(receivedata, 6,10);
  if ((receivedata[4] == 0x00)&&(i==0x00))
  {
    return  READ_OK;
  }
  else
  {
    return  READ_ERROR;
  }
}

/**********************************************************
  Description: write fan status
  Parameters:  buff:fan power data
             fan power
             FAN_POWER_FULL (0X00)
             FAN_POWER_HALF (0X01)
             FAN_POWER_OFF  (0X20)
  Return:      0: module failed to receive command
             1: Module received command successfully
  Others:
**********************************************************/
uint8_t BM52D5121_1::setFanPower(uint8_t power)
{
  uint8_t receivedata[6];

  writeData(power, COMMAND_WRITEFANSTATUS);
  uint8_t i=readBytes(receivedata, 6,10);
  if ((receivedata[4] == 0x00)&&(i==0x00))
  {

    return  READ_OK;
  }
  else
  {
    return  READ_ERROR;
  }
}

/**********************************************************
  Description: write Scan Frequency
  Parameters:  Buff: re frequency tracking data written (only for 00h, re frequency tracking)
  Return:      0: module failed to receive command
             1: Module received command successfully
  Others:
**********************************************************/
uint8_t BM52D5121_1::setScanFrequency()
{
  uint8_t receivedata[6];

  writeData(COMMAND_WRITESCANFREQUENCY);
  uint8_t i=readBytes(receivedata, 6,10);
  if ((receivedata[4] == 0x00)&&(i==0x00))
  {
    delay(3200);
    return  READ_OK;
  }
  else
  {
    return  READ_ERROR;
  }
}

/**********************************************************
  Description: write RGB data
  Parameters:  Buff: RGB working mode written and values of R, G and B (4 bytes in total)
             buff[0]:
             Bit1, Bit0 are 00: the light is off
             Bit1, Bit0 is 01: streamer light mode
             Bit1, Bit0 is 10: breathing light mode
             Bit1, Bit0 are 11: normal light mode
             buff[1]:R;buff[2]:G;buff[3]:B
             streamer light mode：000AH~044CH(10~1100)
             buff[1]:To adjust streamer speed high byte
             buff[2]:To adjust streamer speed low byte
             buff[3]:no mean.
             breathing light mode:The smaller the value, the darker the brightness
             buff[1]:0~128
             buff[2]:0~128
             buff[3]:0~128
  Return:      0: module failed to receive command
             1: Module received command successfully
  Others:
**********************************************************/
uint8_t BM52D5121_1::setRGB(uint8_t buff[])
{
  uint8_t receivedata[6];
  writeData(buff, COMMAND_WRITERGBDATA, 5);
  uint8_t i=readBytes(receivedata,6,10);
  if ((receivedata[4] == 0x00)&&(i==0x00))
  {

    return  READ_OK;
  }
  else
  {
    return  READ_ERROR;
  }
}

/**********************************************************
  Description: write timer data
  Parameters:  buff:time  unit:second
             range1 (0x0001)s~64800(0xFD20)s
  Return:      0: module failed to receive command
             1: Module received command successfully
  Others:
**********************************************************/
uint8_t BM52D5121_1::setTimer(uint16_t time)
{
  uint8_t receivedata[6];
  uint8_t timerdatah;
  uint8_t timerdatal;
  timerdatah=highByte(time);
  timerdatal=lowByte(time);
  uint8_t ack[2]={timerdatah,timerdatal};
  writeData(ack,COMMAND_WRITETIMER,3);
  uint8_t i=readBytes(receivedata,6,10);
  if ((receivedata[4] == 0x00)&&(i==0x00))
  {

    return  READ_OK;
  }
  else
  {
    return  READ_ERROR;
  }
}
/**********************************************************
  Description: write data to the module to sleep the module
  Parameters:  none
  Return:  none
  Others:  none
**********************************************************/
uint8_t BM52D5121_1::sleep()
{
  uint8_t receivedata[6];
  writeData(COMMAND_SLEEP);
  uint8_t i=readBytes(receivedata,6,10);
  if ((receivedata[4] == 0x00)&&(i==0x00))
  {
    return  READ_OK;
  }
  else
  {
    return  READ_ERROR;
  }
}
/**********************************************************
  Description: write data to the module wake up
  Parameters:       none
  Return:      none
  Others:
**********************************************************/
uint8_t BM52D5121_1::reset()
{
  uint8_t receivedata[6];
  writeData(COMMAND_RESET);
  uint8_t i=readBytes(receivedata,6,10);
  if ((receivedata[4] == 0x00)&&(i==0x00))
  {
    return  READ_OK;
  }
  else
  {
    return  READ_ERROR;
  }
}
/**********************************************************
Description: Write data through UART
Parameters: wbuf:The array for storing Data to be sent
            wlen:Length of data sent
Return: None
Others: None
**********************************************************/
void BM52D5121_1::writeBytes(uint8_t wbuf[], uint8_t wlen)
{
  /* Select SoftwareSerial Interface */
  if (_softSerial != NULL)
  {
    while (_softSerial->available() > 0)
    {
      _softSerial->read();
    }
    _softSerial->write(wbuf, wlen);
  }
  /* Select HardwareSerial Interface */
  else
  {
    while (_serial->available() > 0)
    {
      _serial->read();
    }
    _serial->write(wbuf, wlen);
  }
}
/**********************************************************
Description: Read data through UART
Parameters: rbuf: Used to store received data
            rlen: Length of data to be read
Return: 0: check ok
        1: check error
        2: timeout error
Others: None
**********************************************************/
uint8_t BM52D5121_1::readBytes(uint8_t rbuf[], uint8_t rlen, uint16_t timeout)
{
  uint8_t i = 0, delayCnt = 0, checkSum = 0;
  /* Select SoftwareSerial Interface */
  if (_softSerial != NULL)
  {
    for (i = 0; i < rlen; i++)
    {
      delayCnt = 0;
      while (_softSerial->available() == 0)
      {
        if (delayCnt > timeout)
        {
          return TIMEOUT_ERROR; // Timeout error
        }
        delay(1);
        delayCnt++;
      }
      rbuf[i] = _softSerial->read();
    }
  }
  /* Select HardwareSerial Interface */
  else
  {
    for (i = 0; i < rlen; i++)
    {
      delayCnt = 0;
      while (_serial->available() == 0)
      {
        if (delayCnt > timeout)
        {
          return TIMEOUT_ERROR; // Timeout error
        }
        delay(1);
        delayCnt++;
      }
      rbuf[i] = _serial->read();
    }
  }
  /* check Sum */
  for (i = 0; i < (rlen - 1); i++)
  {
    checkSum += rbuf[i];
  }
  checkSum = ~checkSum;
  if (checkSum == rbuf[rlen - 1])
  {
    return CHECK_OK; // Check correct
  }
  else
  {
    return CHECK_ERROR; // Check error
  }
}
/**********************************************************
Description: read data 
Parameters: buff[]:Store the read data
            command:instructions
            datalength:Number of data bytes to be read buff[]
Return: None
Others: None
**********************************************************/
uint8_t BM52D5121_1::readData(uint8_t buff[], uint8_t command, uint8_t datalength)
{
  checksum = HEADER + ADDRESSHIGH + ADDRESSLOW + 0x01 + command;
  checksum = ~checksum;
  uint8_t ack[6] = {HEADER, ADDRESSHIGH, ADDRESSLOW, 0x01, command, checksum};
  writeBytes(ack, 6);
  uint8_t i=readBytes(buff, (datalength + 5), 10);
  if(i==CHECK_OK)
  {
    return CHECK_OK;
  }
  if(i==TIMEOUT_ERROR)
  {
    return TIMEOUT_ERROR;
  }
  else
  {
    return CHECK_ERROR;
  }
}
/**********************************************************
  Description: UART write Data
  Parameters:  buff:Variables for storing Data to be write
               command:Command to write data
               datalength:Bytes of buff +1
  Return:      none
  Others:
**********************************************************/
void BM52D5121_1::writeData(uint8_t buff[], uint8_t command, uint8_t datalength)
{
  uint8_t len;
  len = 5 + datalength;
  uint8_t ack[len] = {HEADER, ADDRESSHIGH, ADDRESSLOW, datalength, command};
  checksum = (uint8_t)(HEADER + ADDRESSHIGH + ADDRESSLOW + datalength + command);
  for (uint8_t i = 0; i < (datalength - 1); i++)
  {
    ack[5 + i] = buff[i];
    checksum = checksum + buff[i];
  }
  checksum = ~checksum;
  ack[len - 1] = checksum;
  writeBytes(ack, len);
}
void BM52D5121_1::writeData(uint8_t data, uint8_t command)
{
  uint8_t ack[7] = {HEADER, ADDRESSHIGH, ADDRESSLOW, 0x02, command, data, checksum};
  checksum = (uint8_t)(HEADER + ADDRESSHIGH + ADDRESSLOW + 0x02 + command + data);
  checksum = ~checksum;
  ack[6]=checksum;
  writeBytes(ack, 7);
}

void BM52D5121_1::writeData( uint8_t command)
{
  uint8_t ack[6] = {HEADER, ADDRESSHIGH, ADDRESSLOW, 0x01, command, checksum};
  checksum = (uint8_t)(HEADER + ADDRESSHIGH + ADDRESSLOW + 0x01 + command);
  checksum = ~checksum;
  ack[5]=checksum;
  writeBytes(ack, 6);
}
