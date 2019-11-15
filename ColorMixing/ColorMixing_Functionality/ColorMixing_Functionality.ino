//Tutorial for RBG LED: https://www.youtube.com/watch?v=5Qi93MjlqzE 

Code
int red_light_pin= 11;
int green_light_pin = 10;
int blue_light_pin = 9;
int pallete_red = A0;
int pallete_yellow = A1; // FSR is connected to analog 0
int pallete_blue = A2;
int sensorReading;  
void setup() {
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
}
void loop() {
  bool red = isTouched(pallete_red);
  bool yellow = isTouched(pallete_tellow);
  bool blue = isTouched(pallete_blue);
  RGB_color(255, 0, 0); // Red
  delay(1000);
  // yellow?
  RGB_color(0, 0, 255); // Blue
  delay(1000);
}
void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}
bool isTouched(int sensorPin) {
  sensorReading = analogRead(sensorPin);
  if (sensorReading > 200) {
    return true;
  } else {
    return false;
  }
  delay(20);
}
