/* 
 Intro April 16 
 Aaron's guest lecture 
 Final example, of lines drawn between many planets 
 orbiting around their centers of orbit
 */

// I think of these as planets
Rotator[] rotators;

void setup() {
  size (640, 360);

  rotators = new Rotator[200];

  // random centers of orbit for the 200 planets
  for (int i =0; i < 200; i++) {
    float x = random(width);
    float y = random(height);

    // note that each planet has its index
    rotators[i] = new Rotator(x, y, i);
  }
}


void draw() {
  background(255);

  for (Rotator r : rotators) {
    r.rotateLine();
    r.checkMouse();
    r.drawLine(rotators);
  }
}

class Rotator {

  float x, y; // Our current location
  float centerX, centerY; // center of our orbit
  float angle; // current angle around the center of orbit
  float radius; // orbit radius
  float acceleration, velocity, direction;

  // our index, so we identify ourselves in the array of all planets
  int index; 

  Rotator(float _centerX, float _centerY, int _index) {
    centerX = _centerX;
    centerY = _centerY;
    index = _index;
    angle =  velocity = acceleration = 0;
    radius = random(40, 80);
    x = y = 0; 
    float coinFlip = random(1);
    if (coinFlip > .5) { // could use round() function
      direction = 1;
    } else {
      direction = -1;
    }
  }

  void rotateLine() {
    velocity += acceleration;
    // velocity *= direction;
    angle += velocity*direction;
    acceleration = 0;
    velocity *= .98;
  }

  void checkMouse() {
    if (dist(mouseX, mouseY, centerX, centerY) < radius
      && mouseX != pmouseX 
      && mouseY != pmouseY) 
    {
      acceleration += .002*direction;
      // println("Mouse!");
    }
  }

  void drawLine(Rotator[] rotators) {

    // calculate the coordinates of this planet
    // according to its distance and angle
    // from its center of orbit
    x = cos(angle) * radius + centerX;
    y = sin(angle) * radius + centerY;

    // See if any of the other planets
    // are close enough to us
    for ( Rotator r : rotators) {

      // except for ourselves
      if (index != r.index) {

        // If a planet is close enough,
        if (dist(x, y, r.x, r.y) < radius) {
          // x, y is our location
          // r.x, r.y is the other planet's location

          // draw a line between us and them
          pushStyle();
          stroke(255, 0, 0, 75);
          line(r.x, r.y, x, y);
          popStyle();
        }
      }
    }
  }
}
