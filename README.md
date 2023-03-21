# General Resources for Classes

## Priorities (learned the hard way)

1. What is the minimum that you need to get done? Get that working first.
That way, if it's difficult you have more time to fix it, and if
it's impossible, you have more time to change your concept.  
1.1. If this is for a class, what's most of the grade?
1.1. If this is for yourself, what's the minimum you would need to feel proud?
1. In my experience, 
the mechanical things are the most difficult to get working, because usually
most students have the least amount of experience with this.
Get the mechanical parts work at least well enough before involving the
Arduino and programming.
1.1. If your robot is to be mobile, 
I would first get the mobility part working
1.1. If your robot has any other moving parts 
	(arms, tentacles, alien appendages, robot grippers) 
	I would try to get at least one of them working. 
1. The guiding principle is to do the things that you have the
least amount of experience with first And always leave the aesthetic stuff
until the very end. It doesn't matter if it looks like a jumble of junk, as
long as it works.  
1.1. One exception to the aesthetics is the wiring. As you've
probably discovered, a big mess of wires is very hard to debug, so spending
time to make the wires tidy can save you a lot of time later when things don't
work.

## Wisdom

1. MY GUIDING PRINCIPLES AFTER 20 YEARS OF PROGRAMMING
Medium
Alex Ewerlöf wrote an excellent article about his principles for working with software that I found could also apply to working on mechanical and electrical systems.

## Smoothing Readings from Noisy Sensors using Filters

1. Running average, built-in example in Arduino (File -> Examples -> Analog ->
Smoothing) [tutorial](https://www.arduino.cc/en/pmwiki.php?n=Tutorial/Smoothing)

1. [Another](https://maker.pro/arduino/tutorial/how-to-clean-up-noisy-sensor-data-with-a-moving-average-filter)
explanation of the running average filter

1. Great [discussion](https://www.megunolink.com/articles/coding/3-methods-filter-noisy-arduino-measurements/) and comparison
	of three smoothing methods: basic average, running average, and an
	exponential filter. The running average is the same as above. The
	exponential filter can be used by installing the *Megunolink* library
	(Sketch -> Include Library -> Manage Libraries, search for *Megunolink*) 

1. Many other filters are available through the library manager. I have not
	 tested these.

**Notes**
- While the examples above often refer to analog sensors, these methods
can be applied to all sensors (e.g. the ultrasonic distance measuring sensor)
- For beginners, I would recommend a basic average or a running average 
	- Basic average is faster to respond, but isn't quite as smooth as a running average.
	- In both cases, you will need to experiment with how many samples to take.  
		- A few samples responds quickly but won't be as smooth 
		- Many samples smooths well but won't respond quickly.  
	- You will have balance how much delay you can
tolerate vs. how smooth you need the result. Usually it's best to do this by
experimentation.

## Fabrication

1. Always design easy access for repair or modification. Never put items on
	 top of one another. Assume you will need easy access to each component.
	 Make access doors big so that you can easily put your hands in or bring
	 components out. Make holes for wires big enough that you can get the
	 connector through as well.
1. Make any enclosures at least twice as big as you think you'll need. Until
	 you're extremely experienced, you will underestimate how much room you'll
	 need and forget things like wires, which take up lots of space
1. Make wires longer than necessary, at least long enough that you can remove
	 a module and work on it comfortably (e.g. placing it face down on a
	 surface, not having to hold it at an uncomfortable angle)
1. Always use stranded wire between modules or between components and boards.
	 Solid wire can only be used when both ends are soldered to the same board.
1. Be consistent with colors: red for +5V (or whatever the dominant voltage
	 is), black wires for ground.
1. Don't have wires traverse empty space. Anchor wires to walls or other
	 support structures. Use zipties to bundle them neatly. 
1. Whenever possible, once you have finished the prototype transfer your
	 circuit from the solderless breadboard to a soldered board such as a
	 prototyping shield. Abolish all jumpers cables and instead solder
	 extensions as necessary. Use heat-shrink tubing on all solder joints to
	 prevent short circuits.


## Theory and critique
1. [Robotic Creatures](doc/roboticCreatures2010Ghedini.pdf)
1. [Catalog](doc/moma_catalogue_machine_art.pdf)
 from Machine Art exhibit, Museum of Modern Art, 1934 


## Inspiration: Artists, Movies, Projects, etc.

### Machine inspiration
- [DIY wire wrapping
- [Ghibli
	Clock](https://www.atlasobscura.com/places/the-giant-ghibli-clock-tokyo-japan)
	also [here](https://www.youtube.com/watch?v=R6nT8IEbaJM)
  machine](https://www.youtube.com/watch?v=3QL1QaIwMwk&t=482s)
- [Astronomical Clock Strasbourg
- [Fortnum & Mason store clock](https://www.youtube.com/watch?v=T7dWeTyexEg)
	Cathedral](https://www.youtube.com/watch?v=lKgZB3P45Kw)
- Series of 15 videos on [Mechanical
	Principles](https://www.youtube.com/watch?v=-42Z-_Kq0QU&list=PLq_UHnXWA4jI_gSAW9rvOr-I5Spqi3i_H)

1.  Drawing Machines
	1. [1](https://www.raspberrypi.org/blog/hanging-wall-plotter/)    
	1. [2](https://www.youtube.com/watch?v=T0jwdrgVBBc)    
	1. [3](http://www.homofaciens.de/technics-machines-v-plotter_en.htm)  
	1. [4](https://www.pinterest.com/pin/516014069788859472/)  
	1. [5](http://www.instructables.com/id/CNC-HANGING-PLOTTER/)  
	1. [6](http://patriciogonzalezvivo.com/2014/vPlotter/)  
	1. [7](http://www.instructables.com/id/Polargraph-Drawing-Machine/)  
	1. [8](https://www.thingiverse.com/thing:12557)  
	1. [9](https://www.thingiverse.com/thing:12403)  
	1. [10](http://makerblock.com/2013/03/a-study-of-drawing-robot-pen-holders-and-design-considerations/)  
	1. [11](https://www.kickstarter.com/projects/1765367532/duograph-drawing-machine?ref=nav_search)  
	1. [12](http://www.thisiscolossal.com/2016/03/cycloid-drawing-machine/)  
	1. The Machine As Artist, an
		 [Introduction](doc/theMachineAsArtistIntroduction.pdf)
  
1. Marble Machines
	1. [1](https://www.youtube.com/user/denha)  
	1. [2](https://tinkerlog.com/)  
	1. [3](https://www.youtube.com/watch?v=3OGyLHu24rk)

1. Didi Vardi's Wonderful Mechamisms
	1. [Binary Counter with old computer parts](media/binaryCounterDidiVardi.wmv)
	1. [Machine Animating late 19th century and early 20th century hand
		 tools](media/oldToolsMachineDidiVardi.wmv)

1. Musical Machines
	1. Carlos Guedes' wonderful [Phobos, Orquestra Robótica
	Disfuncional[(https://vimeo.com/235763130)
	4. Sudhu Tewari's [Yasmin Electro Mechanical 
	Sequencer](https://www.youtube.com/watch?v=MjNB3nKPMb8)
	1. Solenoid tapping wine glasses by [Lilliana Matta](https://vimeo.com/202356514) password
		 2424

1. List of [inspirational movies](http://eat.cca.edu) collected by [Barney
Haynes](http://www.ultrafuzz.net/) (also
[here](https://vimeo.com/barneyhaynes)) and shown at his Interface classes. In
particular

1. Inspirational videos collected by [J.D.
Zamfirescu](https://github.com/zamfi)  
	1.1. Basic robots  
		1.1.1. [Tree-climbing robot](http://www.youtube.com/watch?v=zkpH1BjD6Wc)  
		1.1.1. [Self-balancing robot](http://www.youtube.com/watch?v=Tw9Jr-SPL0Y)  
		1.1.1. [Insect robot](http://www.youtube.com/watch?v=tOsNXg2vAd4#t=120)  
		1.1.1. [Treadbot](http://www.youtube.com/watch?v=YblSltHDbIU)  
		1.1.1. [Velociraptor robot](http://www.youtube.com/watch?v=lPEg83vF_Tw)  
	1.1. Installations  
		1.1.1. [The Bay Lights](http://thebaylights.org/)  
		1.1.1. [Murmur Wall](http://www.future-cities-lab.net/projects/#/murmurwall/)  
		1.1.1. [Floating Couch](http://vimeo.com/72826106)  
		1.1.1. [Wooden Segment Mirror](https://www.youtube.com/watch?v=BZysu9QcceM#t=36)  
		1.1.1. [Generative design](https://www.youtube.com/watch?v=pNkz8wEJljc)  
	1.1. Art & Music bots  
		1.1.1. [Textile weaving](https://vimeo.com/71044541)  
		1.1.1. [ReacTable](https://www.youtube.com/user/marcosalonso)  
		1.1.1. [Projection mapping](https://www.youtube.com/watch?v=czuhNcNU6qU)  
		1.1.1. [Laser harp](http://www.youtube.com/watch?v=sLVXmsbVwUs#t=20)  
		1.1.1. [Cubli: Floating Cube](https://www.youtube.com/watch?v=n_6p-1J551Y)  
		1.1.1. [Arc-o-matic](http://vimeo.com/57082262#at=130)  
		1.1.1. [Robo Faber](http://vimeo.com/78771257)  
		1.1.1. [Eggbot](https://www.youtube.com/watch?v=w4cdbV2oaEc)  
	1.1. Drink-makers  
		1.1.1. [Textspresso](http://www.youtube.com/watch?v=kx9D74t7GD8#t=89)  
		1.1.1. [The Inebriator](http://www.youtube.com/watch?v=WqY7fchs7H0)  
	1.1. Computer Numerical Control (CNC)  
		1.1.1. [Shapoko / tinyg](http://www.youtube.com/watch?v=pCC1GXnYfFI#t=11)  
		1.1.1. [Makerbot Replicator](http://www.youtube.com/watch?v=NAbiAzYhTOQ)  
	1.1. Vacuuming  
		1.1.1. [Roomba](https://www.youtube.com/watch?v=0DNkbZvVYvc)  

2. [Golan Levin: Art that looks back at
you](https://www.youtube.com/watch?v=1G0MzlfMPuM)

3. [Drawdio](https://www.youtube.com/watch?v=PV_w38ldZaE)

4. Other Projects  
	1.1. Alex Markova's [fortune wheel](http://intro17fall.nyuad.im/2017/10/09/homework-due-october-9/)  
	1.1. Claire Neel's [reactive eye](https://youtu.be/lYERKTf5YtI)  
	1.1. Ji Young Kim's [map and national anthems](https://youtu.be/JknAOpjAkmQ  
	1.1. May Baho's [campfire](http://intro17fall.nyuad.im/wp-content/uploads/2017/12/IMG_2544.jpg)  

### Solderless Breadboards

1. [How to Use a Breadboard](https://learn.sparkfun.com/tutorials/how-to-use-a-breadboard) tutorial by Sparkfun
1. [Setting Up a Breadboard](https://itp.nyu.edu/physcomp/labs/labs-electronics/breadboard/) lab at NYU ITP

### Basic Electronics

1. [Basic Electronics](https://learn.sparkfun.com/tutorials/voltage-current-resistance-and-ohms-law) tutorial by Sparkfun
1. [Electricity: the Basics](https://itp.nyu.edu/physcomp/lessons/electronics/electricity-the-basics/) tutorial at NYU ITP

### Data Visualization Examples

1. [Ben Fry](http://benfry.com/allstreets/)

2. [Aaron Koblin](http://www.aaronkoblin.com/project/flight-patterns/)

3. Jer Thorp

	3.1. [Just
Landed](http://blog.blprnt.com/blog/blprnt/just-landed-processing-twitter-metacarta-hidden-data)

	3.2. [another](http://nytlabs.com/projects/cascade.html)

	3.3. [nytimes top coverage and
connections](https://www.flickr.com/photos/blprnt/sets/72157614008027965/with/3288898519/)

4. [Nicholas Feltron](http://feltron.com/FAR14.html)

### Mechanical or Primarily Mechanical

1. [Survival Research Labs](http://www.srl.org) Machine or industrial art

2. [Matt Heckert](http://www.mattheckert.com/)
Machine and kinetic art, machine sound art, and creator of many early SRL
machines

3. [Carl Pisaturo](http://carlpisaturo.com/index.html)
Artist, master machinist, and inventor, Carl documents his process in detail
for great learning opportunities. Great examples of complex motions via cables

4. [North Pitney](http://www.northpitney.com/)
North Pitney’s amazing [reconfigurable maze](http://www.northpitney.com/works/maze/maze.html) is one of my favorite examples of kinetic art.

5. Arthur Ganson
makes amazing sculptures using wire gears and mechanisms
[Making wire gears](http://www.youtube.com/watch?v=f0UNz-ayzrE)
Sample piece: [Meditation #1](http://www.youtube.com/watch?v=kY2Df78faiE)
Search youTube for many other videos of his work

6. Daniel Rozinin
[Wooden
mirror](http://www.designboom.com/weblog/read.php?CATEGORY_PK=&TOPIC_PK=2897) 
in which over 800 small blocks of wood
are individually rotated slightly to display an image of what the camera
captures

7. [Theo Jansen](http://www.strandbeest.com/)
Theo Jansen creates new forms of life using plastic tubing as the basic
building material. Wind is their "food", and their "stomach" is made of recycled
plastic bottles.
Theo’s [The art of creating
creatures](http://www.youtube.com/watch?v=b694exl_oZo) 
presentation at TED in 2006 includes
a wonderful video of his work and a live demonstration of portions of his
mechanisms. Search youTube for many other videos of his work

8. [Del’s Beautiful New Wooden
Machine](http://www.youtube.com/watch?v=u7ziwuIpnVY)
An intricate hand-cranked machine demonstrating many types of simple
mechanisms: cranks, gears, chains, sprockets, offset gears to change speed,
escapements, conversion of rotary motion to linear motion. Thanks to Tristan
for bringing this to my attention.

## Basic Arduino Resources from Arduino

1. Getting Started with Arduino / Genuino Uno
    [tutorial](https://www.arduino.cc/en/Guide/ArduinoUno)

1. Blink [tutorial](http://arduino.cc/en/Tutorial/Blink)

1. DigitalReadSerial [tutorial](http://arduino.cc/en/Tutorial/DigitalReadSerial)

1. AnalogReadSerial [tutorial](http://arduino.cc/en/Tutorial/AnalogReadSerial)

2. Fade [tutorial](http://arduino.cc/en/Tutorial/Fade)
shows how to use the `analogWrite()` function

## Basic Arduino Resources from Other Sources

1. Arduino basics: Intro through Lesson 3 of Adafruit's Arduino [tutorial](http://www.ladyada.net/learn/arduino/index.html)

1. [Arduino in a Nutshell](http://hci.rwth-aachen.de/arduino)

1. Photoresistor
[Instructables](http://www.instructables.com/id/How-to-Use-a-Light-Dependent-Resistor-LDR/)

## Sparkfun Inventor's Kit Resources

1. [Introduction](https://learn.sparkfun.com/tutorials/sik-experiment-guide-for-arduino---v32/introduction-sik-arduino-uno)
to the Sparkfun Inventor's Kit for Arduino Experimenter's Guide

1. [Experiment 1: Blinking an LED](
https://learn.sparkfun.com/tutorials/sik-experiment-guide-for-arduino---v32/experiment-1-blinking-an-led)
in the Sparkfun Inventor's Kit for Arduino Experimenter's Guide

1. [Experiment 2: Reading a
Potentiometer](https://learn.sparkfun.com/tutorials/sik-experiment-guide-for-arduino---v32/experiment-2-reading-a-potentiometer)
in the Sparkfun Inventor's Kit for Arduino Experimenter's Guide

## Blink Without Delay Resources

1. [Tutorial](https://www.arduino.cc/en/Tutorial/BlinkWithoutDelay)
to Blink Without Delay on the official Arduino website

1. [Another](https://www.baldengineer.com/millis-tutorial.html) 
explanation of Blink Without Delay recommended by a student

1. The same student recommends that in order to understand Blink Without
Delay, it is wise to first understand
[millis()](https://www.arduino.cc/en/Reference/Millis)

1. Very detailed line-by-line
[explanation](https://www.baldengineer.com/blink-without-delay-explained.html)
of Blink Without Delay, with links
to explanations of related concepts every step of the way.

2. A detailed
[explanation](https://programmingelectronics.com/tutorial-16-blink-an-led-without-using-the-delay-function-old-version/) of Blink Without Delay. 
I don't like the way he does the circuit, but his explanation is good.

## Arduino Multitasking Resources

1. Excellent Adafruit Multitasking
[Tutorial](https://learn.adafruit.com/multi-tasking-the-arduino-part-1?view=all)
(highly recommended)

1. Play a melody and blink an LED
without using `delay()`:
[toneMelodyAndBlinkWithoutDelay](https://github.com/michaelshiloh/toneMelodyAndBlinkWithoutDelay)

1. Flicker (i.e simulate a candle) multiple LEDs
without using `delay()`:
[flickerMultipleNoDelay](https://github.com/michaelshiloh/resourcesForClasses/blob/master/src/arduinoSketches/flickerMultipleNoDelay/flickerMultipleNoDelay.ino)


## State, state machines, and state change detection (edge detection)

1. [State Change Detection](https://www.arduino.cc/en/Tutorial/StateChangeDetection)

1. A formal State Machine is called a *Finite State Machine* (FSM). Although
	 you can often get away with being less formal, here is a nice
	 [tutorial](https://www.instructables.com/Finite-State-Machine-on-an-Arduino/)
	 on FSMs

2. Adafruit 
	[tutorial](http://www.ladyada.net/learn/arduino/lesson5.html)

3. Another 
	[edge detection tutorial](https://programmingelectronics.com/tutorial-18-state-change-detection-and-the-modulo-operator-old-version/)


## Arduino Tone Resources

1. Decent explanation
[here](https://programmingelectronics.com/an-easy-way-to-make-noise-with-arduino-using-tone/)

2. Using switches to control the tone
[here](http://arduino-tutorials.eu/creating-sounds-with-arduino-buzzer)

## Arduino Sensors Resources

1. Adafruit [guide](http://www.ladyada.net/learn/sensors/) to sensors


## Shift Register resources

1. Adafruit Shift Register
[tutorial](https://learn.adafruit.com/adafruit-arduino-lesson-4-eight-leds/the-74hc595-shift-register)

1. Arduino Shift Register
[tutorial](https://www.arduino.cc/en/Tutorial/ShiftOut)

2. Electronics Tutorials
Shift Register
[tutorial](https://www.electronics-tutorials.ws/sequential/seq_5.html)

1. Sparkfun 
Shift Register
[tutorial](https://learn.sparkfun.com/tutorials/shift-registers)


## Communication resources

#### Sparkfun Serial Communication tutorial
[here](https://learn.sparkfun.com/tutorials/serial-communication)


## Miscellaneous Electronic resources

1. Sparkfun 
Logic Level 
[tutorial](https://learn.sparkfun.com/tutorials/logic-levels)


## Mechatronic Resources

1. Simple [descriptions](http://www.mechanical-toys.com/mechanisums.htm) of
the 6 basic mechanisms

1. [Table of Mechanicks
	 [sic]](media/Table_of_Mechanicks_Cyclopaedia_Volume_2.jpg)

1. Great book describing how to build [Mechanisms](doc/machinations-mechanisms.pdf)

1. How to build a [Crank and
	 Slider](https://www.wikihow.com/Build-a-Crank-and-Slider-Mechanism) 
	 mechanism

1. [Gear generator](http://www.geargenerator.com)

1. Pages 272-281 in "Physical Computing: Sensing and Controlling the
Physical World with Computers" by Igoe/O'Sullivan

1. [How To Design And Make Automata](doc/howToDesignAndMakeAutomata_RobertAdams.pdf) by Robert Adams

1. [How To Design And Make Simple Automata](doc/howToDesignAndMakeSimpleAutomata_RobertAdams.pdf) by Robert Adams (I think this is a different version of the same book above)

1. Different shaped cams provide [different types of reciprocating motion](https://static.fratello.com/2021/08/camupdate1.gif)

1. A nice [overview](https://makezine.com/projects/make-your-own-gears/) of
making your own gears. Don't worry about the specifics (Inkscape etc.) 
but get the general concept which can be achieved in many different 
ways and using different tools.

1. Cardboard Automata
[pamphlet](https://www.exploratorium.edu/pie/downloads/Cardboard_Automata.pdf)
from The Exploratorium which has a clear diagram of how to use two cams to get
alternating rotation

1. "Making Things Move" by Dustyn Roberts

1. Very detailed [book](https://www.cs.cmu.edu/afs/cs/academic/class/15394h-f17/resources/cabaret_mechanical_movement.pdf) on making automata from Cabaret Mechanical Theatre

1. [Free plans](http://cabaret.co.uk/store/downloads/) from Cabaret Mechanical
Theatre

1. Instructables
[tagged](http://www.instructables.com/tag/type-id/keyword-automata/) with the
keyword Automata

1. Nice collection of resources for [Cam and Crank
toys](http://re.trotoys.com/projects/cat/cam-crank-toys/)

1. Free plans to download and other
[resources](http://dugnorth.com/automaton-plans.aspx) from Dug North, a master
automata builder

1. How to Make Cardboard Automata
[article](http://makezine.com/projects/make-cardboard-automata/) on Make:
Projects website (which itself is a great resource for all sorts of projects)

1. [Website](https://www.cs.cmu.edu/afs/cs/academic/class/15394h-f17/resources/mechanism-design.html|) for an Introduction to Mechanisms course at CMU with a ton of great material

1. Hackaday (articles on mechanisms)[https://hackaday.com/tag/mechanisms/). Very good.

1. [YouTube channel](https://www.youtube.com/user/thang010146/videos) illustrating a huge range of mechanisms, many of them quite unusual

1. [Twenty different
	 mechanisms](https://www.youtube.com/watch?v=M1-YeqGynlw&authuser=0) demonstrated using Lego

1. [THE SECRET LIFE OF
	 COMPONENTS](https://www.timhunkin.com/a241_component-videos.htm)
"A series of youtube guides for designers and makers" by Tim Hunkn. Of special
interest in this section of the resource guide are Chain, Hinges, Springs,
Glue, Bearings, Sensors, Linkages and Mechanisms, Motors, Screw Types, and
Prototypes. That's pretty much all of them except for LEDs, Switches, and
Connectors.

1. Not exactly a clock, but an interesting [article](https://www.inverse.com/article/17957-automata-clockwork-robots-artificial-intelligence-jessica-riskin)

1. [Article](https://www.nature.com/articles/d41586-018-05773-y) in Nature magazine about automata (crosses into robots too)

1. [Re-creation](https://www.youtube.com/watch?v=-wR6jAYgVPM) of the famous automata duck

1. CBS News on [Automaton](https://www.youtube.com/watch?v=C7oSFNKIlaM)

1. [Inspiration](https://twitter.com/GregoireSaunier/status/1512924636492800001)

1. [Jigsaw puzzle solving robot](https://www.youtube.com/watch?v=Gu_1S77XkiM) with lots of mechanisms

1.
	 [Interview](https://www.insider.com/realistic-animatronic-special-effects-for-movies-and-tv-2022-3)
	 with brilliant special effects designer at Industrial Light and Magic

1. Online version of a famous book series called [507 Mechanical
	 Movements](http://507movements.com/)

1. Another version of [507 Mechanical Movements](https://www.yeggi.com/q/507+mechanical+movements/)

1. [CAD designs](https://studiored.com/cad/114-of-the-507-mechanical-movement/) of the mechanisms in 507 Mechanical Movements

1. [I don't remember](https://www.red-salamander.com/manuals/)

1. [Making of a animatronic hand](https://makezine.com/article/maker-news/behind-the-scenes-with-the-animatronic-hand-from-netflixs-wednesday/) for promoting the Netflix series *Wednesday*

1. [Animated linkages](https://grabcad.com/library/bennett-linkage-animation-only-1)

1. A book on [Ingenious mechanisms](https://www.amazon.com/Ingenious-Mechanisms-Vol-Designers-Inventors/dp/0831110295/ref=sr_1_5)

1. [Mechanical Movement for Puppets and Automata](http://www.figuresinthefourthdimension.com/index.html) by Figures in the Fourth Dimension

1. A particularly nice [example](http://www.figuresinthefourthdimension.com/html/Spring.html) from Figures in the Fourth Dimension

1. A linkage [simulator](https://blog.rectorsquid.com/linkage-mechanism-designer-and-simulator/), to help you determine the lengths of the elements for
	 achieving particular movements

1. The House of Automata [Instagram account](https://instagram.com/thehouseofautomata)

1. [Bare walking mechanism](https://www.instagram.com/reel/CgpFhJdoJ--/?igshid=YmMyMTA2M2Y=) from the House of Automata

1. [Virtual sphere rolling joint](https://www.youtube.com/watch?v=tcDDDaSMW0I)

1. [20 Mechanical Principles combined in a Useless Lego Machine](https://youtu.be/M1-YeqGynlw). Nice depiction of each mechanism but I wish they were separate rather than all combined to make them easier to study

1. [Engineers Illustrated Thesaurus](https://archive.org/details/HerkhimerH.EngineersIllustratedThesaurus1952), a classic reference book

1. [Escapement mechanisms: Simple and fascinating](https://youtu.be/zBB4EUIOGM8)

================================================================================

## Github Resources

1. Please don't create documentation in PDF or Word format, as these are not
	 visible directly on Github. Use MarkDown (.md files) as described below.

1. How to create a Github account and your first repository
[guide](https://github.com/zamfi/github-guide)

	Your account name should be your name (unless for privacy reasons you'd prefer
	something else) and your repository name could be the course name. 

1. Help! I created my account and repository, but I can't find the button 
that says "Create new file" or "Upload files". How do I fix this?

	Answer: It sounds like you forgot to create a README.md file when you created the
	repository. See below.

2. Help! I created a new repository but I forgot to check the box that says
"Initialize this repository with a README". How can I create a README file?
	
	Answer: You can either:

	1. Delete your repository and create a new one, this time with the box
	checked.

	2.  Click where it says "README" and then click "Commit new file" at the 
	bottom of the page that comes up. This will create a "README" file.

2. How to upload a file to Github
	1. Click on "Upload files"

	![](media/githubUploadFiles.png)

3. How to create a folder in Github

	Git doesn't store empty folders, so you can only create a new folder when
	you have a file to put in it. Also, you can't create a folder
	when you _upload_ a file. The only way to create a folder is 
	to create a _new_ file, and then to tell Github to put that new file
	in a new folder:
	1. Go to the folder inside which you want to create another folder.
	2. Click on _Create new file_.
	3. On the text field for the file name, first write the folder name you
		 want to create, then type _/_ (which creates the new folder) and then
		 the name of the new file you want to create. The name doesn't matter.
	5. Finally, save your new file by pressing the green _Commit new file_
		button at the bottom of the page
	6. If you don't need the file, you may delete it now that the folder
		has been created.

4. How to delete a file
	1. Browse to the file in your repository that you want to delete.
	2. At the top of the file, click the icon of the trash can
	4. Add a short description of why you are deleting this file
	5. Finally, save your changes by pressing the green _Commit changes_
		button at the bottom of the page

4. How to upload a code file so that Github formats it as code

	Use the extension along with the file name. Github recognizes that .ino 
	are code files. Github recognizes many other file extensions as code.

4. How to [organize folders and files](https://github.com/blog/1436-moving-and-renaming-files-on-github) 
	in Github (move and rename)

5. How do I control the appearance of my README.md file?

	There are many guides to Github Markdown. I find
	[this](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet)
	particularly useful.

	Any file that has the .md extension will be interpreted by Github as a
	markdown file.
1. Github
	 [cheatsheet](https://education.github.com/git-cheat-sheet-education.pdf)
1. Git and Github [resources](https://garrulous-fragrance-04a.notion.site/GitHub-Resources-e2b1c4f44afd49dd86ddd0ada3eab99a) created by Thais Alvarenga 
1. [Version Control with Git](https://swcarpentry.github.io/git-novice/)
	lessons by [Software Carpentry](https://software-carpentry.org/)

1. How do I create code blocks within in a markdown (.md) file?

	You can create fenced code blocks by placing triple backticks ``` before and
	after the code block. We recommend placing a blank line before and after code
	blocks to make the raw formatting easier to read.

```
function test() {
  console.log("notice the blank line before this function?");
}
```

15. Git is best used from the command line. If you're using Mac OS or Linux
	 it's pre-installed. If you're using Windows download the tools from
	 [here](https://git-scm.com/download/win). You want the *64-bit Git for
	 Windows Setup* option. Installation is tricky but
	 [this](https://phoenixnap.com/kb/how-to-install-git-windows) should help.
	 Thanks to Chinonyerem for these!


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
	we use primarily (and the only ones I've discussed in class) are N-channel
	enhancement mode MOSFETs

## Debouncing
- Arduino
	[tutorial](https://www.arduino.cc/en/tutorial/debounce)

## Debugging
Students often assume that the problem is a bad component (including
	Arduino) or a problem in their computer. 
	While this is possible, 
	in my experience it is rarely the case. 
	The most likely cause is a mistake in
	your circuit and/or in your program. 
	Suspect those first.

#### Arduino upload or connection problems, or not finding the Arduino port
- Check in the tools menu that the correct serial port is selected
- Try uploading again. Sometimes the second or third time works
- Unplug the USB cable from your laptop and plug it in again. 
Check in the tools menu the serial port again (it might have been reassigned)
- Try a different USB port (if you have any)
- If you are using a USBC to USB-A adapter try a known good adapter, I have
	seen quite a few adapters simply not work with Arduino
- Disconnect your Arduino entirely from any circuit you have built. If this
	works it proves there is a problem in your circuit
- Shut down Arduino and restart
- Shut down your laptop and restart
- If none of the above helped, try a known good Arduino

#### Other problems
In the suggested sequence below, prioritize tests that are easy to do
- If your Arduino power LED (labeled **ON** on the Uno) does not light up:
	- The most likely cause is a short circuit in your circuit. Remove
		everything, verify that the LED now does come on, and rebuild your circuit
	- Sometimes the USB cable is bad. This is rare but does happen.

Things that are easy to check:

- Reminder: Including the servo library 
will disable `analogWrite()` (PWM) on pins 9 and 10, 
whether or not there is a servo on those pins.
- Reminder: Using the `tone()` function 
will disable `analogWrite()` (PWM) on pins 3 and 11.
- Check that you have a `pinMode(pin, OUTPUT)` for any pin you use as a
	digital output

Suggested debugging ~Sequence

1. Test each component in isolation, preferably with known good code, the
best being the built in-examples
1.1. If individual components don't work, remove everything else from your
circuit. Once you get that individual component working, add the rest one by
one, testing each time
1.1 For motor drivers, test the motor and battery in isolation by connecting
the motor directly to the battery
1. If the problem is intermittent, it is very likely caused by a loose
connection. Upload a program that tests that component continously, and
carefully wiggle each wire looking at the output. If the output starts
fluctuating, then you may be close to the intermittent connection

1. Clay Shirky's 4 part [video series](https://vimeo.com/channels/debugging) on debugging

#### Digital Multimeter (DMM) resources
1. Adafruit Digital Multimeter
[tutorial](https://learn.adafruit.com/multimeters?view=all)

1. Sparkfun Digital Multimeter
[tutorial](https://learn.sparkfun.com/tutorials/how-to-use-a-multimeter)

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

1. Processing [Getting Started](http://processing.org/tutorials/gettingstarted/)
tutorial

1. Processing [Coordinate System and Shapes](http://processing.org/tutorials/drawing/)
tutorial

1. Processing [Color](http://processing.org/tutorials/color/) tutorial

1. Daniel Shiffman's [Learning Processing video
	 tutorials](http://learningprocessing.com/videos/)

1. [Examples](http://learningprocessing.com/examples/)
from Daniel Shiffman's _Learning Processing_ book (also available on
[Github](https://github.com/shiffman/LearningProcessing)

1. [Examples](https://github.com/nature-of-code/noc-examples-processing)
from Daniel Shiffman's _The Nature of Code_ book

1. [Getting Started with
	 Processing](media/getting_started_with_processing.pdf) book

1. [Pictures made with Processing](https://www.behance.net/manoloide) 
and [the code](https://github.com/manoloide/AllSketchs) that made them

1.
[NullPointerException](https://forum.processing.org/two/discussion/8071/why-do-i-get-a-nullpointerexception)

1. Processing [Cheat Sheet](doc/processing_cheat_sheet_english.pdf), thanks to
	 [openlab.surattack,com](openlab.surattack,com)

## Classes and Objects
1. Daniel Shiffman’s [written tutorial](https://processing.org/tutorials/objects/)
tutorial on objects in Processing

1. Daniel Shiffman's [video
	 tutorial](https://www.youtube.com/watch?v=lmgcMPRa1qw) on objects in
	 Processing

2. A simple Processing class
[example](https://github.com/michaelshiloh/simpleProcessingClassExample)

3. "[Arduino the Object Oriented
way](https://paulmurraycbr.github.io/ArduinoTheOOWay.html)" tutorial

## Soldering
1. Adafruit 
[guide](https://learn.adafruit.com/adafruit-guide-excellent-soldering?view=all)
to excellent soldering

2. Sparkfun Through Hole Soldering
[tutorial](https://learn.sparkfun.com/tutorials/how-to-solder-through-hole-soldering)

1. Best close up I've ever seen on how to solder pins into a circuit board.
	 It's between 0:17 and 0:28 of [this](https://tinusaur.com/demo/) video

## Solderless Breadboard Resources
1. Sparkfun's [How to Use a
    Breadboard](https://learn.sparkfun.com/tutorials/how-to-use-a-breadboard)
    tutorial.

2. Adafruit's [Breadboards for
    Beginners](https://learn.adafruit.com/breadboards-for-beginners?view=all)
    tutorial

## Fritzing Resources
1. Download and install Fritzing from [fritzing.org](http://www.fritzing.org)

2. Fritzing’s [Getting Started](http://fritzing.org/learning/get-started/)

3. Getting started with Fritzing’s [Project
View](http://fritzing.org/learning/get-started/project-view/)

4. Fritzing Designing
PCB [tutorial](http://fritzing.org/learning/tutorials/designing-pcb/)

5. My [repository](https://github.com/michaelshiloh/Fritzing)
of assorted Fritzing projects

## Othermill/Bantam Tools Printer Circuit Board mill
1. Getting Started
		[project](https://support.bantamtools.com/hc/en-us/articles/115003204926-Bantam-Tools-PCB-Badge)

## Wireless Resources
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
		
	1. Adafruit Bluefruit and Adafruit Motor Shield
	[tutorial](https://github.com/michaelshiloh/motorShieldAndBluefruit)

3. Xbee
	- Tricky to configure
	- Very reliable

	1. Sparkfun [tutorial](https://learn.sparkfun.com/tutorials/xbee-shield-hookup-guide)

4. 433 MHz
	- [Part](http://www.oddwires.com/433-mhz-transmitter-and-receiver-modules-great-for-arduino/)
	- [Library](http://www.airspayce.com/mikem/arduino/RadioHead/)
		(untested)

## Motors Resources
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

7. Adafruit [Motor Shield
	 Tutorial](https://learn.adafruit.com/adafruit-motor-shield-v2-for-arduino?view=all)

## Transistor Resources

1. Quite decent MOSFET
[tutorial](http://www.radio-electronics.com/info/data/semicond/fet-field-effect-transistor/mosfet-basics-tutorial.php)

1. Quite good MOSFET [tutorial and usage
guide](https://oscarliang.com/how-to-use-mosfet-beginner-tutorial/)

## Wordpress Resources

1. Creating your first post as a Wordpress author

	1. Visit your blog's administratoin page at blogname/wp-admin e.g.  [http://intro18fall.nyuad.im/wp-admin](http://intro18fall.nyuad.im/wp-admin). Enter the user name and password that you have been given.

	1. In the left hand toolbar hover over "Posts" and select "Create New"

	1. Give a title to your first post, such as "Introducing Myself"

	1. Write the text of your post in the large box below. You might use this opportunity to experiment with some of the formatting options. You can edit your post now as well as later.

	1. When you are satisfied with your post click "Publish"

	1. It is always wise to make sure you post published correctly and appears how you want it. Hover over the blog name (near the home symbol near the upper left corner) and select "visit site". 

	1. If you are not happy with your post you can click in "Edit" and make further changes.

1. [Comparison of User Roles](https://www.wpbeginner.com/beginners-guide/wordpress-user-roles-and-permissions/?display=wide)

1. Rather than upload a video to a Wordpress blog, it 
is better to upload video to Vimeo or
Youtube and to embed those in your post. [Here](http://www.wpbeginner.com/beginners-guide/how-to-easily-embed-videos-in-wordpress-blog-posts/) are instructions.

## Laser Cutting Resources

1. Laser cut boxes [Gallery of Ideas](doc/LasercutBoxGalleryOfIdeas.pdf)

1. Laser Cut Like a Boss [lecture](doc/LaserCutLikeaBoss.pdf)

1. Laser cut T-Slot [picture](doc/laserCutTSlot.pdf)

1. Laser Cut box [notes](doc/LaserCutBoxNotes.pdf)

1. Detailed [instructions](https://www.wikihow.com/Glue-Acrylic) for gluing acrylic

1. General tips for [Working with

1. CNC panel joinery
	 [ideas](https://makezine.com/2012/04/13/cnc-panel-joinery-notebook/)
acrylic](https://makezine.com/2015/10/29/skill-builder-acrylic/)

## Fusion 360 Tutorials

1. Excellent series by [Kevin Kennedy](https://www.youtube.com/watch?v=sZwM87-nsYA&list=PLrZ2zKOtC_-DR2ZkMaK3YthYLErPxCnT-&index=2&t=0s)
1. Excellent series by [NYCCNC]()
1. Joint tutorial by[NYC CNC](https://www.youtube.com/watch?v=C03H_YZHuAI)
1. Joint tutorial by [Jason Workshop](https://www.youtube.com/watch?v=QisfRW0pd44)
1. Another joint tutorial by[NYC CNC](https://www.youtube.com/watch?v=Bw08O6XsfDI)
1. Joint tutorial by [Autodesk](https://www.youtube.com/watch?v=nngmNos6VI4)
1. [HOW and WHY to Fully Constrain Your
	 Sketches](https://www.youtube.com/watch?v=C11L136U0vQ&list=PLrZ2zKOtC_-DR2ZkMaK3YthYLErPxCnT-&index=19)

## Free CAD models

1. [McMaster-Carr](https://mcmaster.com)
1. [Onshape](https://onshape.com)
1. [Traceparts](https://info.traceparts.com/use-and-manage-3d-cad-models/download-free-cad-models/)
1. [Grabcad](https://grabcad.com/library)


## CAD Resources

1. Free cloud based simple 2D CAD software [Vectr](vectr.com). Somewhat
limited but easy to learn quickly from built-in tutorials.

2. Free Open Source 2D CAD software [inkscape](inkscape.org). Runs on Linux,
MacOS, and Windows.


## Creativity resources

1. [Kermit the Frog at TEDx](https://www.youtube.com/watch?v=zX7vQ2QB6Eo)

## CNC supply resources (stores)

1. [Inventables](https://www.inventables.com/categories/machine-components)

1. [Adafruit](https://www.adafruit.com/category/122)

1. [Servo City](https://www.servocity.com/motion-components)


## Daniel Shiffman Videos

1. Youtube [channel](https://www.youtube.com/user/shiffman/videos)

1. Image and Pixels
	 [tutorials](https://www.youtube.com/playlist?list=PLRqwX-V7Uu6YB9x6f23CBftiyx0u_5sO9)

1. Computer Vision
	 tutorials](https://www.youtube.com/playlist?list=PLRqwX-V7Uu6aG2RJHErXKSWFDXU4qo_ro)

1. [11.4: Introduction to Computer Vision - Processing Tutorial](https://www.youtube.com/watch?v=h8tk0hmWB44&amp;list=PLRqwX-V7Uu6aG2RJHErXKSWFDXU4qo_ro&amp;index=2&amp;t=0s)

1. [11.5: Computer Vision: Color Tracking - Processing Tutorial](https://www.youtube.com/watch?v=nCVZHROb_dE&amp;list=PLRqwX-V7Uu6aG2RJHErXKSWFDXU4qo_ro&amp;index=2)

1. [11.6: Computer Vision: Motion Detection - Processing Tutorial](https://www.youtube.com/watch?v=QLHMtE5XsMs&amp;list=PLRqwX-V7Uu6aG2RJHErXKSWFDXU4qo_ro&amp;index=3)

1. [11.7: Computer Vision: Blob Detection - Processing Tutorial](https://www.youtube.com/watch?v=ce-2l2wRqO8&amp;list=PLRqwX-V7Uu6aG2RJHErXKSWFDXU4qo_ro&amp;index=4)

1. [11.8: Computer Vision: Improved Blob Detection - Processing Tutorial](https://www.youtube.com/watch?v=1scFcY-xMrI&amp;list=PLRqwX-V7Uu6aG2RJHErXKSWFDXU4qo_ro&amp;index=5)

1. [11.9: Computer Vision: Blob Tracking with Persistence - Processing Tutorial](https://www.youtube.com/watch?v=r0lvsMPGEoY&amp;list=PLRqwX-V7Uu6aG2RJHErXKSWFDXU4qo_ro&amp;index=6)

1. [11.10: Computer Vision: Adding Lifespan to Blobs - Processing Tutorial](https://www.youtube.com/watch?v=o1Ob28sF0N8&amp;list=PLRqwX-V7Uu6aG2RJHErXKSWFDXU4qo_ro&amp;index=7)


## How to ask for help, whether from your classmates, professors, or online

The general principles are these:
1. Make it easy to understand what you are doing with clear documentation
	 (well organized schematic or code, good comments etc.)
1. Clearly explain what you think should be happening, and what is happening
	 instead
1. Show that you have seriously tried to solve your problem

More specifically:
1. First, clean up your code, insert meaningful comments, remove unnecessary
	 code, remove unused code that is commented out, indent your code properly,
	 etc. If your code is very long, organize it into functions to make it
	 easier to read. Use meaningful names for functions, variables, and classes.
	 Someone should be able to read your code and understand what it is doing
	 without you having to explain.

1. Explain briefly the overall goal, but don't confuse with unnecessary
	 details. 

1. Show that you have exhausted all reasonable attempts to solve this on your
	 own. Provide links to reference pages, tutorials, examples, etc. that you
	 used to develop and in your attempt to debug your project. Provide
	 summaries of any relevant Google searches, or discussions that you found on
	 forums. 

1. Explain very clearly the precise steps required to reproduce the problem.
	 Test these instructions yourself before you submit the question. 

1. Describe the attempted solutions you already tried, and what the results
	 were. Again, be specific and clear. Give the reason you thought these
	 attempts might work

1. Share error messages, screenshots of the failure, etc. Provide as much
	 information as possible.

1. If your project involves a circuit, share clear photo(s) of your wiring so
	 people can see if you made a mistake.


## Critical Making

1. [The Role of Critical
	 Making](https://waag.org/en/article/role-critical-making)

1. [Critical Making by Matt
	 Ratto](http://opendesignnow.org/index.html%3Fp=434.html)

1. From Ratto's paper above:
Benkler, Y, ‘Freedom in the Commons: Towards a Political Economy of Information’, Duke Law Journal, 52(6), 2003, p. 1245–1277. 
Agre, P, ‘Toward a Critical Technical Practice: Lessons Learned in Trying to Reform AI’, in Bowker, G, Gasser, L, Star, L and Turner, B, eds, Bridging the Great Divide: Social Science, Technical Systems, and Cooperative Work. Erlbaum, 1997. Dourish, P, Finlay, J, Sengers, P, & Wright, P, ‘Reflective HCI: Towards a critical technical practice’, in CHI’04 extended abstracts on Human factors in computing systems, 2004, p. 1727–1728. 
Friedman, B, ‘Value-sensitive design’, interactions, 3(6), p.16-23. DOI:10.1145/242485.242493. 
Flanagan, M, Howe, D, & Nissenbaum, H, Embodying Values in Technology: Theory and Practice. 2005 (draft). 
Dunne, A, & Raby, F, Design Noir: The Secret Life of Electronic Objects. Birkhäuser Basel, 2001. 
Papert, S, Mindstorms: Children, Computers, and Powerful Ideas (2nd ed.). Basic Books, 1993. 
Law, J, After method: mess in social science research. Routledge, 2004. 
Haraway, D, Simians, Cyborgs, and Women: The Reinvention of Nature (1st ed.). Routledge, 1990. Hayles, N, ‘The Materiality of Informatics’, Configurations, 1(1), 1993, p. 147-170. Hayles, N, How we became posthuman: virtual bodies in cybernetics, literature, and informatics. University of Chicago Press, 1999. Kirschenbaum, M, Mechanisms: New Media and the Forensic Imagination. The MIT Press, 2008. 
Lamberty, K, ‘Designing, playing, and learning: sustaining student engagement with a constructionist design tool for craft and math’, in Proceedings of the 6th international conference on Learning sciences, 2004, p. 652.
Lamberty, K, ‘Creating mathematical artifacts: extending children’s engagement with math beyond the classroom’, in Proceedings of the 7th international conference on Interaction design and children, 2008 p. 226–233. 
Ratto, M, ‘Critical Making: conceptual and material studies in technology and social life’, paper for Hybrid Design Practice workshop, Ubicomp 2009, Orlando, Florida. 
Lewin, K, ‘Action research and minority problems’, J Soc. Issues 2(4), 1946, p. 34-46. Argyris, C, Putnam, R, & Smith, D, Action Science: Concepts, methods and skills for research and intervention. San Francisco: Jossey-Bass, 1985. 
Gaver, B, Dunne, T, & Pacenti, E, ‘Design: Cultural probes’, interactions, 6(1), p. 21-29. DOI:10.1145/291224.291235. 
Ratto, M, Hockema, S, ‘Flwr Pwr: Tending the Walled Garden’, in Dekker, A & Wolfsberger A (eds) Walled Garden, Virtueel Platform, The Netherlands, 2009.Ratto, op.cit. 
Latour, B, ‘A Cautious Prometheus? A Few Steps toward a Philosophy of Design’, Keynote lecture for the Networks of Design, meeting of the Design History Society, Falmouth, Cornwall, 3rd September 2008. 

1. Garnet hertz's zine "critical making" (need to upload)

1. Critical Making [website](http://criticalmaking.nl/) in Holland

## Open Source Theory

1. [The Cathedral and the
	 Bazaar](https://www.semanticscholar.org/paper/The-cathedral-and-the-bazaar-musings-on-Linux-and-Raymond/905ca73f18b2571c1c3fde12f6dd18dd0c735a41)

1. [Open Source Model](https://en.wikipedia.org/wiki/Open-source_model)

1. [Why Open Source Misses the Point of Free
	 Software](https://www.gnu.org/philosophy/open-source-misses-the-point.en.html)

# General Resources about Robots

1. [INTRODUCTION TO AUTONOMOUS ROBOTS](github)
Introduction to Autonomous Robots is an open-access book by Nikolaus Correll, Bradley Hayes, Christoffer Heckman, and Alessandro Roncone. The book focuses on mechanisms, sensors, actuators, and algorithms.

1. ELEMENTS OF ROBOTICS
Springer
Published in 2018, Elements of Robotics is an open-access textbook by Mordechai Ben-Ari and Francesco Mondada. The book covers sensors, robot motion, state machines, control, navigation, localization, machine learning, and more.

1. [FOUNDATIONS OF ROBOTICS](foundations-of-robotics.org)
This open-access book by Damith Herath and David St-Onge is an introductory text providing a high-level overview of many aspects of robotics.

1. INTRODUCTION TO ROBOTICS
Princeton
Anirudha Majumdar teaches this course at Princeton University. The course covers feedback control, motion planning, state estimation, and computer vision and uses a Crazyflie quadrotor throughout the course. On the above page, you will find all course materials.

1. [ROBOTICS 501: MATHEMATICS FOR ROBOTICS](GitHub)
“ROB 501: Mathematics for Robotics is a graduate-level course at the University of Michigan that introduces applied mathematics for robotics engineers.
Topics include vector spaces, orthogonal bases, projection theorem, least squares, matrix factorizations, Kalman filter and underlying probabilistic concepts, norms, convergent sequences, contraction mappings, Newton Raphson algorithm, local vs. global convergence in nonlinear optimization, convexity, linear and quadratic programs”.


# Resources for Interactive Media

1. [The playful wonderland behind great
	 inventions](https://www.ted.com/talks/steven_johnson_the_playful_wonderland_behind_great_inventions?language=en)

1. [Where good ideas come
	 from](https://www.ted.com/talks/steven_johnson_where_good_ideas_come_from?language=en)

# Resources for Performing Robots

## New material

1. [Art ex machina](https://wired.me/technology/artificial-intelligence/art-ex-machina/) article in Wired about AI in art, featuring Merritt
	 Moore dancing with robots
1. [Guy Hoffman](http://guyhoffman.com/category/research/robots/)

1. [Noga Erez](https://www.youtube.com/watch?v=Xn813NKlhzI)

1. Amit Dror [Monkeys](https://amitdrori.com/monkeys/)

1. [Slides](doc/2020.09.30-CompositionAndDramaturgy.pdf) from Tegan's
	 guest lecture on September 30 2020

## Robot actors and theatre companies using robots

1. [Ullanta Performance Robotics](http://www.ullanta.com/ullanta/) is a
theater troupe in which the actors are autonomous robots. 

1. Robots and Human Actors Take Bows Together
([NYTimes](http://www.nytimes.com/2012/07/08/theater/robot-and-human-actors-take-bows-together.html))

1. **Oriza Hirata's Robot Theatre**: Oriza Hirata is a playwright and director who produced some important and
moving plays employing both human and robotic actors. In addition to plays he
has written, Hirata has also created android versions of Kenji Miyazawa’s
Night on the Galactic Railroad (2013),Franz Kafka’s The Metamorphosis (2014),
the Hamburg State Opera’s Stilles Meer (Silent Sea, 2016), and Chekhov’s
Three Sisters (2012).

	1.  [Article](https://thetheatretimes.com/the-gaze-of-the-robot/) about Hirata's
Robot Theatre in Theatre Times  
	1.  [Video Article](https://www.youtube.com/watch?v=DllPedBqjjw) about The
Metamorphosis  
	1.  [Article](https://muse.jhu.edu/article/522851) about I, Worker and Sayonara  
	1.  [Publicity video](https://www.youtube.com/watch?v=Uo-4RQPEHIk) for a showing
	of I, Worker and Sayonara
	1.  Two of Hirata's plays (I, Worker and Sayonara) can be found in [this](https://drive.google.com/drive/u/0/folders/1P2xM8_1muDHbNeO_whHsqSpniy_LLpYq) Google Drive folder  
	1.  [Play List](http://www.seinendan.org/eng/play/) of Hirata's theater company
	Seinendan, which includes the robot plays  
	1.  One example of [Three Sisters (Android version)](https://mercatflors.cat/en/espectacle/les-tres-germanes-versio-androide-3/)    
	1. [Seinendan Theater Company + Osaka University Robot Theater
Project](http://www.japansociety.org/event/seinendan-theater-company-osaka-university-robot-theater-project-sayonara-i-worker)

1.  [Uncanny Valley](https://www.rimini-protokoll.de/website/en/project/unheimliches-tal-uncanny-valley). A robot actor in a one-person play. 
Collaboration between Rimini Protokoll and Thomas Melle.


## History

1. Karel Čapek. [R.U.R. (Rossum's Universal
Robots)](http://preprints.readingroo.ms/RUR/rur.pdf)

1. Asimov's Runaround 

1. [a history of cybernetic animals and early
robots](http://cyberneticzoo.com/)

## Articles

1. http://journals.sagepub.com/doi/pdf/10.5772/50644

1. http://www.the-three-sirens.info/intro.html

1. On Stage: [Robots as
Performers](http://guyhoffman.com/publications/HoffmanRSS11Workshop.pdf)

1. [Ontology of Robot
Theatre](http://wustl.probablydavid.com/publications/ontology.pdf)

1. [What is Theatre
Robotics?](http://bostoncommons.net/what-is-theater-robotics/)

1. Shannon, C. E. (1948). A mathematical theory of communication.  The Bell
	 Labs

1. [Art and Technology: The Panacea That
Failed](http://www.etantdonnes.com/SystemsArt/Burnham_Panacea_1980.pdf) Jack  Burnham, from _The
Myths  of  Information_  edited by Kathleen  Woodward, Coda  Press,  1980  
System Technical Journal, Vol. 27

1. [The Machine as Artist: An
Introduction](https://github.com/michaelshiloh/resourcesForClasses/blob/master/doc/theMachineAsArtistIntroduction.pdf) Glenn W. Smith 1 and Frederic Fol Leymarie 

1. Survey chapter from "Art and Electronic Media" by Edward A. Shanken

1. [A Spectacular
Simulacra](http://schip666.blogspot.com/2013/01/a-spectacular-simulacra.html)

1. _Cybernetics and Serendipity_ [catalog](http://www.etantdonnes.com/SystemsArt/cyberneticSerendipityCatalog.pdf)

1. [this](http://www.etantdonnes.com/SystemsArt/Montfort2003_NewMediaReader_17-software-03.pdf)

1. [Analysis](http://schip666.blogspot.com/2014/07/feeling-abandoned-meta-analysis.html)
of an interactive autonomous robot. 


## Artists

1. [ Michael Candy](https://michaelcandy.com)

1. [Simone Giertz](https://youtu.be/WcW70-6eQcY)

3. Jean Tinguely 

6. [Kal Spelletich](http://www.kaltek.org)

7. [Chico Macmurtrie](http://amorphicrobotworks.org/)

4. [Matt Heckert](http://www.mattheckert.com/)

## Tangentially related

1. [Robot Artist](https://vimeo.com/channels/kineticartprojects/30780208)

1. Sudhu's [Pinterest](https://www.pinterest.com/loopstick/)

1. [Theatre robotics for human technology education](http://dl.acm.org/citation.cfm?id=2828975&dl=ACM&coll=DL&CFID=914228458&CFTOKEN=67671507)

1. [Ajay Kapur]( http://karmetik.com/publications)

## Books

1. Japanese robot culture : performance, imagination, and modernity
Yuji. Sone
New York, NY : Palgrave Macmillan 2017

1. Geminoid Studies Science and Technologies for Humanlike Teleoperated Androids
Ishiguro, Hiroshi • 2018
Publisher:
Springer Singapore
ISBN:
9789811087028

1. Essays like Heinrich von Kleist’s “On the Marionette Theater” and Edward Gordon Craig’s “The Actor and the Über-marionette” have suggested that [End Page 400] skillful automata might productively replace and surpass the human actor. 

1. Post-human: thinking humanness through robotics
Julie-Michelle Morin

1. ** Jennifer Rhee "amigdala"

1. The Glass Bees by Ernst Juenger

1. The Invention of Morel by Adolfo Bioy Casares

1. "Art and Electronic Media" Edward A. Shanken (Phaidon)

1. "Book for the Electronic Arts" Arjen Mulder and Maaike Post (de Baile V2)

1. "A Theatre of Machines" A. G. Keller (Macmillan)

1. [Escape Velocity](http://markdery.com/?page_id=145) Mark Dery

1. "Beyond Modern Sculpture" Jack Burnham (George Braziller)

1. "Edison's Eve" Gaby Wood (Knopf)

1. "High Techne" R. L. Rutsky (University of Minnesota Press)

1. Excellent book to help explain why making is a critical part of learning [Invent To Learn: Making, Tinkering, and Engineering in the
Classroom](https://www.amazon.com/gp/product/B00CQDRF84/ref=oh_aui_d_detailpage_o00_?ie=UTF8&psc=1)

1. [Rise of the
Robots](https://www.amazon.com/dp/B00PWX7RPG/ref=dp-kindle-redirect?_encoding=UTF8&btkr=1)

1. Excellent readings in the humanities regarding machine-inclined thinking:
	CLAIR, Jean and Harald Szeemann. eds. 
	Le Macchine Celibi / The Bachelor Machines. 
	Amsterdam: Stedelijk Museum, 1977.9. 

1. [Making Things Move: DIY Mechanisms for Inventors, Hobbyists, and
Artists](www.amazon.com/Making-Mechanisms-Inventors-Hobbyists-Artists/dp/0071741674/ref=sr_1_1?ie=UTF8&qid=1490489633&sr=8-1&keywords=making+things+move)

1. [507 Mechanical
Movements](https://www.amazon.com/507-Mechanical-Movements-Henry-Brown/dp/1614275181/ref=sr_1_1?ie=UTF8&qid=1490489734&sr=8-1&keywords=507+Mechanical+Movements)

1. Practical Electronics for Inventors

1. Vehicles; Valentino Braitenberg, 1986
  A set of mostly thought experiments starting with what you
  described as the coffee can robots and working into a real
  discussion of neural behavior.

1. Systems; Edward A. Shanken (ed), 2015
  A large collection of excerpts from articles about Systems and Art.
  I can heartily recommend anything Ed has written as I think he
  is one of the few people who 'get' media art. This also holds
  for articles by Simon Penny (there are a couple in this book),
  whom I think he is still at UC Irvine but seems to have dropped
  off the Art Map.

1. Industrial Culture Handbook www.researchpubs.com

1. Pranks www.researchpubs.com

1. [Cybernetics Or Control and Communication in the Animal and the
Machine](https://www.amazon.com/Cybernetics-Second-Control-Communication-Machine/dp/1614275025/ref=sr_1_1?ie=UTF8&qid=1490657642&sr=8-1&keywords=Cybernetics+Or+Control+and+Communication+in+the+Animal+and+the+Machine)

1. Physical Computing: Sensing and Controlling the Physical
World with Computers by Igoe/O'Sullivan

1. Cabaret Mechanical Movement by Gary Alexander and Aidan Lawrence-Onn ISBN-13: 978-0952872931

1. Making Simple Automata by Robert Race  ISBN-13: 978-1847977441

1. "How to Build Simple Automata" book (PDF)

1. "Robots and Art: Exploring an Unlikely Symbiosis" Editors: Herath, Damith,
Kroos, Christian, Stelarc (Eds.) ISBN 978-981-10-0319-6

1. "The Future of the Internet and How to Stop it" by Jonathan Zittrain

1. "Robotics: A Very Short Introduction" by Alan Winfield ISBN-13:
978-0199695980
especially pg. 39 and 79

1.  "Robo Sapiens: Evolution of a New Species" by Peter Menzel ISBN-13:
978-0262632454

1. "The Robot in the Garden: Telerobotics and Telepistemology in the Age of
the Internet" by Ken Goldberg ISBN-13: 978-0262571548




## Notes

1. A robotic performance differs from a robotic installation in that a
performance has a beginning and end, and a script

1. A performance is a series of events created to be witnessed

1.  When interact with a robot, we have a model of the robot, but the robot
has no model of us
https://en.wikipedia.org/wiki/Theory_of_mind

1.  "Robots don't need to feel, they just need to give the impression they do" - Louise Lepage

## Questions

1. What is "Automata" vs. "Autonomous beings"?

1. What is interactive?

1. What is a robot? Can a robot be remote controlled or must it be autonomous?
	 
1. What is performance?

1. Will we arrive at a place where the fridge worries when the toaster goes
missing?

1. What is it that gives personality? Does a robot need to be anthropomorphic?
	 Consider
	 [this](http://thescientistvideographer.com/wordpress/bully-triangles-and-terrified-circles/)



# Resources for Robota Psyche
## Required textbooks

1. *Vehicles: Experiments in Synthetic Psychology* 2nd Edition,
Valentino Braitenberg   
ISBN-10 : 0262521121  
ISBN-13 : 978-0262521123  

1. *Entangled: technology and the transformation of performance*,
Chris salter  
ISBN-13: 978-0262195881  
ISBN-10: 0262195887  

1. *The Cybernetic Brain*,  
Andrew Pickering  
ISBN-10 : 0226667901  
ISBN-13 : 978-0226667904  
University of Chicago Press; Illustrated Edition (December 15, 2011)

1. *The Human Use of Human Beings*,  
Norbert Wiener  
ISBN-13 : 978-0306803208  
ISBN-10 : 0306803208  
Da Capo Press; New edition (March 22, 1988)  

1. *The Living Brain*,  
Grey Walter  
ISBN-10 : 0393001539  
ISBN-13 : 978-0393001532  
W. W. Norton and Company, Inc.; Second Edition (May 17, 1963)  

1. *Complexity*,
Melanie Mitchell  
ISBN-10 : 0199798109  
ISBN-13 : 978-0199798100  
Oxford University Press; 1st Edition (September 1, 2011)


## Optional texts:

1. *Chaos: Making a New Science – Illustrated, *,  
James Gleick  
ISBN-10 : 978-0143113454  
ISBN-13 : 978-0143113454  
Penguin Books; 20th Anniversary ed. Edition (August 26, 2008)

1. *Computer Power and Human Reason*,  
J Weizenbaum  
ISBN-10 : 0140179119  
ISBN-13 : 978-0140179118  
Penguin Science, January 1, 1984

1. *Cybernetics: Second Edition: Or the Control and Communication in the Animal and the Machine*,  
Norbert Wiener   
ISBN-10 : 1614275025  
ISBN-13 : 978-1614275022  
Martino Fine Books; 2nd ed. Edition (October 2, 2013)

1. *God and Golem, Inc.*,  
Norbert Wiener  
ISBN-10 : 0262730111  
ISBN-13 : 978-0262730112  
The MIT Press; 7th ed. Edition (March 15, 1966)

1. *Cyborg Manifesto*,
In Simians, Cyborgs, and Women: The Reinvention of Nature 1st Edition  
Donna Haraway  
ISBN-10 : 0415903874  
ISBN-13 : 978-0415903875  
Routledge; 1st Edition (December 12, 1990)    

1. *Turtles, Termites, and Traffic Jams : 
Explorations in Massively Parallel Microworlds*  
Mitchel Resnick  
in the [NYU online
library](http://web.b.ebscohost.com.proxy.library.nyu.edu/ehost/ebookviewer/ebook?sid=5477c50e-b17d-4d9a-8d91-49a2992dfbdd%40pdc-v-sessmgr03&vid=0&format=EB)

## Links

1. [Joanna Bryson](https://www.joannajbryson.org/)
	studies artificial and natural intelligence. She's working to improve the
	governance and ethics of digital technology.


## To be sorted

1.  [Machine Art In The Twentieth
  Century](doc/machineArtInTheTwentiethCentury.pdf)
  
1. [Richard Hamilton](doc/richardhamilton00hami.pdf)

1. Kris Verdonck A Two Dog Company

1. Peter Eckersall CUNY

1. Noh Theatre
Samuel Becket
Brecht

1. "Hey Joe" actor waits for voiceover to define him
Normally, objects represent themselves. With high tech, objects have 2nd agenda

1. ** Marco Donnarumma and Kristina Anderson
Can theatre be a site for practice at the future?
Kristina (Technical University Eindhoven)
This work is situated in a grey zone: academia, art, theatre, music, design
Intelligence is a human word and might be inapplicable to machines
"Human" and "Machine" are neither defined nor static

1. ** Karen Barad: analyze humanness through robotics (get book)
theatre space is perfect for deconstructing Mori's idealized humanness
design driven by normative vision of humanness, or can challenge this

The staging of techo-vulnerability
Ruowen Xu Utrecht University r.xu@uu.nl
entanglement of critique and technophilia

Chico's broken robots: threatening and strong vs. weak and pathetic
Mirja: agent solitude
"Human Being at Risk" Mark Coelkelbergh

morse cups

schipp's robot

1.
michael.rau@stanford.edu (or is it rav)
viewpoints as a vocabulary for robots
mary overlie viewpoints
viewpoints ai (git)
luminos ai (revised)

1.
https://www.youtube.com/watch?v=t2t4BALBmxg
robotic theatre
robot theatre
https://www.sau.edu/news_and_events/n170404_robot-theatre.html
https://www.youtube.com/watch?v=Uo-4RQPEHIk
https://robohub.org/robots-robotics-in-theatre-film-and-television/
https://theatre.uta.edu/emotional-robotics-living-lab/
https://www.robottheatre.co.uk/publications
https://www.robottheatre.co.uk/
http://techandlaw.net/robots-become-art-interview-mr-yi-wei-keng/
robots.ieee.org/robots

1. Thomas Riccio University of Texas, Dallas
thomasriccio.com
Hanson robotics, creators of [Sophia](https://www.hansonrobotics.com/sophia/)
robot personalities 
viseme
frubber
in-character responses to failure modes

1. Louise LePage
university of york

1. Helen Root

1. Irene Echeverria - Altuna

1. Gobsquat Collective

1. Petra Goyeinboeck
Rob Saunders
Creative Robotics Lab University of New South Wales
University of Sydney

1. Machine Movement Lab
Louise Phillippe Deters

1. Tiller Girls
"The Performance of Creative Machines"
"Accomplice" (knocking robot)

1. "Robots As Media"
[syllabus](http://www.peterasaro.org/courses/2016Robots.html)
from The New School's [Peter Asaro](https://twitter.com/PeterAsaro)

1. [Musical robots program at CalArts, ](http://karmetik.com/sites/default/files/publications/2010_nime_robot_0.pdf)

1. Mark Dery - documentary and books

1. ROS, the [robot operating system](http://www.ros.org/).
The ros runs on arduinos and pis. It takes care of all the painful details.
The ROS site has a lot of robot platforms that might be good for starter
projects.

1. [analysis of "Feeling
Abandoned"](http://schip666.blogspot.com/2014/07/feeling-abandoned-meta-analysis.html)

1. Directions in Kinetic Sculpture; Peter Selz, 1966
  The catalog of a show at the UC Berkeley art museum from that year.
  "I found some copies on sale at the museum a couple years ago.
  It is fascinating, both for what was being done and shown here --
  dating from the early 20th century to the 60's -- and for wondering
  why it was not being done and shown in the late 20th century..."

1. Working Conditions; Hans Haake (Alexander Alberro, ed), 2016
  Collected writings of Mr. Haacke. Not so much an art/tech guy
  but wider in scope with much interesting social commentary.
  He did kinetic-ish stuff in the 60s and then switched to
  social systems in 1970.
  His piece [Blue
	Sail](https://kwrgibson.files.wordpress.com/2014/05/tumblr_ljjurvg9aj1qzzt5bo1_500.jpg)

1. Gil Weinberg's work on robot musicianship at Georgia Tech.

1. Heather Knight who is studying with Wendy Ju and is working on robots and
theater.

1. Leonardo magazine

1. Guy Debord 

1. Jean Baudrillard 

1. [Grey
Walter](http://cyberneticzoo.com/cyberneticanimals/w-grey-walter-and-his-tortoises/)

1. [Animatronics](https://en.wikipedia.org/wiki/Animatronics)

1. [History of
	 Technology](https://en.wikipedia.org/wiki/History_of_technology)

