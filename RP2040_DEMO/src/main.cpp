#include <Arduino.h>
/* Demo application for Elektor Webinar Embedded Development 14/4/2022 */

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#include <FS.h>
#include <LittleFS.h>

/*
  We have an 128*128 pixel display 
  a Buzzer 
  three LEDs
  and three buttons on the board
  The following pinmapping is for the 
  makerfab / elektor Raspberry Pi Pico Expermimenting Kit

*/

#define TFT_SPI SPI1
#define TFT_CS 13
#define TFT_RST 15
#define TFT_DC 14
#define SPI_TX 11 //TX
#define SPI_RX 12 //RX
#define SPI_SCK 10 //CLK

#define BUZZER 4
#define LED_BLUE 20
#define LED_GREEN 19
#define LED_YELLOW 18

#define SW1 2
#define SW2 3
#define SW3 22


Adafruit_ST7735 tft = Adafruit_ST7735(&TFT_SPI,TFT_CS, TFT_DC, TFT_RST);

void tft_setup(){

  TFT_SPI.setRX(SPI_RX);
  TFT_SPI.setTX(SPI_TX);
  TFT_SPI.setSCK(SPI_SCK);
  tft.initR(INITR_144GREENTAB);
  
}

void button_setup(){
  pinMode(SW1,INPUT);
  pinMode(SW2,INPUT);
  pinMode(SW3,INPUT);
  
}

void led_setup(){
  pinMode(LED_BLUE,OUTPUT);
  digitalWrite(LED_BLUE,HIGH);
  pinMode(LED_GREEN,OUTPUT);
  digitalWrite(LED_GREEN,HIGH);
  pinMode(LED_YELLOW,OUTPUT);
  digitalWrite(LED_YELLOW,HIGH);
}

void setup() {
  Serial.begin(115200);
  Serial.printf("Hello ST7735 TFT Test");
  tft_setup();
  led_setup();
  /* We will initialize our 500kb LittFS partition */
  if(false==LittleFS.begin()){
    Serial.println("Error mounting LittleFS");
  } else {
    Serial.println("LittleFS mounted");
  }
  Serial.printf("Display Initialized");
  tft.fillScreen(ST7735_BLACK);

}

void loop() {
  static uint8_t pushcnt_sw3=0;
  static uint8_t pushcnt_sw2=0;
  static uint8_t pushcnt_sw1=0;
  
  if(true==digitalRead(SW3)){
    pushcnt_sw3=0;
  } else {
    if(pushcnt_sw3<255){
      pushcnt_sw3++;
    }
  }

  if(true==digitalRead(SW2)){
    pushcnt_sw2=0;
  } else {
    if(pushcnt_sw2<255){
      pushcnt_sw2++;
    }
  }

  if(true==digitalRead(SW1)){
    pushcnt_sw1=0;
  } else {
    if(pushcnt_sw1<255){
      pushcnt_sw1++;
    }
  }
  
  if(pushcnt_sw3==254){
    tft.fillScreen(ST7735_BLUE);
  }

  if(pushcnt_sw2==254){
    tft.fillScreen(ST7735_GREEN);
  }
  
  if(pushcnt_sw1==254){
    tft.fillScreen(ST7735_YELLOW);
  }
  
  
  digitalWrite(LED_BLUE,digitalRead(SW3));
  digitalWrite(LED_GREEN,digitalRead(SW2));
  digitalWrite(LED_YELLOW,digitalRead(SW1));

}

  


