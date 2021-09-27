// Frame differencing with color
// Based on Code listing 1 from 
// Golan Levin's
// Computer vision for artists and designers

// Modified to be compatible with Processing 4.0b1

import processing.video.*;

// an array of pixels to store the previous frame
int previous_frame[];
int num_pixels;

Capture cam; // the capture device

void setup() {
  size(640, 480); // assuming our camera is this size

  String[] cameras = Capture.list();

  if (cameras.length == 0) {
    println("There are no cameras available for capture.");
    exit();
  } else {
    println("Available cameras:");
    for (int i = 0; i < cameras.length; i++) {
      println(cameras[i]);
    }

    // The camera can be initialized directly using an
    // element from the array returned by list(). Set the 
    // array index to the camera you wish to use
    cam = new Capture(this, cameras[0]);
    cam.start();

    // Now we can calculate how many pixels there are in a frame
    num_pixels = (cam.width * cam.height);

    // and now that we know the size, we can
    // allocate memory for storing the previous fram
    previous_frame = new int [num_pixels];

    // Now we initialize the previous frame to blank
    for (int i=0; i<num_pixels; i++) {
      previous_frame[i] = 0;
    }

    loadPixels();
  }
}

void draw() {
  if (cam.available()) {
    cam.read();

    int curr_color, prev_color;   // Declare variables to store a pixel's color.
    float curr_r, curr_g, curr_b; // Declare variables to hold current color values.
    float prev_r, prev_g, prev_b; // Declare variables to hold previous color values.
    float diff_r, diff_g, diff_b; // Declare variables to hold computed differences.
   
    for (int i=0; i<num_pixels; i++) { // For each pixel in the video frame,

      curr_color = cam.pixels[i]; // Fetch the current color in that location,
      prev_color = previous_frame[i]; // and also the previous color from that spot.

      // Extract the red, green, and blue components
      // from both the current and previous pixel color
      curr_r = red (curr_color);
      curr_g = green (curr_color);
      curr_b = blue (curr_color);
      prev_r = red (prev_color);
      prev_g = green (prev_color);
      prev_b = blue (prev_color);

      // And calculate the differences
      diff_r = abs (curr_r - prev_r); // Compute the difference of the red values.
      diff_g = abs (curr_g - prev_g); // Compute the difference of the green values.
      diff_b = abs (curr_b - prev_b); // Compute the difference of the blue values.

      pixels[i] = color(diff_r, diff_g, diff_b); // Render the difference image to the screen.

      // The current pixel information becomes the previous for the next frame
      previous_frame[i] = curr_color;
    }
    updatePixels(); // Write the pixels array to the canvas
  }
}
