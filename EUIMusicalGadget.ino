#include <USBComposite.h>
#include "scales.h"

const uint8_t chords[] = {C,G,A,F};

const uint8_t* chord;

uint32_t BPM=100;


USBMIDI midi;
int sensorValue = 0;
void setup() {
    USBComposite.setProductId(0x0031);
    midi.begin();
    delay(1000);
    randomSeed(analogRead(0));
}

void loop() {

  for(int j=0;j<4;j++){
    
      if(j==2)chord=chord_minor;
      else chord=chord_major;
      
      for(int i=0; i<3;i++){

        
        if(j>0)midi.sendNoteOff(0, chords[j-1]+chord[i], 127);//shut the previous chord
        else midi.sendNoteOff(0, chords[4]+chord[i], 127);
        
        midi.sendNoteOn(0, chords[j]+chord[i], 127); //play the new chord
      }
      
      for (int i=0;i<8;i++){
        long randNote = random(sizeof(major)/sizeof(*major)); 
        long randTime = random(3);
        
        midi.sendNoteOn(0, chords[j]+major[randNote], 127);
        delay((60000/BPM)*min(randTime, 8-i));//wait for the time of the note or to the end of chord
        i+=min(randTime, 8-i);
        midi.sendNoteOn(0, chords[j]+major[randNote], 127);
      }
      
      
    }
     
}
