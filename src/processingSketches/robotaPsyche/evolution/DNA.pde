class DNA {
  float radius;
  float initialMaxSteeringForce;
  float initialMaxSpeed;
  float initialEnergy;
  float metabolism;
  float deadAt;

  DNA (float r, float imsf, float ims, float ie, float metab, float dat) {
    radius = r;
    initialMaxSteeringForce = imsf;
    initialMaxSpeed = ims;
    initialEnergy = ie;
    metabolism = metab; // how much energy is consumed in each frame
    deadAt = dat; // if energy is lower than this vehicle dies
  }

  DNA getDNA() {

    // make a copy because this will be the DNA for the new vehicle
    DNA dna = new DNA(radius, initialMaxSteeringForce, initialMaxSpeed, initialEnergy, metabolism, deadAt);
    return dna;
  }

  // What should we do here?
  // Obviously could be entirely randome but alternatives exist
  // e.g. some regions on the canvas (hotspots?) or exposure to
  // specific vehicles might cause more severe mutations
  void mutate() {
  }

  void inspect() {
    println("DNA information:");
    println("\tRadius = " + radius);
    println("\tInitial Maximum Steering Force = " + initialMaxSteeringForce);
    println("\tInitial Maximum Speed = " + initialMaxSpeed);
    println("\tInitial Energy level = " + initialEnergy);
    println("\tMetabolism rate = " + metabolism);
    println("\tDead at energy level of " + deadAt);
    
    radius = 10; // just so I can see if I selected the right one
  }
}
