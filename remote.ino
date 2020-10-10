/* 
 * MIT License
 * Copyright (c) 2020 Jack Rayner <hello@jrayner.net>
 */

#include <IRremote.h>

IRsend IrSender;

int result;
int index = 0;
int mode;

String inData;

struct { // Define a structure that contains all of the hex codes
  const char* name;
  uint32_t code;
} array[] = {
{"1"                     ,0x3EC129D6},
{"2"                     ,0x3EC1A956},
{"3"                     ,0x3EC16996},
{"4"                     ,0x3EC1E916},
{"5"                     ,0x3EC119E6},
{"6"                     ,0x3EC19966},
{"7"                     ,0x3EC159A6},
{"8"                     ,0x3EC1D926},
{"9"                     ,0x3EC139C6},
{"0"                     ,0x3EC1C936},
{"10+"                   ,0x3EC1B946},
{"TOGGLE/RETURN"         ,0x3EC17986},
{"PIC/CANCEL"            ,0x3EC18D72},
{"MENU"                  ,0x3EC14DB2},
{"EXIT"                  ,0x3EC1ED12},
{"INFO"                  ,0x3EC1659A},
{"CLOCK/EJECT"           ,0x3EC1D12E},
{"REWIND"                ,0x3EC1619E},
{"FORWARD"               ,0x3EC1E11E},
{"L/R"                   ,0x3EC1B54A},
{"PAUSE/ZOOM"            ,0x3EC1C13E},
{"CHAPTER-"              ,0x3EC19D62},
{"CHAPTER+"              ,0x3EC15DA2},
{"STOP"                  ,0x3EC1A15E},
{"PLAY"                  ,0x3EC141BE},
{"LEFT"                  ,0x3EC1AD52},
{"RIGHT"                 ,0x3EC16D92},
{"UP"                    ,0x3EC12DD2},
{"DOWN"                  ,0x3EC1CD32},
{"OK"                    ,0x3EC11DE2},
{"POWER"                 ,0x3EC101FE},
{"VOL-"                  ,0x1CE3F00F},
{"VOL+"                  ,0x1CE3708F},
{"MUTE"                  ,0x1CE318E7},
{"CH+"                   ,0x1CE350AF},
{"CH-"                   ,0x1CE3D02F},
{"TV/AV"                 ,0x1CE3C837},
{"PNS"                   ,0x1CE348B7},
{"TONE-"                 ,0x5EA1D827},
{"TONE+"                 ,0x5EA158A7},
};

#define ARRAY_LENGTH sizeof(array)/sizeof(array[0]) // Array size

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(9600);
    delay(2000);
    Serial.println(F("START " __FILE__ " from " __DATE__));
    Serial.print(F("Ready to send IR signals at pin "));
    Serial.println(IR_SEND_PIN);
    Serial.println("Choose 1 for remote mode, 2 for L336 programming.");
}

void sendCommand(uint32_t code, const char* name, int mode) {
  Serial.print("Sending code for button ");
  Serial.print(name);
  Serial.print(" (");
  Serial.print(array[index].code, HEX);
  Serial.print(") ");
  
  if ( mode == 2 ) { // Programming mode
    Serial.print("for 15 seconds");
    int i;
    for (i = 1; i < 30; ++i) {
      Serial.print(".");
      IrSender.sendNEC(code, 32); // OSSC uses the NEC protocol
      delay(500);
    }
  }
  else if ( mode == 1 ) // Remote mode
  {
    IrSender.sendNEC(code, 32);
  }
}

void loop() {
  while (Serial.available() > 0) { // While there's data in the serial buffer
    char received = Serial.read();
    inData += received; 

    if (received == '\r') { // If the character was a return, user input has finished
      int x = inData.toInt(); // Returns 0 if data can't be converted

      if (!( mode < 3 && mode > 0)) { // If the mode hasn't been set yet
        if ( x < 3 && x > 0) {
          mode = x;
          Serial.println("Please enter button number.");
        }
        else {
          Serial.println("Invalid input.");
        }
      }
      else { // Else mode is set, user input must be a remote code
        if ( x != 0 &&  x < ARRAY_LENGTH ) {
          x--;
          
          sendCommand(array[x].code, array[x].name,mode);
          Serial.println();
          Serial.println("Please enter button number.");
          while(Serial.available() > 0) { // Discard any received data received when running the IR commands
            char t = Serial.read();
          }
        }
        else {
          Serial.println("Invalid input.");
        }
      }
      inData = ""; // Clear received buffer
    }
  }
}
