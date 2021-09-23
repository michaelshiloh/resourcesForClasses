// An array of strings to hold the entire file
String strings[];

// For scaling, we want to know the minimum and maximum latitude and longitude
float minLat;
float maxLat;
float minLong;
float maxLong;

void setup() {
  size(500, 400);

  // The text from the file is loaded into an array.
  strings = loadStrings("/home/michael/Downloads/uswtdb_v4_1_20210721.csv");

  // Did we succeed to load anything?
  if (strings == null) {
    println("failed to load the file, stopping here");

    // this is an endless loop; it's a common way to prevent a program from continuing when something is wrong
    while (true) {
      ;
    }
  }

  println("strings loaded from file successfully, read " + strings.length + " lines");

  // Find the minimum and maximum latitude and longitude
  findMinMaxLatLong();
}

void findMinMaxLatLong() {
  String singleRow[];

  // loop over each row in the file
  for (int csvRowNumber=1; csvRowNumber<strings.length; csvRowNumber++) {

    // get a single row and split that row into individual words
    singleRow = split(strings[csvRowNumber], ',');

    // We know that the last two fields are the latitude and longitude and so they are numerical:
    float longitude = float(singleRow[25]);
    float latitude = float(singleRow[26]);

    // The file may be missing a field, in which case the converstion to a float might have failed
    if ( Float.isNaN(longitude) || Float.isNaN(latitude) ) {
      println("conversion to float failed; skipping row " + csvRowNumber);
    } else {

      if (csvRowNumber == 1) {
        minLat = latitude-10;
        maxLat = latitude+10;
        minLong = longitude-10;
        maxLong = longitude+10;
      }

      if (latitude < minLat) minLat = latitude;
      if (latitude > maxLat) maxLat = latitude;
      if (longitude < minLong) minLong = longitude;
      if (longitude > maxLong) maxLong = longitude;
    }
  } // end of for() loop

  print("Latitude (min, max) = (" + minLat + "," + maxLat + ") ");
  println("Longitude (min, max) = (" + minLong + "," + maxLong + ")");
} // end of findMinMaxLatLong

int csvRowNumber = 1;// Skip the first line, since we know it's a header

void draw() {
  String singleRow[];

  // get a single row and split that row into individual words
  singleRow = split(strings[csvRowNumber], ',');
  //println("Row " + csvRowNumber + " contains " + singleRow.length + " fields" );

  // We know that the last two fields are the latitude and longitude and so they are numerical:
  float longitude = float(singleRow[25]);
  float latitude = float(singleRow[26]);
  //println("Latitude " + latitude + " longitude " + longitude );

  if ( Float.isNaN(longitude) || Float.isNaN(latitude) ) {
    println("conversion to float failed; skipping row " + csvRowNumber);
  } else {

    // scale that to fit on our canvas
    //println(csvRowNumber);
    float ypos = map(latitude, minLat, maxLat, 0, height);
    float xpos = map(longitude, minLong, maxLong, 0, width);

    // Put a mark there
    point(xpos, ypos);
  }
  csvRowNumber++;
  if (csvRowNumber >= strings.length) {
    println("finished");
    noLoop();
  }
}
