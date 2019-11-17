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
int r_g_b[3] = {0,0,0};

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

 for(int count : colorCount) {
    // math stuff
 }
 
  RGB_color(r_g_b[0], r_g_b[1], r_g_b[2]); // Red
  delay(1000);
}

void RYB_to_RBG() {
  int p = min(colorCount[1],colorCount[2]);
  int x[3] = {0,100,100};
  int y[3] = {0,0,100};
  int z[3] = {100,100,0};
  int q[3] = {0,-100,0};

  int j = colorCount[2]*z[0];
  int k = colorCount[0]*x[1]+ colorCount[2]*z[1]+ q[1]*p;
  int l = x[2]*colorCount[0] + colorCount[1]*y[2];


  j = normalize(j,0,100);
  k = normalize(k,0,100);
  l = normalize(l,0,100);
  
  int r = 255*((100-j)/100);
  int g = 255*((100-k)/100);
  int b = 255*((100-l)/100);

  r_g_b[0] = r;
  r_g_b[1] = g;
  r_g_b[2] = b;
  
}

int normalize(int value, int min, int max) {
  int normalized = (value - min) / (max - min);
  return normalized;
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
