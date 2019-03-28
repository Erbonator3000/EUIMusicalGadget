#include <USBComposite.h>

const uint8_t notes[] = {60,62, 63, 65, 67, 69,71, 72};
const int numNotes = sizeof(notes)/sizeof(*notes);

uint8_t currentNote = 0;

USBMIDI midi;

void setup() {
    USBComposite.setProductId(0x0031);
    midi.begin();
    delay(1000);
    randomSeed(analogRead(0));
}

void loop() {

  
  if (currentNote != 0) midi.sendNoteOff(0, currentNote, 127);
  long randNote = random(numNotes); 
  long randTime = random(3);
  
  currentNote = notes[randNote];
  
    midi.sendNoteOn(0, currentNote, 127);
    delay(200*randTime);
}
