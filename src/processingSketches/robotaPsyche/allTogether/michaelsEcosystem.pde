/*

 An environment wrapped in one big class
 
 Michael Shiloh
 
 Based on examples from The Nature of Code by Daniel Shiffman
 
 Change log:
 22 Mar 2022 - created
 
 This code is in the public domain
 */
class MichaelsEcosystem {
  
/**************************************************************************
 The flow field class, more or less straight from the book
 with the addition of the display() function and different
 initialization options (each of which is from the book)
 **************************************************************************/



  class FlowField {

    PVector[][] field;
    int cols, rows;
    int resolution; // Size of each square in the grid, in pixels

    // Constructor takes the desired resolution
    FlowField(int _res) {
      resolution = _res;
      cols = width/resolution;
      rows = height/resolution;

      // Declare the array of PVectors which will hold the field
      field = new PVector[cols][rows];

      // Initialize the field using one of the three options below
      // or make up your own initialization function
      // uniformFlowField();
      randomFlowField();
      // perlinFlowField();
      //followMouse();
    }

    // Pretty boring; all vectors point to the right
    void uniformFlowField() {
      for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
          field[i][j] = new PVector(1, 0); // pointing to the right
        }
      }
    }

    void randomFlowField() {
      for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
          field[i][j] = PVector.random2D();
        }
      }
    }

    void followMouse() {
      for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
          PVector pvMouse = new PVector(mouseX, mouseY);
          PVector pvCurrentLocation = new PVector(i*resolution, j*resolution);
          PVector meToMouse = PVector.sub(pvMouse, pvCurrentLocation);
          meToMouse.normalize();
          field[i][j] = meToMouse;
        }
      }
    }

    // Use perlin noise to determine the angle of each vector
    void perlinFlowField() {

      float xoff = 0.01;//random();
      for (int i = 0; i < cols; i++) {
        float yoff = 0.01; //random(30);
        for (int j = 0; j < rows; j++) {

          // Moving through the noise() space in two dimensions
          // and mapping the result to an angle between 0 and 360
          float theta = map(noise(xoff, yoff), 0, 1, 0, TWO_PI);

          // Convert the angle (polar coordinate) to Cartesian coordinates
          field[i][j] = new PVector(cos(theta), sin(theta));

          // Move to neighboring noise in Y axis
          yoff += 0.1;
        }

        // Move to neighboring noise in X axis
        xoff += 0.1;
      }
    }

    // Given a PVector which defines a location in the flow field,
    // return a copy of the value of the flow field at that location
    PVector lookup(PVector lookup) {

      // Convert x and y values to row and column, and constrain
      // to stay within the field
      int column = int(constrain(lookup.x/resolution, 0, cols-1));
      int row = int(constrain(lookup.y/resolution, 0, rows-1));

      return field[column][row].copy();
    }

    // Display the flow field
    // so we can see if it looks like what we think it should
    //
    void display() {
      for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
          // print("col " + i + " row " + j + "  ");
          // println(i*resolution, j*resolution, field[i][j].x, field[i][j].y);
          pushMatrix();

          // This translates to the top left corner of the grid, but really
          // it should center the vector in the middle of the grid
          translate(i*resolution, j*resolution);
          PVector f = field[i][j].copy();
          f.mult(resolution);
          line(0, 0, f.x, f.y);
          ellipse(f.x, f.y, 5, 5); // circle instead of arrow head
          popMatrix();
        }
      }
    }
  } // End of the FlowField class


  /**************************************************************************
   The vehicle class, more or less straight from the book
   **************************************************************************/

  class Vehicle {

    PVector location;
    PVector velocity;
    PVector acceleration;
    // Additional variable for size
    float r;
    float maxforce;
    float maxspeed;

    Vehicle(float x, float y) {
      acceleration = new PVector(0, 0);
      velocity = new PVector(0, 0);
      location = new PVector(x, y);
      r = 3.0;
      //Arbitrary values for maxspeed and
      // force; try varying these!
      maxspeed = 4;
      maxforce = 0.10;
    }

    // Update the velocity and location, based on the acceleration generated by the steering force
    void update() {
      velocity.add(acceleration);
      velocity.limit(maxspeed);
      location.add(velocity);
      acceleration.mult(0); // clear the acceleration for the next frame
    }

    // Newton’s second law; we could divide by mass if we wanted.
    // If there are multiple forces (e.g. gravity, wind) we use
    // this function for each one, and it is added to the acceleration
    void applyForce(PVector force) {
      acceleration.add(force);
    }

    /********************************************************
     What follow are different steering algorithms. A vehicle could
     use any one, and you are encouraged to create additional ones.
     Each algorithm calculates the steering force and then applies it
     *********************************************************/

    // Apply steering force to seek a target
    void seek(PVector target) {
      PVector desired = PVector.sub(target, location);
      desired.normalize();
      desired.mult(maxspeed);
      PVector steer = PVector.sub(desired, velocity);
      steer.limit(maxforce);
      applyForce(steer);
    }

    // Apply a steering force to follow a flow field
    void follow(FlowField flow) {

      // Look up the vector at that spot in the flow field
      PVector desired = flow.lookup(location);
      desired.mult(maxspeed);

      // Steering is desired minus velocity
      PVector steer = PVector.sub(desired, velocity);
      steer.limit(maxforce);
      applyForce(steer);
    }

    // Apply a steering force to maintain a bit of separation
    void separate (ArrayList<Vehicle> vehicles) {
      float desiredseparation = 20; // how close is too close.
      int count = 0;
      PVector sum = new PVector(0, 0);

      for (Vehicle other : vehicles) {

        // What is the distance between me and another Vehicle?
        float d = PVector.dist(location, other.location);

        // If the distance is zero we are looking at ourselves; exclude that
        if ((d > 0) && (d < desiredseparation)) {

          // calculate the location of this vehicle

          PVector diff = PVector.sub(location, other.location);

          // Alternately, don't normalize
          // in order to separate more from closer vehicles
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
      // but only if there is more than one force
      if (count > 0) { // If zero then no one is too close
        sum.div(count); // sum is now our desired velocity

        // Scale desired velocitysss to maxspeed
        sum.setMag(maxspeed);

        // Apply Reynolds’s steering formula:
        // error is our current velocty minus our desired velocity
        PVector steer = PVector.sub(sum, velocity);
        steer.limit(maxforce);

        // Apply the force to the Vehicle’s
        // acceleration.
        applyForce(steer);
      }
    }

    /********************************************************
     End of the different steering algorithms.
     *********************************************************/

    void display() {
      // Vehicle is a triangle pointing in
      // the direction of velocity; since it is drawn
      // pointing up, we rotate it an additional 90 degrees.
      float theta = velocity.heading() + PI/2;
      fill(175);
      stroke(0);
      pushMatrix();
      translate(location.x, location.y);
      rotate(theta);
      beginShape();
      vertex(0, -r*2);
      vertex(-r, r*2);
      vertex(r, r*2);
      endShape(CLOSE);
      popMatrix();
    }
  } // End of the Vehicle class

  /**************************************************************************
   Callback functions: What should we do on mouseClicks, keyPress,
   or other events
   **************************************************************************/

  // On a mouse click event, add a vehicle at the mouse location
  void mouseClicked() {
    vehicles.add(new Vehicle(mouseX, mouseY));
  }
  /**************************************************************************
   End of callback functions
   **************************************************************************/


  /**************************************************************************
   Finally we can make:
   - a flow field
   - some vehicles
   and see what happens
   **************************************************************************/

  FlowField f;
  ArrayList<Vehicle> vehicles = new ArrayList<Vehicle>();

  void setup() {
    
    f = new FlowField(15); // size of grid square in pixels

    // Make 100 vehicles to start with
    for (int i = 0; i < 100; i++) {
      vehicles.add(new Vehicle(random(width), random(height)));
    }
  }

  void draw() {
    
    // f.display(); // this really slows things down so use it only when you want

    for (Vehicle v : vehicles) {

      // Apply steering force
      v.separate(vehicles); // Try with and without this

      // Apply force to follow the flow field
      v.follow(f);

      // Update the velocity and location,
      // based on the acceleration generated any previous steering forces
      // This also empties the previous steering force for next time
      v.update();

      v.display(); // display the vehicle
    }
  }
}