/* 
  
  // Avoid aggressive vehicles and notice if they are also red
  void avoidAggressive(ArrayList<Vehicle> vehicles) {
    final float tooClose = 25; // only pay attention to vehicles closer than this
    final float tooFast = 0.5; // faster than this is aggressive
    final float redIsAggressiveCertainty = 25; // if this many red vehicles are aggressive we associate

    // to accumilate all the individual avoidance vectors
    int count = 0; // how
    PVector sum = new PVector(0, 0);

    println();

    for (Vehicle other : vehicles) {

      // What is the distance between me and another Vehicle?
      float d = PVector.dist(location, other.location);

      // If the distance is zero we are looking at ourselves so skip over ourselves
      if (d == 0) {
        continue;
      }

      // println("I am " + serialNumber + " other is at distance = " + d );

      // If the distance is greater than tooClose skip this vehicle
      if (d > tooClose) {
        // println("skipping distant vehicle");
        continue;
      }

      // How fast is the other moving towards me?
      PVector otherVelocity = other.getVelocity();

      // Calculate project of velocity that is on the line directly towards me
      PVector lineTowardsMe = PVector.sub(location, other.location); //  vector pointing from other vehicle to me
      lineTowardsMe.normalize();
      // calculate projection
      PVector velocityTowardsMe = lineTowardsMe.mult(otherVelocity.dot(lineTowardsMe));

      float otherSpeed = velocityTowardsMe.mag(); // only interested in speed
      // no, this is wrong. if other is moving quickly but away from me I don't care.

      println("I am " + serialNumber + " other is at distance = " + d + " velocityTowardsMe = " + velocityTowardsMe);

      // Is vehicle close and aggressive?
      if (otherSpeed > tooFast) {
        println("I am " + serialNumber + " found an aggressive vehicle; avoidance vector = " + velocityTowardsMe);

        // Our avoidance velocity should be exactly the projection of the
        // other's velocity towards us.
        // We'll need the average, so add this velocity to the sum
        // of all avoidance velocities and increment the count.
        sum.add(velocityTowardsMe);
        count++;

        // also, if this aggressive vehicle is red,
        // increase the count of aggressive vehicles that are also red
        if ( other.getIsRed() ) {
          //  println(serialNumber + "this vehicle is aggressive and also red; making note");
          redVehiclesThatAreAlsoAggressive ++;
        }
      } else {
        // If this vehicle is not aggressive, but it is red,
        // and if we think that most red vehicles are red,
        // then avoid it!
        if (other.getIsRed() && (redVehiclesThatAreAlsoAggressive > redIsAggressiveCertainty)) {
          // println(serialNumber + "this vehicle is not acting aggresively but it is red, so avoiding it just to be safe");
          // calculate the location of this vehicle
          PVector diff = PVector.sub(location, other.location);
          diff.normalize();

          // We'll need the average, so add this location to the sum
          // of all locations and increment the count.
          sum.add(diff);
          count++;
        }
      }
    } // end of loop inspecting all vehicles

    // We have checked all vehicles and have a sum total of all the avoidance vectors
    if (count > 0) { // If zero then no one is aggresive
      sum.div(count); // sum is now our desired velocity

      // Scale desired velocity to maxspeed
      sum.setMag(maxspeed);

      // Apply Reynolds’s steering formula:
      // error is our current velocty minus our desired velocity
      PVector steer = PVector.sub(sum, velocity);
      steer.limit(maxforce);
      println("I am " + serialNumber + " resultant steering force = " + steer);

      // Apply the force to the Vehicle’s
      // acceleration.
      applyForce(steer);
    }
  }
  
  */
