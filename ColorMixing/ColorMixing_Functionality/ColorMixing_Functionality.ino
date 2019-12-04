//Tutorial for RBG LED: https://www.youtube.com/watch?v=5Qi93MjlqzE
int red_light_pin= 11;
int green_light_pin = 10;
int blue_light_pin = 9;
int pallete_red = A0;
int pallete_yellow = A1; // FSR is connected to analog 0
int pallete_blue = A2;
int sensorReading;  
float colorCount[3] = {0, 0, 0}; //R, Y, B
// this is used to make sure the count does not increase if 
//the user keeps holding a color for longer than a loop
bool canIncrease[3] = {true, true, true};
int r_g_b[3] = {0,0,0};

void setup() {
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  touched(pallete_red, 0);
  touched(pallete_yellow, 1);
  touched(pallete_blue, 2);
//  if (touched the water button) {
//    reset();
//  }
 // at this point we will have the count for each
  RYB_to_RGB();
  RGB_color(r_g_b[0], r_g_b[1], r_g_b[2]); // Red, green, blue
  
//  Serial.println(colorCount[0]);
//  Serial.println(colorCount[1]);
//  Serial.println(colorCount[2]);
//  
  Serial.println(r_g_b[0]);
  Serial.println(r_g_b[1]);
  Serial.println(r_g_b[2]);
  delay(100);
}

void RYB_to_RGB() {

  int r_steps = colorCount[0] + 4*colorCount[1] - 4*min(colorCount[1],colorCount[2]); // red + yellow - green
  int g_steps = colorCount[1]; // yellow
  int b_steps = colorCount[2] - min(colorCount[1],colorCount[2]); // blue - green

  float max_steps = max(r_steps, max(g_steps, b_steps))*1.0;

  r_g_b[0] = (r_steps/max_steps)*255;
  r_g_b[1] = (g_steps/max_steps)*255;
  r_g_b[2] = (b_steps/max_steps)*255;
  
}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}

void touched(int sensorPin, int i) {
  sensorReading = analogRead(sensorPin);
  if (sensorReading > 200 && canIncrease[i]) {
    colorCount[i] += 1;
    canIncrease[i] = false;
  } else if(sensorReading < 200) {
    canIncrease[i] = true;
  }
}


void reset() {
  for(int i = 0; i < 3; i++) {
    colorCount[i] = 0;
    canIncrease[i] = true;
  }
}
