#include <Time.h>
#include <TimeLib.h>
//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 30;        

//the time when the sensor outputs a low impulse
long unsigned int lowIn;         

//the amount of milliseconds the sensor has to be low 
//before we assume all motion has stopped
long unsigned int pause = 5000;  

boolean lockLow = true;
boolean takeLowTime;  

int pirPin = 3;    //the digital pin connected to the PIR sensor's output
int ledPin = 13;
int timeof = 0;


int LDR = A0;            // LDR input at A0 pin.
int LED = 3;             // LED is connected to PWM Pin 3.
int LDRReading = 0;      // to store input value of LDR
int lEDBrightness = 0;   // to store the value of LED Brightness
int threshold_val = 300; // Check your threshold and modify it.


void setup(){
  Serial.begin(9600);     // initializing serail communication.
  pinMode(LED, OUTPUT);   // Defining LED pin as output.
  //motion
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);

  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);
  }


void loop(){
  LDRReading = analogRead(LDR);    // Reading LDR Input.
  Serial.println(LDRReading);      // Printing LDR input value.
  
  if (LDRReading >threshold_val){ 
    Serial.println("The light is off");// Condition to make LED ON.
  lEDBrightness = map(LDRReading, 0, 1023, 0, 255); // Converting LDR to LED Brightness.
  analogWrite(LED, lEDBrightness); // Writing Brightness to LED.
  }
  else{
    Serial.println("The light is on");
  analogWrite(LED, 0);
  Serial.println("---");// If LDR is below threshold make LED OFF.
  }
   // delay to make output readable on serial monitor.
   //motion
delay(5000);
     //the led visualizes the sensors output pin state
       if(lockLow){  
         //makes sure we wait for a transition to LOW before any further output is made:
         lockLow = true;            
         Serial.println("---");
         Serial.print("motion detected at ");
         
         Serial.print(millis()/1000);
        Serial.println("---");
         }
         delay(1000);
         }         
      
