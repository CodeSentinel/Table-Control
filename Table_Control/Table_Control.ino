#include "libs/FastLED/FastLED.h"         // version 3.3.3
#include <SPI.h>                          // built in no library file necessary
#include <SD.h>                           // built in no library file necessary

#define REFRESH_INTERVAL 500              // time refresh interval in milliseconds
#define IR_SENSOR 2                   // connect ir sensor to pin 2

int dispMillis;                           // millis variables for display refresh
int prevDispMillis = 0;

String command;

int matchTime;                            // match status variables
int matchMin;
int matchSec;
int matchSecTens;
int matchSecOnes;
bool matchStatus = false;
bool goalAScored = false;                  // code test parameter
bool goalBScored = false;

int diffMillis  = 100;                    // match timekeeping variables
int matchMillis;
int prevMatchMillis = 0;

bool startAni = false;
bool endAni = false;
bool goalAni = false;

File gameFile;

void setup() 
{
  Serial.begin(9600);
  Serial.println("System Initializing");

  if(!SD.begin())
  {
    Serial.println("SD Failed");
    while(1);
  }
  Serial.println("Initialization Complete");
  
  pinMode(IR_SENSOR, INPUT);                // set pin 2 as input
}

void commandHandler()                            // function to handle serial command (mainly used for serial line commands during prototyping)
{
  if(Serial.available())                         // checks for a command in the serial port and writes it to a string if available
  {
    delay(2);                                    // allows string to fully enter buffer for reading
    command = Serial.readString();
    Serial.print("Recieved Command: ");
    Serial.println(command);
  }

  if(command == "start")                         // start match command resets matchTime variable to 3 before begining the match
  {
    matchStatus = true;
    matchTime = 180;                             // countdown timer length
    command = "none";
    Serial.println("start executed");            // debugging
  }

  if(command == "pause")
  {
    matchStatus = false;
    command = "none";
    Serial.println("pause executed");           // debugging
  }

  if(command == "resume")
  {
    matchStatus = true;
    command = "none";
    Serial.println("resume executed");          // debugging
  }

  if(command == "goal a")
  {
    goalAScored = true;
    command = "none";
    Serial.println("goal a executed");           // debugging
  }

  if(command == "goal b")
  {
    goalBScored = true;
    command = "none";
    Serial.println("goal b executed");             // debugging
  }
}

void matchTimer()                                // function that handles the timekeeping of a match
{
  matchMillis = millis();

  if((matchMillis - prevMatchMillis) > diffMillis)          // determines if the match was paused and corrects for time shift
  {
    prevMatchMillis = matchMillis - diffMillis;
  }

  diffMillis = matchMillis - prevMatchMillis;          // determines time difference for later referencing during match resume
  diffMillis = diffMillis + 100;                       // buffer to allow low time differences between loops

  if((matchMillis - prevMatchMillis) >= 1000)          // decriments the timer every 1 second
  {
    matchTime = matchTime - 1;
    prevMatchMillis = matchMillis;
  }

  if(matchTime == 0)                                   // ends match at 0 second mark
  {
    matchStatus = false;
    endAni = true;
  }
}

void timeDisplay()                                    // function to handle the display of the match timer
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



void goalDetection()
{
  gameFile = SD.open("gamelogs.txt", FILE_WRITE);
  
  if(goalAScored)                                    // temporary parameter for testing without hardware
  {
    matchStatus = false;
    goalAni = true;
    goalAScored = false;
    gameFile.print(matchTime);
    gameFile.print(" -- ");
    gameFile.println("Team A scored");
  }

  if(goalBScored)
  {
    matchStatus = false;
    goalAni = true;
    goalBScored = false;
    gameFile.print(matchTime);
    gameFile.print(" -- ");
    gameFile.println("Team B Scored");
  }

  gameFile.close();
}

void animationHandler()
{
  if(startAni)
  {
    // insert startup animation
    startAni = false;
  }

  if(endAni);
  {
    // insert match end animation
    endAni = false;
  }
  if(goalAni)
  {
    // insert goal animation
    goalAni = false;
  }
}

void loop()                      // main loop for calling other functions
{
  commandHandler();

  goalDetection();
  
  if(matchStatus)                // timer runs only when the match status is true
  {
    matchTimer();
  }

  timeDisplay();

  animationHandler();
}
