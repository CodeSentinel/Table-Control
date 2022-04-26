//PINS NEEDED
const byte btnLeftGoal = 4;
const byte btnStartGame = 5;
const byte btnPauseGame = 6;
const byte btnRightGoal = 7;

//BUTTON FLAGS FOR PRESSED/NOT PRESSED STATUS
bool btnLeftGoalPressed = false;
bool btnRightGoalPressed = false;
bool btnStartGamePressed = false;
bool btnPauseGamePressed = false;

const unsigned long btnCheckDelay = 50;
unsigned long btnCheckLast = 0;


void setup() 
{
  //SET UP ALL NEEDED PINS
  pinMode(btnLeftGoal, INPUT_PULLUP);
  pinMode(btnStartGame, INPUT_PULLUP);
  pinMode(btnPauseGame, INPUT_PULLUP);
  pinMode(btnRightGoal, INPUT_PULLUP);

  //START SERIAL MONITOR TO CHECK DATA
  Serial.begin(9600);
}

void CheckButtonStatus()
{
  /*
   * To check for changes to a push button, while also debouncing the signal, we need to
   * check the current state of the button, as well as the last state of the button. If
   * the current button state is different from the previous, then the button has either
   * been pressed or released. To prevent button bounce, the function should also only
   * occur once every 20-30ms or so. The flag for buttons is cleared when a button is
   * released, or can be cleared by a function that uses the button (to prevent multiple
   * functions that use the same button from occuring)
  */
  //READ ALL BUTTON STATES
  bool leftGoalState = digitalRead(btnLeftGoal);
  bool rightGoalState = digitalRead(btnRightGoal);
  bool pauseGameState = digitalRead(btnPauseGame);
  bool startGameState = digitalRead(btnStartGame);

  //CHECK FOR CHANGE TO FIRST BUTTON
  if(leftGoalState == LOW && btnLeftGoalPressed == false)
  {
    //BUTTON HAS BEEN PRESSED
    btnLeftGoalPressed = true;
  }
  else if(leftGoalState == HIGH && btnLeftGoalPressed == true)
  {
    //BUTTON HAS BEEN RELEASED
    btnLeftGoalPressed = false;
  }
  else
  {
    //BUTTON IS BEING HELD DOWN OR HASN'T BEEN TOUCHED
    //DO NOTHING
  }

  //CHECK FOR SECOND BUTTON CHANGE
  if(rightGoalState == LOW && btnRightGoalPressed == false)
    btnRightGoalPressed = true;
  else if(rightGoalState == HIGH && btnRightGoalPressed == true)
    btnRightGoalPressed = false;
  else{}

  //CHECK FOR THIRD BUTTON CHANGE
  if(pauseGameState == LOW && btnPauseGamePressed == false)
    btnPauseGamePressed = true;
  else if(pauseGameState == HIGH && btnPauseGamePressed == true)
    btnPauseGamePressed = false;
  else{}

  //CHECK FOR FOURTH BUTTON CHANGE
  if(startGameState == LOW && btnStartGamePressed == false)
    btnStartGamePressed = true;
  else if(startGameState == HIGH && btnStartGamePressed == true)
    btnStartGamePressed = false;
  else{}
}

void loop() 
{
  unsigned long currentTime = millis();

  if((currentTime - btnCheckLast) >= btnCheckDelay)
  {
    CheckButtonStatus();
    Serial.println(btnLeftGoalPressed);
    Serial.println(btnStartGamePressed);
    Serial.println(btnPauseGamePressed);
    Serial.println(btnRightGoalPressed);

    btnCheckLast = currentTime;
  }
  
}
