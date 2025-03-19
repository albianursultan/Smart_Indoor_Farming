#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "DHT.h"

LiquidCrystal_I2C lcd(0x27, 20, 4);

#define mois 32
#define uvsensor 33
#define in1 27
#define in2 26
#define DHTPIN 2 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(mois, INPUT);
  pinMode(uvsensor, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  lcd.begin();
  lcd.backlight();
  lcd.display();
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SMART");
  lcd.setCursor(0, 1);
  lcd.print("INDOOR FARM");
  lcd.setCursor(10, 4);
  lcd.print("by:INACOS");
  delay(2000);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  dht.begin();

}

void loop() {

 float h = dht.readHumidity();
 float t = dht.readTemperature();
 int valMOIS = analogRead(32);
 int valUV = analogRead(33);

 float voltage = valUV * (5.0 / 1023.0);
 
  Serial.print("moisture:");
  Serial.println(valMOIS);
  Serial.println("voltage :");
  Serial.print(voltage);
  Serial.println("UV Index :");
  Serial.print(valUV /.1);
  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");

  lcd.setCursor(3, 0);
  lcd.print("Temp:");
  lcd.print(t);
  lcd.print(" °C\tHum: ");
  lcd.print(h);
  lcd.print(" %");


  if (valMOIS > 90) {
    lcd.clear();
    digitalWrite(in1, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Watering ON ");
    delay(2000);
    lcd.clear();
  } else {
    lcd.clear();
    digitalWrite(in1, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Watering OFF");
    delay(2000);
    lcd.clear();
  }
    
}
 
