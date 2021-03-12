#include "SoftwareSerial.h"

// This serial port is used to communicate with the Ping device
// If you are using and Arduino UNO or Nano, this must be software serial, and you must use
// 9600 baud communication
// Here, we use pin 9 as arduino rx (Ping tx, white), 10 as arduino tx (Ping rx, green)
static const uint8_t arduinoRxPin = 4;
static const uint8_t arduinoTxPin = 3;
SoftwareSerial pingSerial = SoftwareSerial(arduinoRxPin, arduinoTxPin); 

void setup()
{
 
    Serial.begin(9600);
   // pinMode(ledPin, OUTPUT);

    //  (?? Setup Sleeper  ??) 
    // Setup Radio Receiver
    // Setup Radio Sender
    // Setup SD
    // Setup devices
    //  Ping1d
    //  Conductivity
    //  Temperature
    //  PH Sensor

    Serial.println("Main Loop");
//    while (!ping.initialize()) {
//        Serial.println("\nPing device failed to initialize!");
//        Serial.println("Are the Ping rx/tx wired correctly?");
//        Serial.print("Ping rx is the green wire, and should be connected to Arduino pin ");
//        Serial.print(arduinoTxPin);
//        Serial.println(" (Arduino tx)");
//        Serial.print("Ping tx is the white wire, and should be connected to Arduino pin ");
//        Serial.print(arduinoRxPin);
//        Serial.println(" (Arduino rx)");
//        delay(10000);
//    }
}
int count = 0;
void loop() {
  if (count % 10 == 0)  { // Take a reading every hour
    takeReadingAndWriteToSDCard();
    count = 0;
  }

  if (receivedSignal()) {
     sendReadingsAndClearSDCard();
  }
  count ++;
  delay(1000); // Wait 1 seconds - in real world, wait for longer and reduce count
}


void takeReadingAndWriteToSDCard() {
  Serial.println("---> takeReadingAndWriteToSDCard () ");
}

boolean receivedSignal() {
  Serial.println("receivedSignal () ");  
  return true;
}

void sendReadingsAndClearSDCard() {
   Serial.println("sendReadingsAndClearSDCard () ");  
}
