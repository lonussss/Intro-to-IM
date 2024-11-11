#include "pitches.h"

// Arrays storing each octave for each note (normal notes)
int CNote[] = {NOTE_C1, NOTE_C2, NOTE_C3, NOTE_C4, NOTE_C5, NOTE_C6, NOTE_C7};
int DNote[] = {NOTE_D1, NOTE_D2, NOTE_D3, NOTE_D4, NOTE_D5, NOTE_D6, NOTE_D7};
int ENote[] = {NOTE_E1, NOTE_E2, NOTE_E3, NOTE_E4, NOTE_E5, NOTE_E6, NOTE_E7};
int FNote[] = {NOTE_F1, NOTE_F2, NOTE_F3, NOTE_F4, NOTE_F5, NOTE_F6, NOTE_F7};
int GNote[] = {NOTE_G1, NOTE_G2, NOTE_G3, NOTE_G4, NOTE_G5, NOTE_G6, NOTE_G7};
int ANote[] = {NOTE_A1, NOTE_A2, NOTE_A3, NOTE_A4, NOTE_A5, NOTE_A6, NOTE_A7};
int BNote[] = {NOTE_B1, NOTE_B2, NOTE_B3, NOTE_B4, NOTE_B5, NOTE_B6, NOTE_B7};

// Arrays storing each octave for each sharp note
int CSharpNote[] = {NOTE_CS1, NOTE_CS2, NOTE_CS3, NOTE_CS4, NOTE_CS5, NOTE_CS6, NOTE_CS7};
int DSharpNote[] = {NOTE_DS1, NOTE_DS2, NOTE_DS3, NOTE_DS4, NOTE_DS5, NOTE_DS6, NOTE_DS7};
int FSharpNote[] = {NOTE_FS1, NOTE_FS2, NOTE_FS3, NOTE_FS4, NOTE_FS5, NOTE_FS6, NOTE_FS7};
int GSharpNote[] = {NOTE_GS1, NOTE_GS2, NOTE_GS3, NOTE_GS4, NOTE_GS5, NOTE_GS6, NOTE_GS7};
int ASharpNote[] = {NOTE_AS1, NOTE_AS2, NOTE_AS3, NOTE_AS4, NOTE_AS5, NOTE_AS6, NOTE_AS7};


void setup() {
  pinMode(7, INPUT);
  pinMode(6, INPUT);
  pinMode(5, INPUT);
  pinMode(4, INPUT);
  pinMode(3, INPUT);
  pinMode(2, INPUT);
  pinMode(13, INPUT);  // Switch input
  pinMode(A5, INPUT);
  Serial.begin(9600);  // Start serial communication for debugging
}

void loop() {
  int buttonState7 = digitalRead(7);
  int buttonState6 = digitalRead(6);
  int buttonState5 = digitalRead(5);
  int buttonState4 = digitalRead(4);
  int buttonState3 = digitalRead(3);
  int buttonState2 = digitalRead(2);
  int sensorValue = analogRead(A5);
  int switchValue = digitalRead(13);  // Read switch value
  Serial.println(sensorValue);

  // Map potentiometer to octave range (0 to 6 for array indexing)
  int octave = map(sensorValue, 0, 1023, 0, 6);

  // Check if no button is pressed
  if (buttonState7 == LOW && buttonState6 == LOW && buttonState5 == LOW && 
      buttonState4 == LOW && buttonState3 == LOW && buttonState2 == LOW) {
    noTone(8);  // Stop any tone on pin 8
  }
  
  // Determine which note arrays to use based on switch
  int* currentCNote = switchValue == LOW ? CNote : CSharpNote;
  int* currentDNote = switchValue == LOW ? DNote : DSharpNote;
  int* currentENote = switchValue == LOW ? ENote : ENote;  // No E# note, so reuse ENote
  int* currentFNote = switchValue == LOW ? FNote : FSharpNote;
  int* currentGNote = switchValue == LOW ? GNote : GSharpNote;
  int* currentANote = switchValue == LOW ? ANote : ASharpNote;
  int* currentBNote = switchValue == LOW ? BNote : BNote;  // No B# note, so reuse BNote

  // Play tones based on button presses and octave selection
  if (buttonState7 == HIGH) {
    tone(8, currentCNote[octave]);
  } else if (buttonState6 == HIGH) {
    tone(8, currentDNote[octave]);
  } else if (buttonState5 == HIGH) {
    tone(8, currentENote[octave]);
  } else if (buttonState4 == HIGH) {
    tone(8, currentFNote[octave]);
  } else if (buttonState3 == HIGH) {
    tone(8, currentGNote[octave]);
  } else if (buttonState2 == HIGH) {
    tone(8, currentANote[octave]);
  }
}
