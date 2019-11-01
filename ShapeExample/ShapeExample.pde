import processing.serial.*;
import ddf.minim.*;

Minim minim;
AudioPlayer playDiamond;
AudioPlayer playHeart;
AudioPlayer playStar;

int lf = 10; // Linefeed in ASCII
String inputString = null;
Serial myPort; // The serial port
int sensorValue = 0;

boolean bool_heart = false; //flute
boolean bool_diamond = false; //bass
boolean bool_star = false; //guitar
// A list of objects
ArrayList<Polygon> polygons;

// Three possible shapes
PShape[] shapes = new PShape[3];

void setup() {
  fullScreen(P2D);
  //size(600,800,P2D);
  
  minim = new Minim(this);
  
  myPort = new Serial(this, "/dev/cu.usbmodem14401", 9600);
  
  // bass always playing
  minim.loadFile("bass.mp3").play();
  
  // setup shapes' music 
  playDiamond = minim.loadFile("piano.mp3"); 
  playHeart = minim.loadFile("flute.mp3");
  playStar = minim.loadFile("guitar.mp3");
 
  PShape heart = createShape();

  heart.beginShape();
  heart.fill(255, 0, 0);
  heart.vertex(50, 15);
  heart.bezierVertex(50, -5, 90, 5, 50, 40);
  heart.vertex(50, 15);
  heart.bezierVertex(50, -5, 10, 5, 50, 40);
  heart.endShape();
  heart.setStroke(false);
  heart.scale(2.0);
  
  
  //this is the star
  PShape star = createShape();
  star = createShape();  
  star.beginShape();
  star.fill(255, 204, 0);
  star.noStroke();
  star.vertex(0, -50);
  star.vertex(14, -20);
  star.vertex(47, -15);
  star.vertex(23, 7);
  star.vertex(29, 40);
  star.vertex(0, 25);
  star.vertex(-29, 40);
  star.vertex(-23, 7);
  star.vertex(-47, -15);
  star.vertex(-14, -20);
  star.endShape(CLOSE);
  
  
  //this is the diamond
  PShape diamond = createShape();
  diamond.beginShape();
  diamond.fill(0, 0, 255);
  diamond.vertex(0,40);
  diamond.vertex(30,0);
  diamond.vertex(60,40);
  diamond.vertex(30,80);
  diamond.vertex(0,40);
  diamond.noStroke();
  diamond.endShape(CLOSE);
  
  
  shapes[0] = heart;
  shapes[1] = star;
  shapes[2] = diamond;
  
  

  // Make an ArrayList
  polygons = new ArrayList<Polygon>();
  

  
  
  //for (int i = 0; i < 25; i++) {
  //  int selection  = 4;
  //  if(bool_heart && bool_diamond && bool_star){
  //    selection = int(random(shapes.length));
  //    playBass.play();
  //    playFlute.play();
  //    playGuitar.play();
  //  } else if (bool_diamond && bool_star){
  //    int[] choose = new int[2];
  //    choose[0] = 1;
  //    choose[1] = 2;
  //    selection = int(random(2));
  //    selection = choose[selection];
  //    playBass.play();;
  //    playGuitar.play();
  //  } else if (bool_diamond && bool_heart){
  //    int[] choose = new int[2];
  //    choose[0] = 0;
  //    choose[1] = 2;
  //    selection = int(random(2));
  //    selection = choose[selection];
  //    playBass.play();
  //    playFlute.play();
  //  } else if (bool_heart && bool_star){
  //    int[] choose = new int[2];
  //     choose[0] = 0;
  //     choose[1] = 1;
  //    selection = int(random(2));
  //    selection = choose[selection];
  //    playFlute.play();
  //    playGuitar.play();
  //  } else if (bool_diamond){
  //    selection = 2;
  //    playBass.play();
  //  } else if (bool_star){
  //     selection = 1;
  //     playGuitar.play();
  //  } else {
  //    playFlute.play();
  //    selection = 0;
  //  }
    
  //          // Pick a random index
  //  Polygon p = new Polygon(shapes[selection]);// Use corresponding PShape to create Polygon
  //  polygons.add(p);
    
  //}
}



void draw() {
  background(0);
  
  if (myPort.available() > 0){
    inputString = myPort.readStringUntil(lf);
    if (inputString != null && inputString.trim().length() > 0){
      inputString = inputString.trim();
      System.out.println(inputString);
      if (inputString.equals("DY")) {
        bool_diamond = true;
      } else if (inputString.equals("DN")) {
        bool_diamond = false;
      } else if (inputString.equals("HY")) {
        bool_heart = true;
      } else if (inputString.equals("HN")) {
        bool_heart = false;
      } else if (inputString.equals("SY")) {
        System.out.println("SY!!!!!");
        bool_star = true;
      } else if (inputString.equals("SN")) {
        bool_star = false;
      }
    }
  }
  
  System.out.println(bool_diamond || bool_heart || bool_star);
  if (bool_diamond) {
    playDiamond.play();
  } else {
    playDiamond.pause();
  }
  if (bool_heart) {
    playHeart.play();
  } else {
    playHeart.pause();
  }
  if (bool_star) {
    playStar.play();
  } else {
    playStar.pause();
  }
  
  //// Display and move them all
  //for (Polygon poly : polygons) {
  //  poly.display();
  //  poly.move();
  //}
}
