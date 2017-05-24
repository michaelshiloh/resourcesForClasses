# Resources for Classes

## Basic Arduino Resources

1. Arduino basics: Intro through Lesson 3 of Adafruit's Arduino [tutorial](http://www.ladyada.net/learn/arduino/index.html)

1. [Arduino in a Nutshell](http://hci.rwth-aachen.de/arduino)

1. Another [Getting Started with
Arduino](http://reboot.yoha.co.uk/index.php?title=Getting_Started_with_Arduino)
	with links to many other sources of information

4. [Introduction](https://learn.sparkfun.com/tutorials/sik-experiment-guide-for-arduino---v32/introduction-sik-arduino-uno)
to the SparkFun Inventor's Kit for Arduino Experimenter's Guide

5. [Experiment 1: Blinking an LED](
https://learn.sparkfun.com/tutorials/sik-experiment-guide-for-arduino---v32/experiment-1-blinking-an-led)
in the SparkFun Inventor's Kit for Arduino Experimenter's Guide

6. [Experiment 2: Reading a
Potentiometer](https://learn.sparkfun.com/tutorials/sik-experiment-guide-for-arduino---v32/experiment-2-reading-a-potentiometer)
in the SparkFun Inventor's Kit for Arduino Experimenter's Guide

2. AnalogReadSerial [tutorial](http://arduino.cc/en/Tutorial/AnalogReadSerial)
by Arduino

3. Photoresistor
[Instructables](http://www.instructables.com/id/How-to-Use-a-Light-Dependent-Resistor-LDR/)

## Arduino Multitasking Resources

1. [Tutorial](https://www.arduino.cc/en/Tutorial/BlinkWithoutDelay)
to Blink Without Delay on the official Arduino website

1. Excellent Adafruit Multitasking
[Tutorial](https://learn.adafruit.com/multi-tasking-the-arduino-part-1?view=all)
(highly recommended)

2. A detailed
[explanation](https://programmingelectronics.com/tutorial-16-blink-an-led-without-using-the-delay-function-old-version/) of Blink Without Delay. I don't like the way he
does the circuit, but his explanation is good.

3. Very detailed line-by-line
[explanation](https://www.baldengineer.com/blink-without-delay-explained.html)
of Blink Without Delay, with links
to explanations of related concepts every step of the way.

## Arduino Tone Resources

1. Decent explanation
[here](https://programmingelectronics.com/an-easy-way-to-make-noise-with-arduino-using-tone/)

2. Using switches to control the tone
[here](http://arduino-tutorials.eu/creating-sounds-with-arduino-buzzer)

## Arduino Sensors Resources

1. Adafruit [guide](http://www.ladyada.net/learn/sensors/) to sensors


## Mechatronic Resources

1. Pages 272-281 in "Physical Computing: Sensing and Controlling the
Physical World with Computers" by Igoe/O'Sullivan, available in the
Hybrid Lab

1. "How to Build Automata" book, available in the Hybrid Lab

1. "How to Build Simple Automata" book, available in the Hybrid Lab

1. "Making Things Move" book, available in the Hybrid Lab 

1. [Machinations/Mechanisms](doc/machinations-mechanisms.pdf)

1. [Gear generator](http://www.geargenerator.com)

1. [Free plans](http://cabaret.co.uk/store/downloads/) from Cabaret Mechanical
Theatre

1. Instructables
[tagged](http://www.instructables.com/tag/type-id/keyword-automata/) with the
keyword Automata

1. Nice collection of resources for [Cam and Crank
toys](http://re.trotoys.com/projects/cat/cam-crank-toys/)

1. Simple [descriptions](http://www.mechanical-toys.com/mechanisums.htm) of
the 6 basic mechanisms

1. Cardboard Automata
[pamphlet](https://www.exploratorium.edu/pie/downloads/Cardboard_Automata.pdf)
from The Exploratorium

1. Free plans to download and other
[resources](http://dugnorth.com/automaton-plans.aspx) from Dug North, a master
automata builder

1. How to Make Cardboard Automata
[article](http://makezine.com/projects/make-cardboard-automata/) on Make:
Projects website (which itself is a great resource for all sorts of projects).

## Github Resources

1. How to create a Github account and your first repository
[guide](https://github.com/zamfi/github-guide)

2. How to upload a file to Github
	1. Click on "Upload files"
3. How to create a folder in Github

	Git doesn't store empty folders, so you can only create a new folder when
	you have a file to put in it. Also, you can't create a folder
	when you _upload_ a file. The only way to create a folder is 
	to create a _new_ file, and then to paste the contents of your file into 
	the new file:
	1. Go to the folder inside which you want to create another folder.
	2. Click on _Create new file_.
	3. On the text field for the file name, first write the folder name you
		 want to create, then type _/_ (which creates the new folder) and then
		 the name of the new file you want to create.
	4. Paste the contents of your file into the "new file"
	4. Optionally, add a short description and an extended description at
		the bottom of the page
	5. Finally, save your changes by pressing the green _Commit new file_
		button at the bottom of the page
4. How to delete a file
	1. Browse to the file in your repository that you want to delete.
	2. At the top of the file, click the icon of the trash can
	4. Add a short description of why you are deleting this file
	5. Finally, save your changes by pressing the green _Commit changes_
		button at the bottom of the page
4. How to [organize folders and files]
(https://github.com/blog/1436-moving-and-renaming-files-on-github) 
	in Github (move and rename)

5. There are many guides to Github Markdown. I find
[this](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet)
particularly useful.

## Making Sounds without Arduino
1. Basic 40106 (hex Schmitt trigger inverter)
		[oscillator](http://fluxmonkey.com/electronoize/40106Oscillator.htm)
2. Other 40106 [ideas](http://bleeplabs.com/rad-fi-analog/)

## Schematics
1. A great
[tutorial](https://learn.sparkfun.com/tutorials/how-to-read-a-schematic) on
schematics
2. There are many different symbols for MOSFETs depending on subtle
difference that we won't be concerned with. 

	I suggest that you use these symbols:

	![](http://www.electrotechservices.com/electronics/images/metal_oxide_semiconductor_fet_symbol.jpg)

	We have both N-channel and P-channel MOSFETs in the lab, but the ones that
	we use primarily (and the only ones I've discussed in class) are N-channel.

## Edge Detection 
1. Arduino [tutorial](https://www.arduino.cc/en/Tutorial/StateChangeDetection)

2. Adafruit 
	[tutorial](http://www.ladyada.net/learn/arduino/lesson5.html)

3. Another 
	[tutorial](https://programmingelectronics.com/tutorial-18-state-change-detection-and-the-modulo-operator-old-version/)

## Debouncing
- Arduino
	[tutorial](https://www.arduino.cc/en/tutorial/debounce)

## Debugging
1. Adafruit Digital Multimeter
[tutorial](https://learn.adafruit.com/multimeters?view=all)

1. Sparkfun Digital Multimeter
[tutorial](https://learn.sparkfun.com/tutorials/how-to-use-a-multimeter)

1. My debugging
[tutorial](http://teachmetomake.com/wordpress/debugging-circuits)

## Functions
1. Arduino function
[reference](https://www.arduino.cc/en/Reference/FunctionDeclaration)

1. User contributed Arduino function 
[tutorial](http://playground.arduino.cc/Code/Function)

1. Arduino function
[lesson](https://startingelectronics.org/software/arduino/learn-to-program-course/15-functions/)

## Arrays 
1. Arduino array [reference](https://www.arduino.cc/en/Reference/Array)

1. Arduino array [tutorial](https://www.arduino.cc/en/Tutorial/Arrays)

1. Another Arduino array
[tutorial](https://programmingelectronics.com/tutorial-13-how-to-use-arrays-with-arduino/)

1. Yet another Arduino array
[tutorial](https://www.tutorialspoint.com/arduino/arduino_arrays.htm)

1. Yet another Arduino array
	[tutorial](https://startingelectronics.org/software/arduino/learn-to-program-course/17-arrays/)

1. Yet another Arduino array [tutorial](http://www.thebox.myzen.co.uk/Tutorial/Arrays.html)

## Processing
1. [Hello Processing](http://hello.processing.org/)
tutorial

2. Processing [Getting Started](http://processing.org/tutorials/gettingstarted/)
tutorial

3. Processing [Coordinate System and Shapes](http://processing.org/tutorials/drawing/)
tutorial

4. Processing [Color](http://processing.org/tutorials/color/) tutorial

## Classes and Objects
1. Daniel Shiffman’s [Objects](https://processing.org/tutorials/objects/)
tutorial (Processing)

2. A simple Processing class
[example](http://teachmetomake.com/wordpress/simple-processing-class-example)

## Soldering
1. Adafruit 
[guide](https://learn.adafruit.com/adafruit-guide-excellent-soldering?view=all)
to excellent soldering

## Fritzing and Othermill
1. Download and install Fritzing from [fritzing.org](http://www.fritzing.org)

2. Fritzing’s [Getting Started](http://fritzing.org/learning/get-started/)

3. Getting started with Fritzing’s [Project
View](http://fritzing.org/learning/get-started/project-view/)

4. Fritzing Designing
PCB [tutorial](http://fritzing.org/learning/tutorials/designing-pcb/)

## Wireless Technologies
1. Wifi
	- Hard to use on some networks such as those that require logging in
		with credentials or those that prevent peer-to-peer communication

	1. Arduino [Yun](https://www.arduino.cc/en/Guide/ArduinoYunLin)

	1. Arduino [MKR1000](https://www.arduino.cc/en/Guide/MKR1000)

2. Bluetooth 
	- Reliable
	- Limited to vendor provided phone app unless you know how to write your
		own
	- __Don't solder the module to your project!__ 
		Add the appropriate header to mate with the module.
		
	1. Adafruit Bluefruit [tutorial](http://teachmetomake.com/wordpress/adafruit-bluefruit-arduino)

3. Xbee
	- Tricky to configure
	- Very reliable

	1. Sparkfun [tutorial](https://learn.sparkfun.com/tutorials/xbee-shield-hookup-guide)

4. 433 MHz
	- [Part](http://www.oddwires.com/433-mhz-transmitter-and-receiver-modules-great-for-arduino/)
	- [Library](http://www.airspayce.com/mikem/arduino/RadioHead/)
		(untested)

## Motors
1. Sparkfun Motors and Selecting the Right One
[tutorial](https://learn.sparkfun.com/tutorials/motors-and-selecting-the-right-one)

2. Adafruit [Arduino Lesson 13. DC
Motors](https://learn.adafruit.com/adafruit-arduino-lesson-13-dc-motors?view=all)

3. Adafruit [Arduino Lesson 14. Servo
Motors](https://learn.adafruit.com/adafruit-arduino-lesson-14-servo-motors/arduino-code-for-knob?view=all)

4. Adafruit [Arduino Lesson 15. DC Motor
Reversing](https://learn.adafruit.com/adafruit-arduino-lesson-15-dc-motor-reversing/arduino-code?view=all)

5. Adafruit [Arduino Lesson 16. Stepper
Motors](https://learn.adafruit.com/adafruit-arduino-lesson-16-stepper-motors/overview?view=all)

6. H-bridge
[tutorial](http://teachmetomake.com/wordpress/arduino-tutorial-h-bridge)
