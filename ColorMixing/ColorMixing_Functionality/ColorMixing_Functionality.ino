//Tutorial for RBG LED: https://www.youtube.com/watch?v=5Qi93MjlqzE
int red_light_pin= 11;
int green_light_pin = 10;
int blue_light_pin = 9;
int pallete_red = A0;
int pallete_yellow = A1; // FSR is connected to analog 0
int pallete_blue = A2;
int sensorReading;  
int colorCount[3] = {0, 0, 0}; //R, Y, B
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
  Serial.println(colorCount[0]);
  Serial.println(colorCount[1]);
  Serial.println(colorCount[2]);
  delay(300);
}

void RYB_to_RGB() {
  int p = min(colorCount[1],colorCount[2]);
  int r[3] = {0,100,100};
  int y[3] = {0,0,100};
  int b[3] = {100,100,0};
  int g[3] = {0,-100,0};

  int rgb_r[3] = {colorCount[0]*r[0], colorCount[0]*r[1], colorCount[0]*r[2]};
  int rgb_y[3] = {colorCount[1]*y[0], colorCount[1]*y[1], colorCount[1]*y[2]};
  int rgb_b[3] = {colorCount[2]*b[0], colorCount[2]*b[1], colorCount[1]*b[2]};
  int rgb_g[3] = {p*g[0], p*g[1], p*g[2]};
  

  int r_column = rgb_r[0] + rgb_y[0] + rgb_b[0] + rgb_g[0];
  int g_column = rgb_r[1] + rgb_y[1] + rgb_b[1] + rgb_g[1];
  int b_column = rgb_r[2] + rgb_y[2] + rgb_b[2] + rgb_g[2];

  int max_ratio = max(r_column, max(g_column, b_column))/100;
  
  r_column = r_column/max_ratio;
  g_column = g_column/max_ratio;
  b_column = b_column/max_ratio;
  
  int r_final = 255*((100- r_column)/100);
  int g_final = 255*((100-g_column)/100);
  int b_final = 255*((100-b_column)/100);

  r_g_b[0] = r_final;
  r_g_b[1] = g_final;
  r_g_b[2] = b_final;
  
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
