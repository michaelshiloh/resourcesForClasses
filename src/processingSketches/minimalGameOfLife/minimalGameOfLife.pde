// Size of cells
int cellSize = 20;

// we don't want too many
float probabilityOfAliveAtStart = 15;

color alive = color(0, 200, 0);
color dead = color(0);

// Array of cells
int[][] cells; 

// We need to store a copy of the state of the cells 
// while calculating the next generation
int[][] copyOfCells; 

void setup() {
  size (1000, 800);

  // Make the arrays of cells 
  cells = new int[width/cellSize][height/cellSize];
  copyOfCells = new int[width/cellSize][height/cellSize];

  setupCells();

  stroke(48);     // stroke will draw the background grid
  background(0);  // Fill in black in case cells don't cover the entire canvas
  frameRate(1);   // very slow so we can see what's happening
}

void setupCells() {
  int liveCellCount = 0;
  for (int x=0; x<width/cellSize; x++) {
    for (int y=0; y<height/cellSize; y++) {
      float state = random (100);
      if (state > probabilityOfAliveAtStart) { 
        state = 0; // dead
      } else {
        state = 1; // alive
        liveCellCount++;
      }
      cells[x][y] = int(state); // Save state of each cell
    }
  }
  println("live cell count = " + liveCellCount);
}

void draw() {
  drawCells();
  nextGeneration();
}

void drawCells() {
  for (int x=0; x<width/cellSize; x++) {
    for (int y=0; y<height/cellSize; y++) {
      if (cells[x][y]==1) {
        fill(alive); // If alive
      } else {
        fill(dead); // If dead
      }

      // now stroke and fill are correct
      rect (x*cellSize, y*cellSize, cellSize, cellSize);
    }
  }
}

void nextGeneration() { 

  // Save a copy of the current generate  
  // while calculating the next generation
  // because the current generate will change
  // as we go along
  for (int x=0; x<width/cellSize; x++) {
    for (int y=0; y<height/cellSize; y++) {
      copyOfCells[x][y] = cells[x][y];
    }
  }

  // Visit each cell. x and y index into the active generation
  for (int x=0; x<width/cellSize; x++) {
    for (int y=0; y<height/cellSize; y++) {

      int aliveNeighbors = 0; 

      // Now visit the eight neighbors of each cell
      // and count how many are alive. 
      // Count neighbors in the copy of this generation
      // because the current generation will change as we go along 

      // xx and yy index into the copy of the generation
      for (int xx=x-1; xx<=x+1; xx++) { // neighbors on the sides
        for (int yy=y-1; yy<=y+1; yy++) {  // neighbors above and below

          // Make sure we are not out of bounds
          if ( ( (xx >= 0) && (xx < width / cellSize)) &&
            ( (yy >= 0) && (yy < height/cellSize))) { 

            // don't count ourselves
            if (!((xx==x)&&(yy==y))) { 

              // if the neighbor is alive
              if (copyOfCells[xx][yy]==1) {

                // count it
                aliveNeighbors ++;
              } // end of counting live neighbor
            } // End of not counting ourselves
          } // End of not out of bounds
        } // End of yy loop
      } //End of xx loop

      // We've checked the neigbours: apply rules!

      // If this cell is alive, and it has fewer
      // than two or more than 3 live neighbors, 
      // this cell dies
      if (copyOfCells[x][y]==1) { 
        if (aliveNeighbors < 2 || aliveNeighbors > 3) {
          cells[x][y] = 0; // Die unless it has 2 or 3 aliveNeighbors
        }
      } else { // end of this cell being alive

        // Otherwise (this cell is dead),
        // make it alive if it has exactly 3 live neighbors
        if (aliveNeighbors == 3 ) {
          cells[x][y] = 1; //
        } // end of exactly 3 neighbors
      } // End of this cell being dead
    } // End of y loop
  } // End of x loop
} // End of function
