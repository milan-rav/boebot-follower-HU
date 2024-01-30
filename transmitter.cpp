#include <SPI.h>
#include "printf.h"
#include "RF24.h"

const int pinCE = 7; //This pin is used to set the nRF24 to standby (0) or active mode (1)

const int pinCSN = 8; //This pin is used to tell the nRF24 whether the SPI communication is a command or message to send out

RF24 radio(pinCE, pinCSN); // Create your nRF24 object or wireless SPI connectiona

#define WHICH_NODE 1     // must be a number from 1 - 6 identifying the PTX node

uint8_t address[][6] = { "1Node", "2Node" };

#define radioNumber 1


    uint8_t out1A=5;
    uint8_t out1B=2;
    uint8_t out2A=3;
    uint8_t out2B=4;
 
uint8_t radioSend[]={out1A,out1B,out2A,out2B};

void setup() {

  Serial.begin(115200);   //start serial to communicate process
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {}  // hold in infinite loop
  }
    Serial.println(F("radio hardware is responding!!"));
  radio.setPALevel(RF24_PA_LOW);  // "short range setting" - increase if you want more range AND have a good power supply
  //radio.setChannel(111);          // the higher channels tend to be more "open"
  radio.setPayloadSize(sizeof(radioSend));
  radio.openWritingPipe(address[radioNumber]);  //open reading or receive pipe
    radio.openReadingPipe(1, address[!radioNumber]);
  radio.stopListening(); 


}

void loop() {

//   bool rslt = radio.write( &out, sizeof(out) );
//   if (rslt)
//   {
//     Serial.println("  Acknowledge received");
//   }
//   else
//   {
//     Serial.println("  Tx failed");
//   }
// delay(100);



    unsigned long start_timer = micros();                // start the timer
    bool report = radio.write(&radioSend , sizeof(radioSend));  // transmit & save the report
    unsigned long end_timer = micros();                  // end the timer

    if (report) {
      Serial.print(F("Transmission successful! "));  // payload was delivered
      Serial.print(F("Time to transmit = "));
      Serial.print(end_timer - start_timer);  // print the timer result
      Serial.println(F(" us. Sent: "));
      radioSend[0]=+5;
 // print payload sent
         // increment float payload
    } else {
      Serial.println(F("Transmission failed or timed out"));  // payload was not delivered
    }

    // to make this example readable in the serial monitor
    delay(1000);  // slow transmissions down by 1 second

}
