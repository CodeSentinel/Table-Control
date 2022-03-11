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
#define REFRESH_INTERVAL 500              // time refresh interval in milliseconds
#define IR_SENSOR 2                       // connect ir sensor to pin 2

// ALL VARIABLES NEEDED FOR TIMING USING millis()
int diffMillis  = 100;                            // match timekeeping variables
int matchMillis;
int prevMatchMillis = 0;
const unsigned int scoreboardMillisDelay = 500;   // delay between scoreboard refreshes
unsigned int prevScoreboardMillis = 0             // storage for last time scoreboard refreshed

// ALL VARIABLES NEEDED FOR GAME MECHANICS AND TIMING
int matchTime;                                        // match time in seconds
byte scoreTeam1 = 0;                                  // score counter for team 1
byte scoreTeam2 = 0;                                  // score counter for team 2
bool matchStatus = false;                             // flag for if a game is active
bool goalScored = false;                              // flag for if a goal has been scored

// ALL VARIABLES NEEDED FOR TIME AND GOAL DISPLAY SYSTEM
int matchMin;
int matchSec;
int matchSecTens;
int matchSecOnes;

// ALL VARIABLES USED FOR DEBUGGING
String command;

// REQUIRED SETUP FUNCTION FOR THE PROGRAM
void setup() 
{
  Serial.begin(9600);
  Serial.println("System Start");
  pinMode(IR_SENSOR, INPUT);                // set pin 2 as input
}

void commandHandler()                       // function to handle serial command (mainly used for serial line commands during prototyping)
{
  if(Serial.available())                    // checks for a command in the serial port and writes it to a string if available
  {
    delay(2);                               // allows string to fully enter buffer for reading
    command = Serial.readString();
    Serial.print("Recieved Command: ");
    Serial.println(command);
  }

  if(command == "start")                    // start match command resets matchTime variable to 3 before begining the match
  {
    matchStatus = true;
    matchTime = 180;                        // countdown timer length
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

  if(matchTime <= 0)                     // ends match at 0 second mark
  {
    matchStatus = false;
    endAni = true;
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
    
    Serial.print(matchMin);
    Serial.print(":");
    Serial.print(matchSecTens);
    Serial.println(matchSecOnes);
  }
}

void goalTracking()
{
  goalScored = digitalRead(IR_SENSOR) == 1 ? true : false;    // sensor == 1 means object detected (goal), sensor == 0 means no object detected (no goal)
  if(goalScored)                                              // temporary parameter for testing without hardware
  {
    matchStatus = false;
    goalAni = true;
    goalScored = false;
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

  goalTracking();
  
  if(matchStatus)          // timer runs only when the match status is true
  {
    matchTimer();
  }

  timeDisplay();
}
