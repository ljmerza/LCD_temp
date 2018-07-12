/***********************************************************************************
Created by: Leonardo Merza
Version: 1.02
***********************************************************************************/

/***********************************************************************************
Imports
***********************************************************************************/
#include <LiquidCrystal.h>
#include <DHT.h>

/***********************************************************************************
Variables
***********************************************************************************/
// RS, E, DB4, DB5, DB6, DB7 pins
int RSpin = 12;
int ePin = 11;
int db4Pin = 5;
int db5Pin = 4;
int db6Pin = 3;
int db7Pin = 2;

int lcdWidth = 16;
int lcdHeight = 2;

//multiplexer pins
int s0Pin = 6;
int s1Pin = 7;
int s2Pin = 8;
int s3Pin = 9;

int dhtPin = 10;

LiquidCrystal lcd(RSpin, ePin, db4Pin, db5Pin, db6Pin, db7Pin);
DHT dht;

// array of all multiplexer values possible
int muxPins[64] = {0,0,0,0, 1,0,0,0, 0,1,0,0, 1,1,0,0, 0,0,1,0, 1,0,1,0, 
    0,1,1,0, 1,1,1,0, 0,0,0,1, 1,0,0,1, 0,1,0,1, 1,1,0,1, 0,0,1,1, 1,0,1,1, 0,1,1,1, 1,1,1,1};

/***********************************************************************************
***********************************************************************************/
void setup(){
  Serial.begin(9600);
  
  dht.setup(dhtPin);
  lcd.begin(lcdWidth, lcdHeight);
  
  pinMode(s0Pin,OUTPUT);
  pinMode(s1Pin,OUTPUT);
  pinMode(s2Pin,OUTPUT);
  pinMode(s3Pin,OUTPUT);
} // void setup(){

/***********************************************************************************
***********************************************************************************/
void loop(){ 
  // get DHT values 
  float humidity = dht.getHumidity();
  float temperature = dht.toFahrenheit(dht.getTemperature());
  
  // set lcd and write temp values
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.setCursor(5, 0);
  lcd.print(temperature); 
  if(temperature > 100){
    lcd.setCursor(10, 0);
  }
  else{
    lcd.setCursor(10, 0);
  }
  lcd.print("F");
  
  // set lcd and write humidty values
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.setCursor(9, 1);
  lcd.print(humidity);
  if(humidity > 10){
    lcd.setCursor(14, 1);
  }
  else{
    lcd.setCursor(13, 1);
  }
  lcd.print("%");
    
  // start LED temps at 60 and light up LEDs based on current temp value
  int tempStart = 60;
  
  for(int i=0;i<64;i+=4){
    if(temperature>=tempStart){
      digitalWrite(6, muxPins[i]);
      digitalWrite(7, muxPins[i+1]);
      digitalWrite(8, muxPins[i+2]);
      digitalWrite(9, muxPins[i+3]);
    } // if(temperature<temp){
    tempStart+=2;
    // delay so multiplexer can light up all LEDs
    delayMicroseconds(400);
  } // for(int i=0;i<sizeof(muxPins;i+=4)){
} // void loop(){  
