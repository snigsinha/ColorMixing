import processing.serial.*;
import ddf.minim.*;

Minim minim;
AudioPlayer playA;
AudioPlayer playB;
//AudioPlayer playC;

int lf = 10; // Linefeed in ASCII
String myString = null;
Serial myPort; // The serial port
int sensorValue = 0;

void setup() {
  // Open the port you are using at the rate you want:
  myPort = new Serial(this, "/dev/cu.usbmodem14401", 9600);
  myPort.clear();
  // Throw out the first reading, in case we started reading 
  // in the middle of a string from the sender.
  myString = myPort.readStringUntil(lf);
  myString = null;
 // we pass this to Minim so that it can load files from the data directory
 minim = new Minim(this);
 // loadFile will look in all the same places as loadImage does.
 // this means you can find files that are in the data folder and the 
 // sketch folder. you can also pass an absolute path, or a URL.
 // Change the name of the audio file here and add it by clicking on "Sketch —> Import File"
 playA = minim.loadFile("bass.mp3"); 
 playB = minim.loadFile("flute.mp3");
 //playC = minim.loadFile("guitar.mp3");
}

void draw() {
  // check if there is something new on the serial port
  while (myPort.available() > 0) {
  // store the data in myString 
  myString = myPort.readStringUntil(lf);
  // check if we really have something
  if (myString != null) {
    myString = myString.trim(); // let's remove whitespace characters
    // if we have at least one character...
    if(myString.length() > 0) {
       println(myString); // print out the data we just received
       // if we received a number (e.g. 123) store it in sensorValue, we sill use this to change the background color. 
       try {
           sensorValue = Integer.parseInt(myString);
           // As the range of an analog sensor is between 0 and 1023, we need to 
           // convert it in order to use it for the background color brightness
           int brightness = (int)map(sensorValue, 0, 1023, 0, 255);
           background(brightness);
       } catch(Exception e){}
       if(myString.equals("A")){
          if(playA.isPlaying() == false){
              playA.play();
       if(myString.equals("B")){
          if(playB.isPlaying() == false){
              playB.play();
          }
          
       }
    }
  }
 }
}
  }
}
