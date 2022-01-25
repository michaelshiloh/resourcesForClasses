# Simple p5.js Class Example



Suppose you wanted a circle (or a ball) bouncing around in a box. You
might do something like
this:


````

/*
Step 1: A bouncing ball the old fashioned way
 */
let INITIALXSPEED = 4;
let INITIALYSPEED = 7;
let CIRCLESIZE = 15;
let ballx, bally, ballxSpeed, ballySpeed;

function setup() {
  createCanvas(400, 400);
  smooth();
  ballx = 10;
  bally = 50;
  ballxSpeed = INITIALXSPEED;
  ballySpeed = INITIALYSPEED;
}

function draw() {
  // Always erase the screen first
  background(0);

  // update the position of the circle
  ballx = ballx + ballxSpeed;
  bally = bally + ballySpeed;


  // check for collisions
  let r = CIRCLESIZE/2;
  if ( (ballx<r) || (ballx>width-r)) {
    ballxSpeed = -ballxSpeed;
  }
  if ( (bally<r) || (bally>height-r)) {
    ballySpeed = -ballySpeed;
  }
  // Finally draws the circle
  fill(255);
  ellipse(ballx, bally, CIRCLESIZE, CIRCLESIZE);
}

````

Copy this code into a new p5.js sketch and run it. Read the code and
understand what it’s doing.

Now suppose you wanted two balls, or 10, or 100. You’d have to copy all of
that again and again. After copying it 5 or 6 times you might ask yourself
if there isn’t a better way.

You might notice, for instance, that most of the code is exactly the same, 
it’s just dealing with a
different ball. Wouldn’t it be nice to
describe the ball behaviour once, and then have it automatically know how to
do that to all the balls?

There is a way, using classes and objects. This is called 
*object oriented programming* or *OOP*. Here is the same program using
OOP.

````

/*
 Step 2: Creating a class for a bouncing ball
 based on http://www.openprocessing.org/sketch/48960
 */

let XSPEED = 4;
let YSPEED = 7;
let CIRCLESIZE = 15;

// This is the definition of the MovingCircle class.
// Start with the name of the class:
class MovingCircle {

  // any variable declared here will be properties of
  // objects of this type
  //let x, y, xSpeed, ySpeed;

  // Now the functions that are part of this class:

  // This special function declaration has the same name
  // as the class (MovingCircle) and it has no return type. This
  // is known as the constructor and it's run every time a new
  // object of this type is created.
  constructor( xpos,  ypos) {
    this.x = xpos;
    this.y = ypos;
    this.xSpeed = XSPEED;
    this.ySpeed = YSPEED;
  }

  // Now come the functions (methods) of the class that
  // can be called. These functions describe what the
  // object can do:
  
  // The update() function adds the speed to the position, making
  // our circle move around:
   update() {
    this.x += this.xSpeed;
    this.y += this.ySpeed;
  }

  // The checkCollisions() function checks to see if our circle has gone off
  // the edge of the screen, and if so reverses the speed and hence the direction:
   checkCollisions() {
    let r = CIRCLESIZE/2;
    if ( (this.x<r) || (this.x>width-r)) {
      this.xSpeed = -this.xSpeed;
    }
    if ( (this.y<r) || (this.y>height-r)) {
      this.ySpeed = -this.ySpeed;
    }
  }
  // This function finally draws the circle
   drawCircle() {
    fill(255);
    ellipse(this.x, this.y, CIRCLESIZE, CIRCLESIZE);
  }
} // End of the MovingCircle class

// Now that we have defined the class (the cookie cutter)
// we can put it to use to make objects (the cookies):

// Make an object of type MovingCircle
// The two parameters are its initial position:
let myCircle = new MovingCircle(25, 72);

function setup() {
  createCanvas(400, 400);
  smooth();
}

function draw() {
  // Always erase the screen first
  background(0);
  // update the position of the circle
  myCircle.update();
  // check for collisions with the walls
  myCircle.checkCollisions();
  // and finally draw the circle
  myCircle.drawCircle();
}

````

If you want two balls, you don’t need to redefine the class, just create
more objects:

````

/*
 Simple Processing class example 
 Step 3: Creating two objects using the same class
 
 based on http://www.openprocessing.org/sketch/48960
 */
let XSPEED = 4;
let YSPEED = 7;
let CIRCLESIZE = 15;

let myCircle;
let myOtherCircle;

function setup() {
  createCanvas(400, 400);
  smooth();
  myCircle= new MovingCircle(50, 50);
  myOtherCircle= new MovingCircle(100, 100);
}

function draw() {
  // Always erase the screen first
  background(0);
  // update the position of the circle
  myCircle.update();
  myOtherCircle.update();
  // check for collisions with the walls
  myCircle.checkCollisions();
  myOtherCircle.checkCollisions();
  // and finally draw the circle
  myCircle.drawCircle();
  myOtherCircle.drawCircle();
}

// Copy the class definition from the previous step to 
// see for yourself that no changes are necessary for multiple 
// objects. (Once we have made our cookie cutter we can use
// it as many times as we want):

````

But that seems like the class didn’t really save us that much work. Why use
classes? Answer: it really
helps when you want to make lots of objects, and you use arrays instead of
individual names for each
object:

````

/*
 Step 4: Creating an array of objects using a class
 based on http://www.openprocessing.org/sketch/48960
 */

let XSPEED = 4;
let YSPEED = 7;
let CIRCLESIZE = 15;

// create an empty array for a bunch of objects
let myCircleArray = [];

// We'll make 10 objects
let QUANTITY = 100;

function setup() {
  createCanvas(400, 400);
  smooth(); 
  // Here is where we create the objects and populate the
  // array with them
  for (let i=0; i < QUANTITY ; i++) {
    // don't start at the edge or the ball will get stuck
    myCircleArray.push(new MovingCircle(random(CIRCLESIZE, width-CIRCLESIZE),
                           random(CIRCLESIZE, height-CIRCLESIZE)));
  }
}

function draw() {
  background(0);

  // iterate through every moving circle

  for (let i=0; i < myCircleArray.length; i++) {

    myCircleArray[i].update();
    myCircleArray[i].checkCollisions();

    myCircleArray[i].drawCircle();
  }
}


// Copy the class definition from the previous step to 
// see for yourself that no changes are necessary for multiple 
// objects. (Once we have made our cookie cutter we can use
// it as many times as we want):

````

You don't need to create all your objects at once. Once you have
the class, you can make objects any time you need.
For instance, you might add a new ball 
whenever you click a mouse button. 
