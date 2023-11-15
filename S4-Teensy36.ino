
#include "MIDIUSB.h"
int sol1 = 33;
int sol2 = 34;
int sol3 = 35;
//reorganize
int sol4 = 36;


int hitDur = 12; //duration for each hit (ms)
int coolDown = 0; //cooldown time for each hit (ms)

void setup() {
  
  pinMode(sol1, OUTPUT);
  pinMode(sol2, OUTPUT);
  pinMode(sol3, OUTPUT);
  pinMode(sol4, OUTPUT);
}

void loop() {
  midiEventPacket_t rx = MidiUSB.read();
  switch (rx.header) {
    case 0x9:            //Note On message
      handleNoteOn(
        rx.byte1 & 0xF,  //channel
        rx.byte2,        //pitch
        rx.byte3         //velocity
      );
      break;
    default:
      break;
  }
}

void handleNoteOn(byte channel, byte pitch, byte velocity) {
  hitDur = map(velocity, 0, 127, 2, 27);
  if (pitch == 36) 
  {hit(sol1);}
  if (pitch == 37)
  {hit(sol2);}
  if (pitch == 38)
  {hit(sol3);}
  if (pitch == 39)
  {hit(sol4);}
}

void hit(int drum) {
  digitalWrite(drum, HIGH);  //turn solenoid all the way on
  delay(hitDur);                                      // wait
  digitalWrite(drum, LOW);  //turn solenoid all the way off
  delay(coolDown);
}
