void setup() {


pinMode(13,OUTPUT);
pinMode(A2, INPUT);

}

void loop() {

int buttonState = digitalRead(A2);

if (buttonState == HIGH) {

digitalWrite(13, HIGH);

} else {

digitalWrite(13, LOW);

}

}