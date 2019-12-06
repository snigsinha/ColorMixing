//Tutorial for RBG LED: https://www.youtube.com/watch?v=5Qi93MjlqzE
int LED_R= 11;
int LED_G = 10;
int LED_B = 9;

int LED_R_guess= 7;
int LED_G_guess = 6;
int LED_B_guess = 5;

int pallete_red = A0;
int pallete_yellow = A1; 
int pallete_blue = A2;
int water = A3;
int ran = 0;


int sensorReading;  
float colorCount[3] = {0, 0, 0}; //R, Y, B

// yellow, purple, red, blue, green, redder purple, cyan
float colorsGuess[7][3] = {{255.0,63.75,0},{255.0,0,255.0}, {255.0,0,0}, {0,0,255.0},{0,255.0,0}, {255.0,0.0,127.50}, {0.0,255.0,255.0}};

// this is used to make sure the count does not increase if 
//the user keeps holding a color for longer than a loop
bool canIncrease[3] = {true, true, true};
float r_g_b[3] = {0.0,0.0,0.0};
float r_g_b_guess[3] = {0.0, 0.0, 0.0};

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
  generateNewColor();
 
}

void loop() {
  touchedColor(pallete_red, 0);
  touchedColor(pallete_yellow, 1);
  touchedColor(pallete_blue, 2);

  if(guessed_right()) {
     Serial.println("colours match");
    blinkLED();
    reset();
    generateNewColor();
  }
  
  if (touchedWater(water)) {
    Serial.println("water touched detected");
    reset();
  }
  
  RYB_to_RGB();
  RGB_color(r_g_b[0], LED_R, r_g_b[1], LED_G, r_g_b[2], LED_B);
  RGB_color(r_g_b_guess[0], LED_R_guess, r_g_b_guess[1], LED_G_guess, r_g_b_guess[2], LED_B_guess);
  delay(100);
}

void generateNewColor() {
  
  
  

  memcpy(r_g_b_guess, colorsGuess[ran], 3*sizeof(float));

  Serial.println(ran);
  ran ++;
  if(ran == 7){
    ran = 0;
  }
 
  

}

bool guessed_right() {
  bool matched = true;

  for(int i = 0; i < 3; i++){ //check within for loop  
    if (r_g_b[i] != (r_g_b_guess[i])){
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
    RGB_color(0, LED_R_guess, 0, LED_G_guess, 0, LED_B_guess);
    delay(500);
  }
}


void reset() {
  for(int i = 0; i < 3; i++) {
    colorCount[i] = 0;
    canIncrease[i] = true;
  }
}
