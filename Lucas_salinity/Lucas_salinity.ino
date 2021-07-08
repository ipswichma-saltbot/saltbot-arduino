#include <RTClib.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>                        
#define rx 5                         
#define tx 6
#define ONE_WIRE_BUS 7   

SoftwareSerial myserial(rx, tx);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
RTC_DS1307 rtc;

String inputstring = "";
String sensorstring = "";
boolean input_string_complete = false;
boolean sensor_string_complete = false;

//Set the time to take a single measurement
int yr = 2021;
int mon = 04;
int dy = 18;
int hr = 9;
int mi = 31;

void setup()  {
  Serial.begin(9600);
  myserial.begin(9600);
  sensors.begin();
  Serial.println("Starting ... ");
  Serial.println(rtc.now().year());
  Serial.println("Got Current Date ... ");
  
  inputstring.reserve(10);
  sensorstring.reserve(30);
}

void serialEvent() {                                  //if the hardware serial port receives a char
  inputstring = Serial.readStringUntil(13);           //read the string until we see a <CR>
  input_string_complete = true;                       //set the flag used to tell if we have received a completed string from the PC
}

void loop() {                    
  Serial.println("Starting loop ... ");
                  
    DateTime now = rtc.now();
    //if((now.year()==yr)) {
    if(1==1) {
      Serial.print('Taking measurement...');
      take_sal_and_temp();
    }
    delay(1500);
    Serial.println("");
    Serial.println(now.year());
}

void take_sal_and_temp(void) {
 sensors.requestTemperatures(); // Send the command to get temperatures
    //Serial.println(sensors.getTempCByIndex(0));

  if (input_string_complete == true) {                //if a string from the PC has been received in its entirety
    myserial.print(inputstring);                      //send that string to the Atlas Scientific product
    myserial.print('\r');                             //add a <CR> to the end of the string
    inputstring = "";                                 //clear the string
    input_string_complete = false;                    //reset the flag used to tell if we have received a completed string from the PC
  }

  if (myserial.available() > 0) {                     //if we see that the Atlas Scientific product has sent a character
    char inchar = (char)myserial.read();              //get the char we just received
    sensorstring += inchar;                           //add the char to the var called sensorstring
    if (inchar == '\r') {                             //if the incoming character is a <CR>
      sensor_string_complete = true;                  //set the flag
    }
  }


  if (sensor_string_complete == true) {               //if a string from the Atlas Scientific product has been received in its entirety
    if (isdigit(sensorstring[0]) == false) {          //if the first character in the string is a digit
      
      Serial.println(sensorstring);                   //send that string to the PC's serial monitor
      print_EC_data();   
      Serial.println("sensorstring");
    }
    else                                              //if the first character in the string is NOT a digit
    {
                                   //then call this function 
    }
    sensorstring = "";                                //clear the string
    sensor_string_complete = false;                   //reset the flag used to tell if we have received a completed string from the Atlas Scientific product
  }
}

void print_EC_data(void) {                            //this function will pars the string  

  char sensorstring_array[30];                        //we make a char array
  char *EC;                                           //char pointer used in string parsing
  char *TDS;                                          //char pointer used in string parsing
  char *SAL;                                          //char pointer used in string parsing
  char *GRAV;                                         //char pointer used in string parsing
  float f_ec;                                         //used to hold a floating point number that is the EC
  
  sensorstring.toCharArray(sensorstring_array, 30);   //convert the string to a char array 
  EC = strtok(sensorstring_array, ",");               //let's pars the array at each comma
  TDS = strtok(NULL, ",");                            //let's pars the array at each comma
  SAL = strtok(NULL, ",");                            //let's pars the array at each comma
  GRAV = strtok(NULL, ",");                           //let's pars the array at each comma

  Serial.print("EC:");                                //we now print each value we parsed separate
  Serial.println(EC);                                 //this is the EC value
  Serial.println(sensors.getTempCByIndex(0));
  Serial.println();
}
