/*

Parking Sensor
github.com/ChristianJaya

*/
 
#define BLYNK_TEMPLATE_ID "XXXXXXXXX"
#define BLYNK_DEVICE_NAME "XXXXXXXXX"
#define BLYNK_AUTH_TOKEN "XXXXXXXXX"
#define BLYNK_FIRMWARE_VERSION "0.1.0"
#define BLYNK_PRINT Serial
#define echoPin 15
#define trigPin 2
#define buzzerPin 5
#define ledPin 4
#include <Wire.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "XXXXXXXXX";
char pass[] = "XXXXXXXXX";
long duration;
float cm;
BlynkTimer timer;
WidgetLED led(V1);
WidgetLED buzzer(V2);

void myTimerEvent()
{
}

void setup()
{
  Serial.begin(115200);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1L, myTimerEvent);
}

void loop()
{
  lcd.init(); 
  lcd.backlight();
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm = duration / 58.82;
  
  if(cm < 20) 
  {
    led.on();
    buzzer.on(); 
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledPin, HIGH); 
    lcd.setCursor(0,0); 
    lcd.print(cm); 
    lcd.print(" CM");
    lcd.setCursor(0,1);
    lcd.print("WATCHOUT!");
    Blynk.virtualWrite(V3, cm);
    Blynk.virtualWrite(V4, "WATCHOUT!");
    Serial.print("LED AND BUZZER ON - ");
  }
  
  else
  {
    led.off();
    buzzer.off(); 
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW); 
    lcd.setCursor(0,0); 
    lcd.print(cm); 
    lcd.print(" CM"); 
    lcd.setCursor(0,1);
    lcd.print("SAFE!");
    Blynk.virtualWrite(V3, cm);
    Blynk.virtualWrite(V4, "SAFE!");
    Serial.print("LED AND BUZZER OFF - ");
  } 
 
  Serial.print("Distance : ");
  Serial.print(cm);
  Serial.print(" CM");
  Serial.print("\n");
  delay(10);
  Blynk.run();
  timer.run(); 
}
