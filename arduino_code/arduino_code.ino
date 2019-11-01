int diamondSensorPin = A0; // FSR is connected to analog 0
int heartSensorPin = A1;
int starSensorPin = A2;
int sensorReading;      // the analog reading from the FSR resistor divider

void setup(void) {
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
}
 
void loop(void) {
  isTouched(diamondSensorPin, 0);
  isTouched(heartSensorPin, 1);
  isTouched(starSensorPin, 2);
}

bool isTouched(int sensorPin, int serialOutVal) {
  sensorReading = analogRead(sensorPin);
  if (sensorReading > 200) {
    Serial.println(serialOutVal);
  } 
}
