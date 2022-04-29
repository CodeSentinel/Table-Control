/*
 *  MAIN PROGRAM FILE FOR THE INTERACTIVE SOCCER TABLE PROJECT, "TABLE TEAM",
 *  FOR CAL POLY POMONA ROBOTICS CLUB (2021-2022)
 * 
 *  THE MAIN GOALS OF THIS PROGRAM ARE AS FOLLOWS:
 *  --recognize competing teams using RFID cards and scanner
 *  --keep team information stored physically (SD Card)
 *  --detect goals or other important game events
 *  --display match time and each team's score, for both players and the audience
 *  --display immersive effects for game events using an individually addressable LED matrix
 */

// ALL LIBRARIES REQUIRED FOR THE PROGRAM
#include "libs/FastLED/FastLED.h"         // version 3.3.3
#include <SPI.h>                          // arduino built-in
#include <SD.h>                           // arduino built-in

// ALL CONSTANTS USED THROUGHOUT THE CODE
#define MATCH_LENGTH 180                    // time of one match
#define REFRESH_INTERVAL 100              // time refresh interval in milliseconds
#define LEFT_BUTTON 4
#define RIGHT_BUTTON 7
#define PLAY_PAUSE 6
#define START_MATCH 5

// ALL VARIABLES NEEDED FOR TIMING USING millis()
int diffMillis  = 100;                            // match timekeeping variables
int matchMillis;
int prevMatchMillis = 0;
const unsigned int scoreboardMillisDelay = 500;   // delay between scoreboard refreshes
unsigned int prevScoreboardMillis = 0;             // storage for last time scoreboard refreshed
const unsigned int ioMillisDelay = 50;            //delay between IO checks
unsigned int prevIoMillis = 0;                    //storage for last time IO was checked

// ALL VARIABLES NEEDED FOR GAME MECHANICS AND TIMING
int matchTime = 0;                                    // match time in seconds
byte scoreTeam1 = 0;                                  // score counter for team 1
byte scoreTeam2 = 0;                                  // score counter for team 2
bool matchStatus = false;                             // flag for if a game is active
bool goalScored = false;                              // flag for if a goal has been scored
String dataOut;                                       // outputs to serial for computer interface
bool btnLlast = HIGH;
bool btnRlast = HIGH;
bool btnSlast = HIGH;
bool btnPlast = HIGH;
bool btnLeftGoalPressed = false;                      //flags for all the pressable buttons
bool btnRightGoalPressed = false;
bool btnStartGamePressed = false;
bool btnPauseGamePressed = false;

// ALL VARIABLES NEEDED FOR TIME AND GOAL DISPLAY SYSTEM
int matchMin = 0;
int matchSec = 0;
int matchSecTens = 0;
int matchSecOnes = 0;
int dispMillis;
int prevDispMillis;

// ALL VARIABLES USED FOR DEBUGGING
String command;

// REQUIRED SETUP FUNCTION FOR THE PROGRAM
void setup() 
{
  Serial.begin(9600);
  //Serial.println("System Start");
  pinMode(LEFT_BUTTON, INPUT_PULLUP);               // set pins as input
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);
  pinMode(PLAY_PAUSE, INPUT_PULLUP);
  pinMode(START_MATCH, INPUT_PULLUP);
}

void commandHandler()                       // function to handle serial command (mainly used for serial line commands during prototyping)
{
  if(Serial.available())                    // checks for a command in the serial port and writes it to a string if available
  {
    delay(2);                               // allows string to fully enter buffer for reading
    command = Serial.readString();
    //Serial.print("Recieved Command: ");
    //Serial.println(command);
  }

  if(command == "start")                    // start match command resets matchTime variable to 3 before begining the match
  {
    matchStatus = true;
    matchTime = MATCH_LENGTH;               // countdown timer length
    command = "none";
    Serial.println("start executed");       // debugging
  }

  if(command == "pause")
  {
    matchStatus = false;
    command = "none";
    Serial.println("pause executed");      // debugging
  }

  if(command == "resume")
  {
    matchStatus = true;
    command = "none";
    Serial.println("resume executed");    // debugging
  }

  if(command == "goal")
  {
    goalScored = true;
    command = "none";
    Serial.println("goal executed");     // debugging
  }

  if(command == "k")
  {
    matchStatus = false;
    matchTime = 0;
    scoreTeam1 = 0;
    scoreTeam2 = 0;
    command = "none";
    //Serial.println("kill executed");    // debugging
  }
}

void matchTimer()                        // funtion that handles the timekeeping of a match
{
  matchMillis = millis();

  if((matchMillis - prevMatchMillis) > diffMillis)          // determines if the match was paused and corrects for time shift
  {
    prevMatchMillis = matchMillis - diffMillis;
  }

  diffMillis = matchMillis - prevMatchMillis;               // determines time difference for later referencing during match resume
  diffMillis = diffMillis + 100;                            // buffer to allow low time differences between loops

  if((matchMillis - prevMatchMillis) >= 1000)               // decriments the timer every 1 second
  {
    matchTime = matchTime - 1;
    prevMatchMillis = matchMillis;
  }
}

void timeDisplay()                       // function to handle the display of the match timer
{
  matchMin = matchTime / 60;
  matchSec = matchTime % 60;
  matchSecTens = matchSec / 10;
  matchSecOnes = matchSec % 10;
    
  dispMillis = millis();
  
  if((dispMillis - prevDispMillis) >= REFRESH_INTERVAL)         // checks to see if the display needs to be refreshed
  {
    prevDispMillis = dispMillis;
    
    /* Serial.print(matchMin);
    Serial.print(":");
    Serial.print(matchSecTens);
    Serial.println(matchSecOnes); */

    dataOut = "T";
    dataOut = dataOut + matchMin;
    dataOut = dataOut + ":";
    dataOut = dataOut + matchSecTens;
    dataOut = dataOut + matchSecOnes;
    dataOut = dataOut + "L";
    dataOut = dataOut + scoreTeam1;
    dataOut = dataOut + "R";
    dataOut = dataOut + scoreTeam2;
    Serial.print(dataOut);

    if(matchTime <= 0)                   // ends match at 0 seconds after displaying the final time
    {
      matchStatus = false;
    }
  }
}

void gameInput()
{
  if(btnLeftGoalPressed)
  {
    btnLeftGoalPressed = false;
    //matchStatus = false;
    scoreTeam1 = scoreTeam1 + 1;
  }

  if(btnRightGoalPressed)
  {
    btnRightGoalPressed = false;
    //matchStatus = false;
    scoreTeam2 = scoreTeam2 + 1;
  }

  if(btnPauseGamePressed)
  {
    btnPauseGamePressed = false;
    if(matchStatus)
    {
      matchStatus = false;
    }
    else
    {
      matchStatus = true;
    }
  }

  if(btnStartGamePressed)
  {
    btnStartGamePressed = false;
    if(matchStatus = false)
    {
      matchTime = MATCH_LENGTH;
      scoreTeam1 = 0;
      scoreTeam2 = 0;
    }
  }
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
  //CHECK FOR TIMING
  unsigned int currentTime = millis();
  if((currentTime - prevIoMillis) >= ioMillisDelay)
  {
    //READ ALL BUTTON STATES
    bool leftGoalState = digitalRead(LEFT_BUTTON);
    bool rightGoalState = digitalRead(RIGHT_BUTTON);
    bool pauseGameState = digitalRead(PLAY_PAUSE);
    bool startGameState = digitalRead(START_MATCH);
  
    //CHECK FOR CHANGE TO FIRST BUTTON
    if(leftGoalState == LOW && btnLlast == HIGH)
    {
      //BUTTON HAS BEEN PRESSED
      btnLlast = LOW;
      btnLeftGoalPressed = true;
    }
    else if(leftGoalState == HIGH && btnLlast == LOW)
    {
      //BUTTON HAS BEEN RELEASED
      btnLlast = HIGH;
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

    prevIoMillis = currentTime;

    gameInput();
  }
}

/*
 * MAIN PROGRAM LOOP FOR THE PROGRAM BELOW. GENERAL CODE SHOULD FLOW AS FOLLOWS:
 * --while game is not in progress, check RFID scanner to scan for two distinct teams
 * --upon each time "signing in", load their team data for the match (color, team name, goals)
 * --after two teams signed in, reset all match variables and wait for match start (button press)
 * --ONCE A MATCH HAS STARTED:
 * ----decrement match time each second
 * ----check goal sensors for if a goal occured. if so, pause match and increment score
 * ----play any animations that correspond with match events
 * ----refresh the scoreboard to reflect any time change or score change
 * ----check for any external button presses (timeouts, necessary pauses, errors)
 * ----check for if match has ended using match timer
 * --ONCE A MATCH HAS ENDED:
 * ----store match statistics to physical media (SD Card)
 * ----play any animations that correspond with end of match
 * ----prepare RFID scanner for next check-in
 */

void loop()                 // main loop for calling other functions
{
  commandHandler();
  
  CheckButtonStatus();
  
  if(matchStatus)          // timer runs only when the match status is true
  {
    matchTimer();
    timeDisplay();
  }
}
