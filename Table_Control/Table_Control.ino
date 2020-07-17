#include "libs/FastLED/FastLED.h"     // version 3.3.3

#define REFRESH_INTERVAL 500          // time refresh interval in milliseconds

int dispMillis;                       // millis variables for display refresh
int prevDispMillis = 0;

String command;

int matchTime;                  // match status variables
int matchMins;
int matchSec;
int matchSecTens;
int matchSecOnes;
bool matchStatus = false;
bool matchIntro = false;
bool goalScored = false;        // code test parameter

int diffMillis  = 100;          // match timekeeping variables
int matchMillis;
int prevMatchMillis = 0;

bool startAni = false;
bool endAni = false;
bool goalAni = false;

//Boolean variables that represent BCD for each of the timer 7-segments
bool segOnesA = 0;
bool segOnesB = 0;
bool segOnesC = 0;
bool segOnesD = 0;
bool segTensA = 0;
bool segTensB = 0;
bool segTensC = 0;
bool segTensD = 0;
bool segMinsA = 0;
bool segMinsB = 0;
bool segMinsC = 0;
bool segMinsD = 0;

void setup() 
{
  Serial.begin(9600);
  Serial.println("System Start");
}

void commandHandler()         // function to handle serial command (mainly used for serial line commands during prototyping)
{
  if(Serial.available())          // checks for a command in the serial port and writes it to a string if available
  {
    command = Serial.readString();
    Serial.print("Recieved Command: ");
    Serial.println(command);
  }

  if(command == ("start"))          // start match command resets matchTime variable to 3 before begining the match
  {
    matchIntro = true;
    matchTime = 3;          // countdown timer length
    command = "none";
  }

  if(command == ("pause"))
  {
    matchStatus = false;
    command = "none";
  }

  if(command == ("resume"))
  {
    matchStatus = true;
    command = "none";
  }

  if(command == ("goal"))
  {
    goalScored = true;
    command = "none";
  }
}

void matchTimer()         // funtion that handles the timekeeping of a match
{
  matchMillis = millis();

  if((matchMillis - prevMatchMillis) > diffMillis)    // determines if the match was paused and corrects for time shift
  {
    prevMatchMillis = matchMillis - diffMillis;
  }

  diffMillis = matchMillis - prevMatchMillis;         // determines time difference for later referencing during match resume
  diffMillis = diffMillis + 100;                      // buffer to prevent infinite loop

  if((matchMillis - prevMatchMillis) >= 1000)         // decriments the timer every 1 second
  {
    matchTime = matchTime - 1;
    prevMatchMillis = matchMillis;
    timeConversion();                                 //Updates variables for time displaying
  }

  if((matchTime == 0) && (matchIntro == true))        // ends match intro at 0 second mark and begins the match timer
  {
    matchStatus = true;
    matchIntro = false;
    matchTime = 180;
  }

  if((matchTime == 0) && (matchStatus == true))         // ends match at 0 second mark
  {
    matchStatus = false;
    endAni = true;
  }
}

void timeDisplay()          // Function to display match time on 7-seg array
{
    
  dispMillis = millis();
  
  if((dispMillis - prevDispMillis) >= REFRESH_INTERVAL)         // checks to see if the display needs to be refreshed
  {
    prevDispMillis = dispMillis;
    
    Serial.print(matchMins);
    Serial.print(":");
    Serial.print(matchSecTens);
    Serial.println(matchSecOnes);
  }
}

void goalDetection()
{
  if(goalScored)          // temporary parameter for testing without hardware
  {
    matchStatus = false;
    goalAni = true;
  }
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

void timeConversion()             //Function for calculating the minute and second values
{                                 // from the match timer variable
  matchMins = matchTime / 60;     //Changed matchMin to matchMins
  matchSec = matchTime % 60;
  matchSecTens = matchSec / 10;
  matchSecOnes = matchSec % 10;

  //Store the information as BCD for each 7-segment
  segOnesA = bitRead(matchSecOnes, 0);
  segOnesB = bitRead(matchSecOnes, 1);
  segOnesC = bitRead(matchSecOnes, 2);
  segOnesD = bitRead(matchSecOnes, 3);
  segTensA = bitRead(matchSecTens, 0);
  segTensB = bitRead(matchSecTens, 1);
  segTensC = bitRead(matchSecTens, 2);
  segTensD = bitRead(matchSecTens, 3);
  segMinsA = bitRead(matchMins, 0);
  segMinsB = bitRead(matchMins, 1);
  segMinsC = bitRead(matchMins, 2);
  segMinsD = bitRead(matchMins, 3);
}

void loop()         // main loop for calling other functions
{
  commandHandler();

  goalDetection();
  
  if((matchStatus == true) || (matchIntro == true))         // the timer will run when both the intro and match time are called for
  {
    matchTimer();
  }

  timeDisplay();

  animationHandler();
}
