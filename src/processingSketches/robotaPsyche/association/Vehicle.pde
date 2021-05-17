
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

    // 50% chance of being red
    if (round(random(1)) == 1) {
      isRed =  true;
    } else {
      isRed = false;
    }
  }

  // Return the distance from the given location to this vehicle
  float distanceTo(PVector l) {
    return PVector.sub(l, location).mag();
  }

  boolean offCanvas() {
    if (location.x > width) return true;
    if (location.y > height) return true;
    return false;
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
  // Avoiding things is many steps:
  // 1. Given an ArrayList of all vehicles, identify the ones that are to be avoided
  // 2. Accumilate avoidance vectors for those vehicles that are to be avoided
  // 3. Once all vehicles have been inspected, average the accumilated vectors
  // 4. Apply Reynolds’s steering formula with the resulting single vector
  void avoidAggressive(ArrayList<Vehicle> vehicles) {

    // to accumilate all the individual avoidance vectors
    int count = 0; // how
    PVector sum = new PVector(0, 0);

    // Now look at each vehicle and if it is aggressive calculate the desired vector to avoid it
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
        
        // Also, if it's red, add to the redVehiclesThatAreAlsoAggressive count
        if (other.getIsRed()) {
          redVehiclesThatAreAlsoAggressive++;
          println("I am " + serialNumber + " other is red, count is now = " + redVehiclesThatAreAlsoAggressive);
        }

        // Get the location of this vehicle relative to us
        PVector diff = PVector.sub(location, other.location); // in book, but  wrong way?

        println("I am " + serialNumber + " other is " + other.getSerialNumber() + " and is aggressive; will avoid; diff = " + diff);

        diff.normalize();
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
      applyForce(applyLimits(steer));
    }
  }

  /*
   TODO: Note that avoidRedVehicles() is almost exactly the same as avoidAggressive().
   Anytime that you have similar code that is duplicated, this is an opportunity
   for consolidation.
   
   Worse, anytime there is duplication, there is the risk that corrections are made in one,
   but not another. This is another reason to consolidate: it makes better code.
   
   My general principle is to always avoid having multiple source code, whether it's 
   a program, a document, or a function or variable within a program.
   */

  void avoidRedVehicles(ArrayList<Vehicle> vehicles) {
    // to accumilate all the individual avoidance vectors
    int count = 0; // how
    PVector sum = new PVector(0, 0);

    // 1. Given an ArrayList of all vehicles, identify the ones that are to be avoided

    // Now look at each vehicle and if it is red calculate the desired vector to avoid it
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

      // Is other vehicle red?
      boolean otherIsRed = other.getIsRed();


      // If so, avoid it, using the same logic as in separate
      if (otherIsRed) {

        println(); // so messages are separated

        // 2. Accumilate avoidance vectors for those vehicles that are to be avoided
        // Get the location of this vehicle relative to us
        PVector diff = PVector.sub(location, other.location); // in book, but  wrong way?

        println("I am " + serialNumber + " other is red; will avoid; diff = " + diff);

        diff.normalize();
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

      // 3. Once all vehicles have been inspected, average the accumilated vectors

      sum.div(count); // sum is now our desired velocity
      sum.normalize();
      // Scale desired velocity to maxspeed
      sum.mult(maxspeed);

      // 4. Apply Reynolds’s steering formula with the resulting single vector

      // Apply Reynolds’s steering formula:
      // error is our current velocty minus our desired velocity
      PVector steer = PVector.sub(sum, velocity);
      println("I am " + serialNumber +  " sum = " + sum + " my v = " + velocity + " steer = " + steer);

      steer.limit(maxforce);

      // Apply the force to the Vehicle’s
      // acceleration.
      applyForce(applyLimits(steer));
    }
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

  // Newton’s second law; we could divide by mass if we wanted.
  // If there are multiple forces (e.g. gravity, wind) we use
  // this function for each one, and it is added to the acceleration
  private void applyForce(PVector force) {
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

  // Methods used for debugging

  void inspect() {
    println("\nVehicle inspector:");
    println("SerialNumber: " + serialNumber );
    println("Location: " + location + " velocity = " + velocity + " acceleration = " + acceleration);
    println("Maximum steering force = " + maxforce + ", maximum speed = " + maxspeed);
  }

  void setLocation(PVector _location) {
    location = _location;
  }

  // Private methods used only member methods

  private boolean getIsRed() {
    return (isRed);
  }

  // Am I aggressive?
  private  boolean getIsAggressive() {
    float chance = random(100);

    if (isRed) {
      // If I am red, the threshold for aggression is 20 (i.e. 80% are aggressive)
      return (chance > 20);
    } else {
      // otherwise, the threshold is 80 (i.e. only 20% are aggressive)
      return(chance > 80);
    }
  }
  
  private int getSerialNumber() {
    return (serialNumber);
  }
}
