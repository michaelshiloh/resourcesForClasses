
// The vehicle class, more or less straight from the book

class Vehicle {

  PVector location;
  PVector velocity;
  PVector acceleration;
  float maxforce;
  float maxspeed;
  boolean alive;
  boolean isRed;
  int r;
  int serialNumber;
  final float tooClose = 25; // only pay attention to vehicles closer than this

  Vehicle(float x, float y, float vx, float vy, int sn) {

    // internal variables from arguments
    location = new PVector(x, y);
    serialNumber = sn;

    // other internal variables
    acceleration = new PVector(0, 0);
    velocity = new PVector(vx, vy);
    maxforce = 1;
    maxspeed = 4;
    r = 3;
    alive = true;

    if (round(random(1)) == 1) {
      isRed =  true;
    } else {
      isRed = false;
    }
  }

  PVector getVelocity() {
    PVector myVelocity =  velocity.copy(); // is this the right way to make a copy?
    return myVelocity;
  }

  boolean getIsRed() {
    return (isRed);
  }

  boolean offCanvas() {
    if (location.x > width) return true;
    if (location.y > height) return true;
    return false;
  }

  int getSerialNumber() {
    return serialNumber;
  }

  // Am I aggressive?
  boolean getIsAggressive() {
    float chance = random(100);

    if (isRed) {
      // If I am red, the threshold for aggression is 20 (i.e. 80% are aggressive)
      return (chance > 20);
    } else {
      // otherwise, the threshold is 80 (i.e. only 20% are aggressive)
      return(chance > 80);
    }
  }

  void setLocation(PVector _location) {
    location = _location;
  }

  /*
  Different steering algorithms. A vehicle
   could use any, and you can create additional ones.
   Each algorithm calculates and returns a steering force
   */

  // Calculate steering force to seek a target
  // simpleSeek goes to target at max speed
  void simpleSeek(PVector target) {
    PVector desired = PVector.sub(target, location);
    applyForce(applyLimits(desired));
  }

  // Given the desired velocity, return the maximum steering force
  // given limits of speed and steering force
  PVector applyLimits(PVector desiredVelocity) {
    desiredVelocity.normalize();
    desiredVelocity.mult(maxspeed);
    PVector steerForce = PVector.sub(desiredVelocity, velocity);
    steerForce.limit(maxforce);
    return(steerForce);
  }

  // Calculate the steering force to follow a flow field
  void follow(FlowField flow) {
    // Look up the vector at that spot in the flow field
    PVector desired = flow.lookup(location);
    desired.mult(maxspeed);

    // Steering is desired minus velocity
    PVector steer = PVector.sub(desired, velocity);
    applyForce(applyLimits(steer));
  }

  // Avoid aggressive vehicles and notice if they are also red
  void avoidAggressive(ArrayList<Vehicle> vehicles) {


    // to accumilate all the individual avoidance vectors
    int count = 0; // how
    PVector sum = new PVector(0, 0);


    for (Vehicle other : vehicles) {

      // What is the distance between me and another Vehicle?
      float d = PVector.dist(location, other.location);

      // If the distance is zero we are looking at ourselves so skip over ourselves
      if (d == 0) {
        continue;
      }

      // If the distance is greater than tooClose skip this vehicle
      if (d > tooClose) {
        continue;
      }

      // Is other vehicle aggressive?
      boolean otherIsAggressive = other.getIsAggressive();

      // If so, avoid it, using the same logic as in separate
      if (otherIsAggressive) {

        println(); // so messages are seaparated
        // Get the location of this vehicle relative to us
        PVector diff = PVector.sub(location, other.location); // in book, but  wrong way?

        println("I am " + serialNumber + " other is aggressive; will avoid; diff = " + diff);

        diff.normalize(); // why normalize? wouldn't we want to separate more from closer vehicles?
        diff.div(d); // closer vehicles generate stronger desire to flee
        println("after div, diff = " + diff);
        // We'll need the average, so add this location to the sum
        // of all locations and increment the count.
        sum.add(diff);
        count++;
      }
    }


    // We have checked all vehicles and have a sum total of all the avoidance vectors
    if (count > 0) { // If zero then no one is aggresive
      sum.div(count); // sum is now our desired velocity
      sum.normalize();
      // Scale desired velocity to maxspeed
      sum.mult(maxspeed);

      // Apply Reynolds’s steering formula:
      // error is our current velocty minus our desired velocity
      PVector steer = PVector.sub(sum, velocity);
      println("I am " + serialNumber +  " sum = " + sum + " my v = " + velocity + " steer = " + steer);

      steer.limit(maxforce);

      // Apply the force to the Vehicle’s
      // acceleration.
      applyForce(steer);
    }
  }

  // Calculate a steering force to separate from other vehicles
  void separate (ArrayList<Vehicle> vehicles) {
    float desiredseparation = 200; // how close is too close.
    int count = 0;
    PVector sum = new PVector(0, 0);

    for (Vehicle other : vehicles) {

      // What is the distance between me and another Vehicle?
      float d = PVector.dist(location, other.location);

      // If the distance is zero we are looking at ourselves; exclude that
      if ((d > 0) && (d < desiredseparation)) {

        // calculate the location of this vehicle
        PVector diff = PVector.sub(location, other.location);
        diff.normalize();

        // We'll need the average, so add this location to the sum
        // of all locations and increment the count.
        sum.add(diff);
        count++;
      }
    } // end of loop over all vehicles

    // now calculate the average,
    // figure out the force
    // and apply the force:
    if (count > 0) { // If zero then no one is too close
      sum.div(count); // sum is now our desired velocity
      applyForce(applyLimits(sum));
    }
  }

  // Newton’s second law; we could divide by mass if we wanted.
  // If there are multiple forces (e.g. gravity, wind) we use
  // this function for each one, and it is added to the acceleration
  void applyForce(PVector force) {
    acceleration.add(force);
  }

  // Update the velocity and location, based on the acceleration generated by the steering force
  void update() {
    velocity.add(acceleration);
    velocity.limit(maxspeed);
    location.add(velocity);
    acceleration.mult(0); // clear the acceleration for the next frame
  }

  void display() {
    // Vehicle is a triangle pointing in
    // the direction of velocity; since it is drawn
    // pointing up, we rotate it an additional 90 degrees.
    float theta = velocity.heading() + PI/2;

    pushMatrix();
    translate(location.x, location.y);
    rotate(theta);

    // For debugging, print our serial number
    fill(0);
    text(serialNumber, 0, 0);

    if (isRed) {
      fill(255, 0, 0);
    } else {
      fill(175);
    }
    beginShape();
    vertex(0, -r*2);
    vertex(-r, r*2);
    vertex(r, r*2);
    endShape(CLOSE);

    popMatrix();
  }

  // Return the distance from the given location to this vehicle
  float distance(PVector l) {
    return PVector.sub(l, location).mag();
  }

  void inspect() {
    println("\nVehicle inspector:");
    println("SerialNumber: " + serialNumber );
    println("Location: " + location + " velocity = " + velocity + " acceleration = " + acceleration);
    println("Maximum steering force = " + maxforce + ", maximum speed = " + maxspeed);
  }
}
