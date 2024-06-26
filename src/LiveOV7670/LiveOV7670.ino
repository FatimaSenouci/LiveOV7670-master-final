#define LED_PIN 13 // Define the LED pin
#define BUZZER_PIN 8 // Define the buzzer pin
#define vibOutPin 9
const int BUTTON_PIN = 1;
#include "setup.h"
#include <Firmata.h>


#define OV7670_320x240 2 // OV7670 resolution configuration
char data = ' '; // Variable to store incoming serial data
bool buttonPressed = false;
bool shouldVibrate = false;



void setup() {
   // This is not necessary and has no effect for ATMEGA based Arduinos.
  // WAVGAT Nano has slower clock rate by default. We want to reset it to maximum speed
  Firmata.begin();

  
  CLKPR = 0x80; // enter clock rate change mode
  CLKPR = 0; // set prescaler to 0. WAVGAT MCU has it 3 by default.

  initializeScreenAndCamera(); // Initialize the camera module - OV7670
  
  // Write a comment when the connection is established


  Serial.begin(500000);


 //Serial.write("*RDY*");  // Send start command 
  pinMode(vibOutPin, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT); // Set the LED pin as output
  pinMode(BUZZER_PIN, OUTPUT); // Set the buzzer pin as output
  digitalWrite(LED_PIN, LOW); // Initially turn off the LED
  digitalWrite(BUZZER_PIN, LOW); // Initially turn off the buzzer
  //Serial.println("Hi!, I am Arduino"); // Send a message via serial communication
  
 Serial.write("*RDY*");  // Send start command

}

void loop() {
int buttonState = digitalRead(BUTTON_PIN); // read new state

 if (buttonState == LOW) {
    //Serial.println("The button is being pressed");
    digitalWrite(BUZZER_PIN, LOW); // turn off
    buttonPressed = true; 
    Serial.println("restart");

  }
  

  Firmata.processInput();

  processFrame(); // Process camera frame
if (Serial.available() > 0){
    data = Serial.read(); // Read the incoming serial data
    /********/
      if (data== '8') {
      shouldVibrate = true;
    } else if (data== '9') {
      shouldVibrate = false;
    }
  }
if (shouldVibrate) {
    digitalWrite(vibOutPin, HIGH);
    delay(2000);
    digitalWrite(vibOutPin, LOW);
    delay(600);
    digitalWrite(vibOutPin, HIGH);
    delay(2000);
    digitalWrite(vibOutPin, LOW);
    delay(2000);
  } else {
    // If shouldVibrate is false, stop the vibration
    digitalWrite(vibOutPin, LOW);
    delay(2000);  // Optional: introduce a small delay before checking again
  }
    /*****************/
    // Control LED and buzzer based on received data
   // Control LED and buzzer based on received data
    if (data == 'f') {
        digitalWrite(BUZZER_PIN, HIGH); // Turn on buzzer
         //delay(500); // Keep them on for 1 second
    if (buttonState == LOW) {
    //Serial.println("The button is being pressed");
   digitalWrite(BUZZER_PIN, LOW); // turn off
   buttonPressed = true;
  }
    }
      else if (data == 's') {
        digitalWrite(BUZZER_PIN, LOW); // Turn off buzzer
        
        
    }  if (data == '5') {
        digitalWrite(LED_PIN, HIGH); // Turn on LED
         delay(500); // Keep them on for 1 second
    }  if (data == '6') {
        digitalWrite(LED_PIN, LOW); // Turn off LED
    }
}  


       
