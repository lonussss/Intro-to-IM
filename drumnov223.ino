const int numButtons = 16; // Total number of buttons
const int digitalButtonPins[14] = {2, 3, 4, 5, 6, 7, 8, 9, 13, A0, A1,A2,A3,A4}; // Digital button pins
const int analogPin = A5; // Analog pin for the last 2 buttons
const int voltageLevels[2] = {90, 500}; // Expected analog values
const int tolerance = 50; // +/- for voltage readings

bool buttonStates[16] = {false}; // Track all button states

// Shift register pins
const int dataPin = 10;
const int clockPin = 12;
const int latchPin = 11;

uint16_t ledStates = 0;

const int spiralOrder[16] = {0, 1, 2, 3, 7, 11, 15, 14, 13, 12, 8, 4, 5, 6, 10, 9};

void setup() {
  // Initialize digital pins
  for (int i = 0; i < 14; i++) {
    pinMode(digitalButtonPins[i], INPUT_PULLUP);
  }

  // Initialize shift register pins
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);

  Serial.begin(9600);

  spiralEffectRecursive(0);

}

void loop() {
  // Check digital buttons
  for (int i = 0; i < 14; i++) {
    bool isPressed = digitalRead(digitalButtonPins[i]) == LOW;
    if (isPressed && !buttonStates[i]) {
      Serial.println(i);
      buttonStates[i] = true;
      ledStates |= (1 << i);
      updateShiftRegister();
    } else if (!isPressed && buttonStates[i]) {
      buttonStates[i] = false;
      ledStates &= ~(1 << i);
      updateShiftRegister();
    }
  }

  // Check analog buttons
  int analogValue = analogRead(analogPin);
  for (int i = 0; i < 2; i++) {
    int buttonIndex = 14 + i;
    if (abs(analogValue - voltageLevels[i]) < tolerance) {
      if (!buttonStates[buttonIndex]) {
        Serial.println(buttonIndex);
        buttonStates[buttonIndex] = true;
        ledStates |= (1 << buttonIndex);
        updateShiftRegister();
      }
    } else {
      buttonStates[buttonIndex] = false;
      ledStates &= ~(1 << buttonIndex);
      updateShiftRegister();
    }
  }
}
void startupSequence() {
  for (int i = 0; i < 16; i++) {
    ledStates = (1 << i); // Light up one LED at a time
    updateShiftRegister();
    delay(300); // Short delay for animation
  }

  // Turn all LEDs off after the sequence
  ledStates = 0;
  updateShiftRegister();
}
// effect shown when you plug in device or connect to serial
void spiralEffectRecursive(int index) {
  if (index >= 16) {
    // Base case: All LEDs light up for 2 seconds
    ledStates = 0xFFFF; // Turn ON all 16 LEDs
    updateShiftRegister();
    delay(2000); // Keep them ON for 2 seconds

    // Turn off all LEDs
    ledStates = 0; // Turn OFF all LEDs
    updateShiftRegister();
    return;
  }

  //Light up the next LED in the spiral order
  int ledIndex = spiralOrder[index]; // Get the LED index in spiral order
  ledStates = (1 << ledIndex);  // Light up the corresponding LED
  updateShiftRegister();
  delay(100); // Short delay for effect

  // Call recursively for the next index
  spiralEffectRecursive(index + 1);
}


// Shift register update
void updateShiftRegister() {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, (ledStates >> 8));
  shiftOut(dataPin, clockPin, MSBFIRST, ledStates);
  digitalWrite(latchPin, HIGH);
}
