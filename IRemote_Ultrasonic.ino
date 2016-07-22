// This code is created for drving an arduino powered robot with IR remote and ultrasonic sensors
#include "IRremote.h"
 
int receiver = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'
 
//Back Wheel
const int motor1Pin = 5;    
const int motor2Pin = 10;    
const int enablePin = 9;   
const int enablePin2 = 11;
const int motor1Pin2 = 13;
const int motor2Pin2 = 12;



// Front Wheel
const int MOTOR1PIN = 13;
const int MOTOR2PIN = 12;
const int ENABLEPIN = 9;
const int ENABLEPIN2 = 11;
const int MOTOR1PIN2 = 5;
const int MOTOR2PIN2 = 10;

//Front Sensor
const int trigPin = 2;
const int echoPin = 6;

// LED
const int ledPin = 3; //Green
const int ledPin2 = 4; //Red
 
/*-----( Declare objects )-----*/

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  
   pinMode(motor1Pin, OUTPUT);
    pinMode(motor2Pin, OUTPUT);
    pinMode(enablePin, OUTPUT);

    pinMode(motor1Pin2, OUTPUT);
    pinMode(motor2Pin2, OUTPUT);
    pinMode(enablePin2, OUTPUT);

    pinMode(MOTOR1PIN, OUTPUT);
    pinMode(MOTOR2PIN, OUTPUT);
    pinMode(ENABLEPIN, OUTPUT);

    pinMode(MOTOR1PIN2, OUTPUT);
    pinMode(MOTOR2PIN2, OUTPUT);
    pinMode(ENABLEPIN2, OUTPUT);
    
   pinMode(ledPin, OUTPUT);
   pinMode(ledPin2, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver
 
}/*--(end setup )---*/
 
 
void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  // set enablePin high so that motor can turn on:
  long duration, distance;
  long duration2, distance2; // For calc dist. for second sensor
  long duration3, distance3;
  
  // Front Sensor Code
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  
  if (irrecv.decode(&results)) // have we received an IR signal?
 
  {
    Serial.println(results.value, HEX);
    irrecv.resume(); // receive the next value
  }  
  
  // Sensor Check
  if (distance < 10)
   {
    // Turn red led light on
   digitalWrite(ledPin, LOW); 
   digitalWrite(ledPin2, HIGH);
    // Rotating 
    Serial.println("Rotating Motors");
    digitalWrite(MOTOR1PIN, LOW);   // set leg 1 of the H-bridge low
    digitalWrite(MOTOR2PIN, LOW);  // set leg 2 of the H-bridge high
    digitalWrite(MOTOR1PIN2, LOW);   // set leg 1 of the H-bridge side 2 low
    digitalWrite(MOTOR2PIN2, LOW);  // set leg 2 of the H-bridge side 2 high
   }
   
   else
   {
    if (irrecv.decode(&results)) // have we received an IR signal?
    {
    Serial.println(results.value, HEX);
    irrecv.resume(); // receive the next value
    }  
   }
   
   //bot moves right
     if(results.value==0xFFA25D)
    {
      digitalWrite(ledPin2, LOW); // Turn GREEN led light on
      digitalWrite(ledPin, HIGH); 
      
      digitalWrite(MOTOR1PIN, LOW);   // set leg 1 of the H-bridge low
      digitalWrite(MOTOR2PIN, HIGH);  // set leg 2 of the H-bridge high
      digitalWrite(MOTOR1PIN2, LOW);   // set leg 1 of the H-bridge side 2 low
      digitalWrite(MOTOR2PIN2, HIGH);  // set leg 2 of the H-bridge side 2 high
    }
    
    //bot moves back
    if(results.value==0xFF629D)
    {
      digitalWrite(MOTOR1PIN, HIGH);   // set leg 1 of the H-bridge low
      digitalWrite(MOTOR2PIN, LOW);  // set leg 2 of the H-bridge high
      digitalWrite(MOTOR1PIN2, HIGH);   // set leg 1 of the H-bridge side 2 low
      digitalWrite(MOTOR2PIN2, LOW);  // set leg 2 of the H-bridge side 2 high
    }
    //bot stops
    if(results.value==0xFFC23D)
    {
      digitalWrite(MOTOR1PIN, LOW);   // set leg 1 of the H-bridge low
      digitalWrite(MOTOR2PIN, LOW);  // set leg 2 of the H-bridge high
      digitalWrite(MOTOR1PIN2, LOW);   // set leg 1 of the H-bridge side 2 low
      digitalWrite(MOTOR2PIN2, LOW);  // set leg 2 of the H-bridge side 2 high
    }
}/* --(end main loop )-- */
 
/*-----( Function )-----*/

// BUTTON ADDRESS
// CH- : 0xFFA25D
// CH: 0xFF629D
// PREV: 0xFF22DD
// NEXT : 0xFF02FD
// PLAY/PAUSE: 0xFFC23D

