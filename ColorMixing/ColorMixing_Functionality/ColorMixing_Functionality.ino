//Tutorial for RBG LED: https://www.youtube.com/watch?v=5Qi93MjlqzE
int LED_R= 11;
int LED_G = 10;
int LED_B = 9;

int LED_R_guess= 7;
int LED_G_guess = 6;
int LED_B_guess = 5;

int pallete_red = A0;
int pallete_yellow = A1; // FSR is connected to analog 0
int pallete_blue = A2;
int water = A3;


int sensorReading;  
float colorCount[3] = {0, 0, 0}; //R, Y, B

// RYB proportion for purple, orange, green,red, yellow, blue
float colorsGuess[6][3] = {{0.5, 0.0, 0.5}, {0.5, 0.5, 0.0}, {0.0, 0.5, 0.5}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};
float current[3]; 

// this is used to make sure the count does not increase if 
//the user keeps holding a color for longer than a loop
bool canIncrease[3] = {true, true, true};
int r_g_b[3] = {0,0,0};
int r_g_b_guess[3] = {0, 0, 0};

void setup() {
  //user
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  //guessing
  pinMode(LED_R_guess, OUTPUT);
  pinMode(LED_G_guess, OUTPUT);
  pinMode(LED_B_guess, OUTPUT);
  Serial.begin(9600);
  display_color_guess();
 
}

void loop() {
  touchedColor(pallete_red, 0);
  touchedColor(pallete_yellow, 1);
  touchedColor(pallete_blue, 2);

  if(guessed_right()) {
    blinkLED();
    reset();
    display_color_guess();
  }
  
  if (touchedWater(water)) {
    reset();
  }
  
  RYB_to_RGB();
  RGB_color(r_g_b[0], LED_R, r_g_b[1], LED_G, r_g_b[2], LED_B);
  RGB_color(r_g_b_guess[0], LED_R_guess, r_g_b_guess[1], LED_G_guess, r_g_b_guess[2], LED_B_guess);

//  Serial.println(colorCount[0]);
//  Serial.println(colorCount[1]);
//  Serial.println(colorCount[2]);
//  
  Serial.println(r_g_b[0]);
  Serial.println(r_g_b[1]);
  Serial.println(r_g_b[2]);
  delay(100);
}

void generateNewColor() {
  int ran = int(random(0, 6));
  memcpy(current, colorsGuess[ran], 3*sizeof(float));
}

void display_color_guess() {

  generateNewColor();

  int r_steps = current[0] + 4*current[1] - 4*min(current[1],current[2]); // red + yellow - green
  int g_steps = current[1]; // yellow
  int b_steps = current[2] - min(current[1],current[2]); // blue - green

  float max_steps = max(r_steps, max(g_steps, b_steps))*1.0;

  r_g_b_guess[0] = (r_steps/max_steps)*255;
  r_g_b_guess[1] = (g_steps/max_steps)*255;
  r_g_b_guess[2] = (b_steps/max_steps)*255;
}

bool guessed_right() {
  bool matched = true;
  int total = colorCount[0] + colorCount[1] + colorCount[2];
  //float check = {0.0,0.0,0.0};

  for(int i = 0; i < 3; i++){ //check within for loop
    if (current[i] != (colorCount[i]/total)){
      matched = false;
    }
  }
  return matched; 
  
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


void RGB_color(int r_light, int r_pin, int g_light, int g_pin, int b_light, int b_pin)
 {
  analogWrite(r_pin, r_light);
  analogWrite(g_pin, g_light);
  analogWrite(b_pin, b_light);
}

void touchedColor(int sensorPin, int i) {
  sensorReading = analogRead(sensorPin);
  if (sensorReading > 200 && canIncrease[i]) {
    colorCount[i] += 1;
    canIncrease[i] = false;
  } else if(sensorReading < 200) {
    canIncrease[i] = true;
  }
}

bool touchedWater(int sensorPin) {
  sensorReading = analogRead(sensorPin);
  if (sensorReading > 200) {
    return true;
  } else {
    return false;
  }
}

void blinkLED(){
  for(int i = 0; i < 5; i++){
    
    RGB_color(r_g_b[0], LED_R, r_g_b[1], LED_G, r_g_b[2], LED_B);
    RGB_color(r_g_b_guess[0], LED_R_guess, r_g_b_guess[1], LED_G_guess, r_g_b_guess[2], LED_B_guess);
    delay(500);
    RGB_color(0, LED_R, 0, LED_G, 0, LED_B);
    RGB_color(0, LED_R_guess, 0, LED_G, 0, LED_B);
    delay(500);
  }
}


void reset() {
  for(int i = 0; i < 3; i++) {
    colorCount[i] = 0;
    canIncrease[i] = true;
  }
}
