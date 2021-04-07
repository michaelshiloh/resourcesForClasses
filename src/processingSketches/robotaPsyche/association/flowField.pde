// The flow field class, more or less straight from the book
// with the addition of the display() function 
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

    // Initialize the field 
    randomFlowField();
  }

  void randomFlowField() {
    for (int i = 0; i < cols; i++) {
      for (int j = 0; j < rows; j++) {
        field[i][j] = PVector.random2D(); // unit vectors
      }
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

  // Display the flow field so we can see if it looks like what we think it should
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
}
