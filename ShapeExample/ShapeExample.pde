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

boolean bool_heart = true; //flute
boolean bool_diamond = true; //bass
boolean bool_star = true; //guitar

ArrayList<Polygon> hearts;
ArrayList<Polygon> stars;
ArrayList<Polygon> diamonds;

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
  
  hearts = new ArrayList<Polygon>();
  diamonds = new ArrayList<Polygon>();
  stars = new ArrayList<Polygon>();

  for (int i = 0; i < 25; i++) {
    hearts.add(new Polygon(heart));
  }
   for (int i = 0; i < 25; i++) {
    stars.add(new Polygon(star));
  }
   for (int i = 0; i < 25; i++) {
    diamonds.add(new Polygon(diamond));
  }
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
  
  //System.out.println(bool_diamond || bool_heart || bool_star);
  if (bool_diamond) {
    playDiamond.play();
    for(Polygon pol : diamonds) {
      pol.display();
      pol.move();
    }
  } else {
    playDiamond.pause();
  }
  if (bool_heart) {
    playHeart.play();
    for(Polygon pol : hearts) {
      pol.display();
      pol.move();
    }
  } else {
    playHeart.pause();
  }
  if (bool_star) {
    playStar.play();
    for(Polygon pol : stars) {
      pol.display();
      pol.move();
    }
  } else {
    playStar.pause();
  }
}
