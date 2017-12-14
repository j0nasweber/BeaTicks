/*********************************************************************
  
  BioFeedback with Adafruit Bluefruit
  
*********************************************************************/
#include <TimerOne.h>
#include <Arduino.h>

#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"

#define FACTORYRESET_ENABLE         0
#define MINIMUM_FIRMWARE_VERSION    "0.6.6"
#define MODE_LED_BEHAVIOUR          "MODE"
#define N 64 //1,2,4,8,16,32,64

#define Tau         0.05
#define Ts          0.025
#define THRESHOLD   38


int buff[N];

int xn = 0;
int yn = 0;
int yn_1 = 0;
int b = 4;
int bn = 0;
int bn_1 = 0;
int pointer, pointer2 = 0;

bool EN = true;
int led = 13;

void setup(void)
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);

  bleConfig();

  Timer1.initialize(Ts*100);
  Timer1.attachInterrupt(timerInterrupt);
}

/**************************************************************************/
/*
  read analog pulse values from analog pin A0 and print it out over serial ble connection
*/
/**************************************************************************/
void loop(void)
{
  
}

void timerInterrupt(){
  xn = analogRead(0);
  for(int i = 0; i < N; i++){
    yn+=buff[i];
  }
  yn/=N;  
  /*
  Serial.print(yn);
  Serial.print(";");
  //*/
  if(yn > THRESHOLD && yn_1 > yn && EN == false){
    blePrint();
    Serial.println("1");
    //Serial.print("1025;");

    EN = true;
    digitalWrite(led, HIGH);
    //delay(300);
    digitalWrite(led, LOW);
  }else if(yn <= THRESHOLD && EN){
    EN = false;
  }
  //*/
  
  yn_1 = yn;
  bn_1 = bn;

  buff[pointer] = xn;
  pointer++;
  
  if(pointer > (N-1) ){
    pointer = 0;
  }
}

