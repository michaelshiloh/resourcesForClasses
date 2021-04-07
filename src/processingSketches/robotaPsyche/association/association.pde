/*
Vehicles that make associations (red = aggressive)
 
 Michael Shiloh
 March 21 2021
 
 Change log
 21 mar 2021 - ms - initial entry
 03 apr 2021 - ms - add ability to move vehicles
 04 apr 2021 - ms - aggression is random rather than based on vehicle speed
 07 apr 2021 - ms - remove all unnecessary stuff to make it easier to read
 
 Based on examples from The Nature of Code by Daniel Shiffman - Thanks Dan!
 
 This code is in the public domain
 */

ArrayList<Vehicle> vehicles = new ArrayList<Vehicle>();
FlowField f;
boolean singleFrame = true; // For debugging: when true, do only one frame and then stop
int numberVehicles = 20; // no longer a constant
int redVehiclesThatAreAlsoAggressive = 0;

void setup() {
  size (900, 900);
  f = new FlowField(15);

  // Make some vehicles to start with
  for (int i = 0; i < numberVehicles; i++) {
    vehicles.add(new Vehicle(
      random(width), random(height), // location
      random(-10, 10), random(-10, 10), // velocity
      i )); // serial number is the index number
  }

  //vehicles.add(new Vehicle(100, 100, 0, 0, 0));
  //vehicles.add(new Vehicle(100, 120, 0, s50, 1));
}

void draw() {
  background(200);
  // f.display(); // this really slows things down so use only when needed

  // If the mouse button is pressed, allow the mouse to drag
  // around the closest vehicle
  if (mousePressed) {
    Vehicle closestVehicle = getClosestVehicleTo(mouseX, mouseY);
    PVector newLocation = new PVector(mouseX, mouseY);
    closestVehicle.setLocation(newLocation);
  }

  // Here is the usual loop as developed in The Nature of Code
  for (Vehicle v : vehicles) {

    // Apply forces as accelerations. Each force adds an acceleration
    v.avoidAggressive(vehicles);
    // v.follow(f); // Apply the steering force to follow the flow field

    // Update the velocity and location
    // based on the accumilated acceleration
    // This also clears the acceleration at the end of the update so that we're
    // ready to start accumilating new accelerations in the next frame
    v.update();

    v.display(); // display the vehicle
  }

  // Remove any vehicles that have gone beyond the canvas
  for (int i = vehicles.size() - 1; i >= 0; i--) {
    Vehicle v = vehicles.get(i);
    if (v.offCanvas()) {
      // println("removing vehicle number " + v.getSerialNumber());
      vehicles.remove(i);
    }
  }

  if (singleFrame) {
    noLoop(); // for debugging
  }
}

// mouseClicked() is called after a mouse button has been pressed and then released
// Inspect the vehicle that is closest to the mouse
void mouseClicked() {

  Vehicle closestVehicle = getClosestVehicleTo(mouseX, mouseY);
  closestVehicle.inspect();
}

// Return the vehicle closest to the given location
Vehicle getClosestVehicleTo(float x, float y) {

  Vehicle closestVehicle = vehicles.get(0);
  float closestVehicleDistance = width*height; //assume worst case
  PVector location = new PVector(x, y);

  for (Vehicle v : vehicles) {
    float distance = v.distanceTo(location);

    if ( distance < closestVehicleDistance ) {
      closestVehicle = v;
      closestVehicleDistance = distance;
    }
  }
  return closestVehicle;
}

void keyPressed() {
  switch (key) {
  case 'p':
    println("Loop paused; framecount = " + frameCount);
    noLoop();
    break;
  case 'r':
    singleFrame = false;
    loop();
    break;
  case 'd':
    frameRate -= 10;
    println("frameRate = " + frameRate);
    break;
  case 'u':
    frameRate += 10;
    println("frameRate = " + frameRate);
    break;
  case 's': // single frame
    singleFrame = true;
    // println("single frame; framecount = " + frameCount);
    loop();
    break;
  case 'n':
    //vehicles.add(new Vehicle(mouseX, mouseY, numberVehicles++));
    break;
  default:
    println("p = pause; r = run; d = slow down; u = speed up; s = single frame; n = new vehicle");
  }
}
