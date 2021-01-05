#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
const uint64_t pipeOut = 0xE8E8F0F0E1LL; //IMPORTANT: The same as in the receiver

RF24 radio(7, 8); // select  CSN  pin
struct MyData {
  byte throttle;
  byte yaw;
  byte led;
 
};
int value=0;
MyData data;

void resetData() 
{
  //This are the start values of each channal
  // Throttle is 0 in order to stop the motors
  //127 is the middle value of the 10ADC.
    
  data.throttle = 127;
  data.yaw = 127;
  data.led=0;
}



void setup() {
   Serial.begin(9600);
   analogWrite(A0,1023);
   radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipeOut);
  resetData();
  // put your setup code here, to run once:

}

void loop() {
  
  while (Serial.available())
        {
           value = Serial.read();
        }
     
     if (value == '1')
     {
      data.throttle = 127;
  data.yaw = 127;
  data.led=127;
       // digitalWrite (led, HIGH);
        Serial.println("stop");
     }
     
     else if (value == '5')
     {
      data.throttle = 255;
  data.yaw = 127;
  data.led=127;
       // digitalWrite (led, LOW);
        Serial.println("forward");
     }
         
     else if (value == '4')
     {
      data.throttle = 0;
  data.yaw = 127;
  data.led=127;
       // digitalWrite (led, LOW);
        Serial.println("backward");
     } 
     else if (value == '3')
     {
      data.throttle = 255;
  data.yaw = 255;
  data.led=127;
        //digitalWrite (led, LOW);
        Serial.println("right");
     }
         
     else if (value == '2')
     {
      data.throttle = 255;
  data.yaw = 0;
  data.led=127;
        //digitalWrite (led, LOW);
        Serial.println("left");
     }
  // put your main code here, to run repeatedly:
  Serial.print(data.throttle);Serial.print("   " );
Serial.print(data.yaw);Serial.print("   " );


Serial.print(data.led );Serial.print("   " );

Serial.println(" " );
  radio.write(&data, sizeof(MyData));

}
