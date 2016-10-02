// This code is used to get values of an IRremote controller buttons
#include "IRremote.h"
 
int receiver = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11
 
/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'
 
void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver
 
}/*--(end setup )---*/
 
 
void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (irrecv.decode(&results)) // have we received an IR signal?
 
  {
    Serial.println(results.value, HEX);
    irrecv.resume(); // receive the next value
  }  
}/* --(end main loop )-- */
 
/*-----( Function )-----*/

