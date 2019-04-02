#include <USBComposite.h>
#include "scales.h"

#define TRIGGER_PIN    PB12
#define ECHO_PIN       PB13

#define MELODY 1
#define CHORDS 1
const uint8_t chords[] = {C,G,A,F};

const uint8_t* chord;

uint32_t BPM=160;


USBMIDI midi;
int sensorValue = 0;
void setup() {
    USBComposite.setProductId(0x0031);
    midi.begin();
    delay(1000);
    randomSeed(analogRead(0));
    pinMode(TRIGGER_PIN,OUTPUT);// trigger pin
  pinMode(ECHO_PIN,INPUT);// echo pin
}

void loop() {

  long randNote = random(sizeof(major)/sizeof(*major));
  long randTime=0;
  
  for(int j=0;j<4;j++){
    
      if(j==2)chord=chord_pwr;
      else chord=chord_pwr;
      if(CHORDS){
        for(int i=0; i<2;i++){
          if(j>0)midi.sendNoteOff(0, chords[j-1]+chord[i]-12, 127);//shut the previous chord
          else midi.sendNoteOff(0, chords[2]+chord[i]-12, 127);
        
          midi.sendNoteOn(0, chords[j]+chord[i]-12, 127); //play the new chord
        }
      }
      
      for (int i=0;i<8;i++){
       if (MELODY){
        if(randTime==0){
          if(j==2)chord=chord_minor;

          if(j==3) midi.sendNoteOff(0, chords[j]+minor[randNote], 127);
          else midi.sendNoteOff(0, chords[j]+major[randNote], 127);//shut the previous note
          
          long newNote = randNote;
          while(newNote == randNote) randNote += random(4)-2;
          
              digitalWrite(TRIGGER_PIN,HIGH);
              delay(1);
              digitalWrite(TRIGGER_PIN,LOW);
  
              uint32_t pulseLen  = pulseIn( ECHO_PIN, HIGH );
              randNote=map(pulseLen/58.138,10,50,0,6);
              
          if(randNote<0)randNote=0;
          if(randNote>6)randNote=6;
          randTime = random(2);
          if(j==2) midi.sendNoteOn(0, chords[j]+minor[randNote], 127);
          else midi.sendNoteOn(0, chords[j]+major[randNote], 127);
          
        }else{randTime--;}
       }
        delay(60000/(BPM*2));//wait for the time of the note or to the end of chord
      }
      
      
    }
     
}
