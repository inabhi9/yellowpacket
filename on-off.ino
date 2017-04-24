#include <ctype.h>
#include <SoftwareSerial.h>

#define bit9600Delay 100  
#define halfBit9600Delay 50
#define bit4800Delay 188 
#define halfBit4800Delay 94 

byte rx = 7;
byte tx = 6;
byte epsonPin = 8;
byte benqPin = 9;
byte penasonicPin = 10;
bool needSend = false;
int prevEpsonStatus = HIGH;
int prevBenqStatus = HIGH;
int prevPenasonicStatus = HIGH;

char EPSON_ON[] = "PWR ON";
char EPSON_OFF[] = "PWR OFF";
char BENQ_ON[] = "<CR>*pow=on#<CR>";
char BENQ_OFF[] = "<CR>*pow=off#<CR>";
char PENASONIC_ON[] = "STXPONETX";
char PENASONIC_OFF[] = "STXPOFETX";

SoftwareSerial mySerial(rx, tx); // RX, TX

void setup() {
    pinMode(epsonPin, INPUT_PULLUP);
    pinMode(benqPin, INPUT_PULLUP);
    pinMode(penasonicPin, INPUT_PULLUP);
  
    // set the data rate for the SoftwareSerial port
    mySerial.begin(9600);
    //Serial.begin(9600);
    mySerial.println("YellowPacket booted!");
}


void loop() {
    parseAndAct(epsonPin, prevEpsonStatus, EPSON_ON, EPSON_OFF);
    parseAndAct(benqPin, prevBenqStatus, BENQ_ON, BENQ_OFF);
    parseAndAct(penasonicPin, prevPenasonicStatus, PENASONIC_ON, PENASONIC_OFF);
    //delay(10);
}



void parseAndAct(byte pin, int &prevStatus, char onMsg[], char offMsg[]) {
    int currStatus = digitalRead(pin);
    needSend  = currStatus != prevStatus;

    if (needSend == true){
        needSend = false;
        if (currStatus == LOW) {
            mySerial.println(onMsg);
        } else if (currStatus == HIGH) {
            mySerial.println(offMsg);
        }
    }

    prevStatus = digitalRead(pin);
    Serial.println(currStatus);
}
