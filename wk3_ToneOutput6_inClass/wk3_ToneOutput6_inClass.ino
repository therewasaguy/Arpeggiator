// power chords!

#include "pitches.h"
int airange;
const int speakerPin = 8;
int note1;
int note2;
int note3;
int n = 16;

//drum variables
int pitch = 0;           // pitch
int pitchChange = 10;    // pitch change amount
long lastSound = 0;      // last time you changed the pitch
int soundDelay = 30;     // delay between pitch steps


// notes in the melody:
int melody[] = {
   NOTE_C2, NOTE_F4,NOTE_C4};
   
int melody2[] = {
   NOTE_C2, NOTE_G4,NOTE_C3};

int melody3[] = {
   NOTE_C2, NOTE_C4,NOTE_C3,NOTE_AS2, NOTE_C4,NOTE_C3};

//starting point for the three notes, controlled by three photoresistors
int n1 = 196;
int n2 = 98;
int n3 = 262;

//starting point for the knob that controls transposition, mapped to a range that makes sense via "mod"
int anaFive = 0;
int mod = 0;

void setup() {
  Serial.begin(9600);
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  note1 = analogRead(A0);
  note2 = analogRead(A1);
  note3 = analogRead(A2);
  anaFive = analogRead(A5);
  mod = map(anaFive, 0, 1023, 1, 8);
  n = map(anaFive, 0, 1023, 8, 256);
  Serial.println(pitch);
  
//  tone(8,65*mod, 10);
  
  if (note1 < 500) {
    for (int thisNote = 0; thisNote < 3; thisNote++) {
     //     to calculate the note duration, take one second divided by the note type.
     //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
       tone(8, melody[thisNote],40);
     //pause for the note's duration plus 30 ms:
     delay(4 +n);

    }
  }
  
  if (note2 < 700) {
    for (int thisNote = 0; thisNote < 3; thisNote++) {
     //     to calculate the note duration, take one second divided by the note type.
     //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
       tone(8, melody2[thisNote],40);
     //pause for the note's duration plus 30 ms:
     delay(4 +n);
    }
  }
  
  if (note3 > 400 && note3 < 700) {
    for (int thisNote = 0; thisNote < 6; thisNote++) {
     //     to calculate the note duration, take one second divided by the note type.
     //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
       tone(8, melody3[thisNote]*2,40);
     //pause for the note's duration plus 30 ms:
     delay(4 +n);
    }
  }
  
  if (note3 < 400) {
    for (int thisNote = 0; thisNote < 6; thisNote++) {
     //     to calculate the note duration, take one second divided by the note type.
     //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
       tone(8, melody3[thisNote],40);

     //pause for the note's duration plus 30 ms:
     delay(4 +n);
    }
  }
  
//make drum sounds!

//snare
if (analogRead(A4) > 10) {
    //make sound
    pitch = map(analogRead(A4), 0, 500, 80, 2000);
  }  
  
//kick
if (analogRead(A3) > 10) {
  pitch = map(analogRead(A3), 0, 500, 60, 1000);
}
  
  if (pitch > 10) {
     makeSound();
  }
}


void makeSound() {
  // if the sound delay has passed since the last time you changed pitch:
  if (millis() - lastSound >= soundDelay) {

    // decrement the brightness using the fade change value:
    pitch = pitch - pitchChange;
    // if the pitch is above 100, play it:
    if (pitch > 10) {
      tone(7, pitch);
      tone(7, pitch + 150);
      tone(7, pitch + 50);
      tone(7, pitch - 10);
    } 
    // if the pitch is below 100Hz, turn it off:
    else {
      noTone(7);
    }
    // save the time you last changed pitch for next check:
    lastSound = millis(); 
  }  
}

