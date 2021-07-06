/*
   Simple example of using a state machine for a game
*/

/* Circuit */
const int LEDPIN = 3;
const int BLUEBUTTONPIN = 2;
const int GREENBUTTONPIN = 4;

int state;
boolean gameWon;

void setup() {
  state = 0;
  gameWon = false;
}

void loop() {

  /*
     state 0: initial state
     state 1: instructions state
      if blue button is pressed, instructions are displayed again
      if green button is pressed, game starts
     state 2: game play state
     state 3: set initials for high score
      blue button: scrool through initials
      green button: play again
     state 4: ask if user wants to play again
  */

  // Implementing a state machine with if() statements
  if (state == 0) {
    // reset whatever you need for the game
    digitalWrite(LEDPIN, HIGH);
    state = 1; // state transition to state 1
  }

  if (state == 1) {
    displayInstructions();
    if (digitalRead(BLUEBUTTONPIN) == HIGH) {
      restartInstructions();
    }
    if (digitalRead(GREENBUTTONPIN) == HIGH) {
      state = 2;
    }
  }

  if (state == 2) {
    startGame();
    if (digitalRead(BLUEBUTTONPIN) == HIGH) {
      doBlueButtonAction();
    }
    if (digitalRead(GREENBUTTONPIN) == HIGH) {
      doGreenButtonAction();
    }
    if (gameWon == true) {
      state = 3;
    }

  }

  if (state == 3) {
    if (digitalRead(BLUEBUTTONPIN) == HIGH) {
      displayNextInitials();
    }
    if (digitalRead(GREENBUTTONPIN) == HIGH) {
      state = 4;
    }
  }

  if (state == 4) {
    askUserIfPlayAgain();
    if (digitalRead(GREENBUTTONPIN) == HIGH) {
      state = 0;
    }
  }

  // The same state machine with a switch() statement
  switch (state) {
    case 0:
      // reset whatever you need for the game
      digitalWrite(LEDPIN, HIGH);
      state = 1; // state transition to state 1
      break;

    case 1:
      displayInstructions();
      if (digitalRead(BLUEBUTTONPIN) == HIGH) {
        restartInstructions();
      }
      if (digitalRead(GREENBUTTONPIN) == HIGH) {
        state = 2;
      }
      break;

    case 2:
      startGame();
      if (digitalRead(BLUEBUTTONPIN) == HIGH) {
        doBlueButtonAction();
      }
      if (digitalRead(GREENBUTTONPIN) == HIGH) {
        doGreenButtonAction();
      }
      if (gameWon == true) {
        state = 3;
      }

      break;

    case 3:
      if (digitalRead(BLUEBUTTONPIN) == HIGH) {
        displayNextInitials();
      }
      if (digitalRead(GREENBUTTONPIN) == HIGH) {
        state = 4;
      }
      break;

    case 4:
      askUserIfPlayAgain();
      if (digitalRead(GREENBUTTONPIN) == HIGH) {
        state = 0;
      }
      break;
  } // end of switch() statement
} // end of loop() function

void displayInstructions() {
}
void restartInstructions() {
}
void startGame() {
} 
void doBlueButtonAction() {
}
void doGreenButtonAction() {
}
void displayNextInitials() {
}
void askUserIfPlayAgain() {
}
