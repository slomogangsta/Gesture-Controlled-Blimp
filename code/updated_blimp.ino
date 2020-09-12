#include<VirtualWire.h>
void setup()
{
vw_set_ptt_inverted(true); 
vw_set_rx_pin(12);
vw_setup(4000);
pinMode(3, OUTPUT);//cwm
pinMode(5, OUTPUT);//ccwm
Serial.begin(9600);
vw_rx_start();
}
void loop()
{
  
uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;
if (vw_get_message(buf, &buflen)) 
{
if(buf[0]=='1')//stop
{
analogWrite(3,0);

analogWrite(5,0);
Serial.println(" calm down beast");
}
if(buf[0]=='2')//right 
{
analogWrite(5,255);
analogWrite(3,100);
Serial.println(" yaay turn right ");
}

if(buf[0]=='3')//left
{
digitalWrite(3,255);
digitalWrite(5,100);
Serial.println(" yaay turn left");
} 
if(buf[0]=='4')//stable
{
  digitalWrite(3,255);
  digitalWrite(5,255);
Serial.println(" Run Run Run");
} 
}
}

