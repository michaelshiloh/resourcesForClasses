# resourcesForClasses

1. Basic Arduino Resources

	1. Arduino basics: Intro through Lesson 4 of Adafruit's Arduino [tutorial]
	(http://www.ladyada.net/learn/arduino/index.html)

	1. [Arduino in a Nutshell](http://hci.rwth-aachen.de/arduino)

	1. Another [Getting Started with
	Arduino](http://reboot.yoha.co.uk/index.php?title=Getting_Started_with_Arduino)
		with links to many other sources of information

	2. AnalogReadSerial [tutorial]
	(http://arduino.cc/en/Tutorial/AnalogReadSerial)
	by Arduino

	3. Photoresistor
	[Instructables](http://www.instructables.com/id/How-to-Use-a-Light-Dependent-Resistor-LDR/)

	4. [Introduction](https://learn.sparkfun.com/tutorials/sik-experiment-guide-for-arduino---v32/introduction-sik-arduino-uno)
	to the SparkFun Inventor's Kit for Arduino Experimenter's Guide

	5. [Experiment 1: Blinking an LED](
	https://learn.sparkfun.com/tutorials/sik-experiment-guide-for-arduino---v32/experiment-1-blinking-an-led)
	in the SparkFun Inventor's Kit for Arduino Experimenter's Guide

	6. [Experiment 2: Reading a
	Potentiometer](https://learn.sparkfun.com/tutorials/sik-experiment-guide-for-arduino---v32/experiment-2-reading-a-potentiometer)
	in the SparkFun Inventor's Kit for Arduino Experimenter's Guide

1. Arduino Multitasking Resources

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

1. Arduino Tone Resources

	1. Decent explanation
	[here](https://programmingelectronics.com/an-easy-way-to-make-noise-with-arduino-using-tone/)

	2. Using switches to control the tone
	[here](http://arduino-tutorials.eu/creating-sounds-with-arduino-buzzer)

1. Arduino Sensors Resources

	1. Adafruit [guide](http://www.ladyada.net/learn/sensors/) to sensors


2. Mechatronic Resources

	1. Pages 272-281 in "Physical Computing: Sensing and Controlling the
	Physical World with Computers" by Igoe/O'Sullivan, available in the
	Hybrid Lab

	1. "How to Build Automata" book, available in the Hybrid Lab

	1. "How to Build Simple Automata" book, available in the Hybrid Lab

	1. "Making Things Move" book, available in the Hybrid Lab 

	1. [Machinations/Mechanisms](doc/machinations-mechanisms.pdf)
	
	1. [Gear generator](http://www.geargenerator.com)

3. Github Resources

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

4. Making Sounds without Arduino
	1. Basic 40106 (hex Schmitt trigger inverter)
	    [oscillator](http://fluxmonkey.com/electronoize/40106Oscillator.htm)
	2. Other 40106 [ideas](http://bleeplabs.com/rad-fi-analog/)

5. Schematics
	1. A great
	[tutorial](https://learn.sparkfun.com/tutorials/how-to-read-a-schematic) on
	schematics
	2. There are many different symbols for MOSFETs depending on subtle
	difference that we won't be concerned with. 
	
	I suggest that you use these symbols:

	![](http://www.electrotechservices.com/electronics/images/metal_oxide_semiconductor_fet_symbol.jpg)

	We have both N-channel and P-channel MOSFETs in the lab, but the ones that
	we use primarily (and the only ones I've discussed in class) are N-channel.
