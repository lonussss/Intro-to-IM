int redLed = 11;
int brightness = 0;
int greenLed = 13;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(redLed,OUTPUT);
pinMode(greenLed, OUTPUT);
pinMode(A1,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int buttonState = digitalRead(A1);
int sensorValue = analogRead(A2);

if (buttonState == HIGH )
{
  digitalWrite(13, HIGH);
  //Serial.println("button pressed");
} else{
  digitalWrite(13, LOW);
  
}


sensorValue = constrain(sensorValue, 300,350);

brightness = map(sensorValue,300,350,0,255);
Serial.println(sensorValue);

analogWrite(redLed,brightness);

delay(30);
}

