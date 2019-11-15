//Tutorial for RBG LED: https://www.youtube.com/watch?v=5Qi93MjlqzE
int red_light_pin= 11;
int green_light_pin = 10;
int blue_light_pin = 9;
int pallete_red = A0;
int pallete_yellow = A1; // FSR is connected to analog 0
int pallete_blue = A2;
int sensorReading;  
int colorCount[3] = {0, 0, 0};
// this is used to make sure the count does not increase if 
//the user keeps holding a color for longer than a loop
bool canIncrease[3] = {true, true, true};

void setup() {
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
}

void loop() {
  touched(pallete_red, 0);
  touched(pallete_yellow, 1);
  touched(pallete_blue, 2);
//  if (touched the water button) {
    reset();
//  }
 // at this point we will have the count for each
 
//  RGB_color(255, 0, 0); // Red
//  delay(1000);
}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}

void touched(int sensorPin, int index) {
  sensorReading = analogRead(sensorPin);
  if (sensorReading > 200 && canIncrease[index] == true) {
    colorCount[index] += 1;
    canIncrease[index] = false;
  } else {
    canIncrease[index] = true;
  }
}

void reset() {
  for(int i = 0; i < 3; i++) {
    colorCount[i] = 0;
    canIncrease[i] = true;
  }
}
