
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // create an RF24 object, CE, CSN const byte address[6] = "00001"; // address
void setup() {
   radio.begin();
   radio.openWritingPipe(address);  // set the address
   radio.stopListening();  // set module as transmitter
}
void loop() {
   const char text[] = "Hello World";  // message
   radio.write(&text, sizeof(text));  // send message
   delay(1000);
}






#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 8); // CE, CSN
const byte address[6] = "00001"; // address void setup() {
while(!Serial); Serial.begin(9600);
   radio.begin();
   radio.openReadingPipe(0, address); // set the address
   radio.startListening();  // set module as receiver
}
void loop() {
   // Read the data if available in buffer
if(radio.available()) {
char text[32] = {0}; radio.read(&text, sizeof(text)); Serial.println(text);
} }
