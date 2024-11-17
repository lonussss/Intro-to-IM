int sensor = A0; 

void setup() {

  Serial.begin(9600);


 
}

void loop() {
      int sensorValue= analogRead(sensor);
      int mappedValue = map(sensorValue,0,1023,0,640); //mapped value to size of canvas
      Serial.println(mappedValue); //send value to p5.js
  }