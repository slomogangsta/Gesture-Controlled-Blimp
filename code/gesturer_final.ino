#include <Wire.h>
#include <MPU6050.h>
#include<VirtualWire.h>
char *controller;
MPU6050 mpu;

void setup() 
{
  Serial.begin(115200);
Serial.println("Initialize MPU6050");
while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  pinMode(6,OUTPUT);//pitch measurement 
  pinMode(7,OUTPUT);//-ve roll measurement 
  pinMode(8,OUTPUT);//+ve roll measurement 
  pinMode(13,OUTPUT);
vw_set_ptt_inverted(true); //
vw_set_tx_pin(9);
vw_setup(4000);// speed 
 }

void loop()
{
  Vector normAccel = mpu.readNormalizeAccel();
  int roll = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis))*180.0)/M_PI;
  int pitch = (atan2(normAccel.YAxis, normAccel.ZAxis)*180.0)/M_PI; 
  Serial.print(" Pitch = ");
  Serial.print(pitch);
  Serial.print(" Roll = ");
  Serial.print(roll);
  if(pitch<=-85)
  {
  controller="1" ;
vw_send((uint8_t *)controller, strlen(controller));
vw_wait_tx(); 
 Serial.print(" 1 ");
}
if(roll>=65)
  {
   controller="2" ;
vw_send((uint8_t *)controller, strlen(controller));
vw_wait_tx(); 
Serial.print(" 2");
}
 if(roll<=-65)
  {
   controller="3" ;
vw_send((uint8_t *)controller, strlen(controller));
vw_wait_tx();
Serial.print(" 3"); 
  }
if(roll>(-30)&&roll<30)
  {
   controller="0" ;
vw_send((uint8_t *)controller, strlen(controller));
vw_wait_tx();
Serial.print("  0"); 
}
if(pitch<=-85)
  {
  controller="1" ;
vw_send((uint8_t *)controller, strlen(controller));
vw_wait_tx(); 
 Serial.print("  1 ");
}
 if(pitch>-85)
  {
  controller="4" ;
vw_send((uint8_t *)controller, strlen(controller));
vw_wait_tx(); 
 Serial.print("  4 ");
}
Serial.println();
delay(100);
  }



