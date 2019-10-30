/**
 * PolygonPShapeOOP. 
 * 
 * Wrapping a PShape inside a custom class 
 * and demonstrating how we can have a multiple objects each
 * using the same PShape.
 */


// A list of objects
ArrayList<Polygon> polygons;

// Three possible shapes
PShape[] shapes = new PShape[3];

void setup() {
  //fullScreen(P2D);
  size(600,800,P2D);
  /*
  PShape heart = createShape(GROUP);
  PShape circle1 = createShape(ELLIPSE,60,0,100,100);
  PShape circle2 = createShape(ELLIPSE,135,0,100,100);
  PShape triangle = createShape(TRIANGLE,0,0,200,0,100,150);
  
  heart.addChild(circle1);
  heart.addChild(circle2);
  heart.addChild(triangle);
  
  // Draw the group
  //translate(width/2, height/2);
  shape(heart);
 */
 
 
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
  
  boolean bool_heart = true;
  boolean bool_diamond = false;
  boolean bool_star = true;
  
  
  for (int i = 0; i < 25; i++) {
    int selection  = 4;
    if(bool_heart && bool_diamond && bool_star){
      selection = int(random(shapes.length));
    } else if (bool_diamond && bool_star){
      int[] choose = new int[2];
      choose[0] = 1;
      choose[1] = 2;
      selection = int(random(choose.length));
    } else if (bool_diamond && bool_heart){
      int[] choose = new int[2];
      choose[0] = 0;
      choose[1] = 2;
      selection = int(random(choose.length));
    } else if (bool_heart && bool_star){
      int[] choose = new int[2];
       choose[0] = 0;
       choose[1] = 1;
      selection = int(random(choose.length));
    } else if (bool_diamond){
      selection = 2;
    } else if (bool_star){
       selection = 1;
    } else {
      selection = 0;
    }
    
            // Pick a random index
    Polygon p = new Polygon(shapes[selection]);        // Use corresponding PShape to create Polygon
    polygons.add(p);
  }
}

void draw() {
  background(0);

  // Display and move them all
  for (Polygon poly : polygons) {
    poly.display();
    poly.move();
  }
}
