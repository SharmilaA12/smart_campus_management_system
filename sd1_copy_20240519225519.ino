#define BLYNK_TEMPLATE_ID "TMPL3Iq0QFK99"
#define BLYNK_TEMPLATE_NAME "sd1"
#define BLYNK_AUTH_TOKEN "5gqWXQLCAKpjxxSXbmRLuAOyNefBY94M"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h> // Include the ESP32_Servo library

char auth[] = "5gqWXQLCAKpjxxSXbmRLuAOyNefBY94M";
char ssid[] = "Bharath M";
char pass[] = "Bharath@13";

BlynkTimer timer;

#define echoPin 32
#define trigPin 33
Servo servo;
long duration;
int distance; 
int binLevel=0;

void SMESensor()
{
  int ir=digitalRead(34);
  if(ir==HIGH)
  {    
    servo.write(90);
    for(int i=0; i<50; i++)
    {
      Blynk.virtualWrite(V2, 90);
      ultrasonic(); 
      delay(100);
    }
    servo.write(0);
    Blynk.virtualWrite(V2, 0);
  }
  if(ir==LOW)
  {
    
    ultrasonic();
    delay(200);
  }
}
void ultrasonic()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2; //formula to calculate the distance for ultrasonic sensor
    binLevel=map(distance, 21, 0, 0,100); // ADJUST BIN HEIGHT HERE
    Blynk.virtualWrite(V0, distance);
    Blynk.virtualWrite(V1, binLevel);
}
void setup()
{
  Serial.begin(9600);
  servo.attach(13);
  pinMode(34, INPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
   Blynk.begin(auth, ssid, pass);
  delay(2000);
  timer.setInterval(1000L, SMESensor);
}

void loop() 
{
  Blynk.run();
  timer.run();
}
