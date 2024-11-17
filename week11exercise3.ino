int ledPin = 8;       // Pin connected to the LED
int sensorPin = A0;   // Pin connected to the analog sensor
String inputString = "";  // String to accumulate incoming serial data
bool stringComplete = false; // Flag to check if a full command is received

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); 
}

void loop() {
  

  while(Serial.available()){
    String bounced = Serial.readStringUntil('\n');  //read serial string until new line
    if(bounced == "bounced"){
      flashLED();
    }
  int sensorValue = analogRead(sensorPin); // Read the analog sensor value
  int mappedValue = map(sensorValue, 0, 1023, -3 ,3);  // Map the sensor value to a range (-1 to 1)
  Serial.println(mappedValue); // Send the mapped value to p5.js
  }

  

}

void flashLED() {
  digitalWrite(ledPin, HIGH); // Turn LED on
  delay(100);                 // Keep LED on for 100 ms
  digitalWrite(ledPin, LOW);  // Turn LED off
}