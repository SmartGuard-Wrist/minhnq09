int sensorPin = 2;

void setup() {
    pinMode(sensorPin, INPUT);
    Serial.begin(9600);
}

void loop() {
  int value = digitalRead(sensorPin);
  Serial.println(value);
  delay(100);

}
