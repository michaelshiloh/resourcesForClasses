**Preparations**

1. Make an educational account at ....
	1.1. Select NYU New York as your institution

1. Download and install Fusion 360

**Workflow**

It is best if you use variables to dimension everything. Just like with
programs, if you need to change anything, change the variable and 
anything that depends on that
gets updated automatically. In Fusion 360, variables are called **Parameters**

1. Open Fusion 360

1. File -> New Design

1. Your name -> Preferences -> Preview 

	1.1. Select _UI Preview_

	1.1. Select _OK_

1. Since we will be using parameters a lot, it is helpful to 
have this in the shortcuts

	1.1. In the _Modify_ menu, go down to _Change Parameters_ **but do not click
	yet!**

	1.1. **Right click** on the 3 dots and select _Pin to Toolbar_. Note the new
	shortcut which is a Sigma symbol.

	1.1. Click elsewhere to close this pulldown menu

1. Enter all your parameters. These might be the size of the material,
the size of the 5 holes for the stepper motor (and other holes), the distance
between all the holes, etc.

	1.1. Click on the _Change Parameter_ icon (Sigma symbol).

	1.1 Click on the _+_ sign next to **User Parameters**

	1.1 Enter your first parameter, e.g. 

		1.1.1. motorScrewDiameter 3mm

		1.1.1. motorScrewDistanceOC 31mm

		1.1.1. acrylicWidth 200mm

		1.1.1 motorDistanceFromEdge 20mm


1. In the Browser tab on the left, **Right click** in the top of the tree 
(it should say _(unsaved)_ and select _New Component_.

	1.1. **Double Left click** on the name and change it to something 
	meaningful, like **stepper motor mounting**

	1.1. Verify that this new component is selected (circle with dot to the
	right of the name).

1. Click on _Create Sketch_ (leftmost icon in the toolbar)
