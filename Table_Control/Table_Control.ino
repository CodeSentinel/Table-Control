#include "libs/FastLED/FastLED.h"     // version 3.3.3

#define REFRESH_INTERVAL 2          // time display refresh interval in milliseconds

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

//Variables for POV effect for scoreboard
byte segmentOn = 0;       //Which segment should turn on
bool bcdOut1 = 0;         //A,B,C,D pins of the 74LS47
bool bcdOut2 = 0;
bool bcdOut3 = 0;
bool bcdOut4 = 0;
bool segMOS1 = 0;         //Transistors that control current flow through
bool segMOS2 = 0;         // each segment
bool segMOS3 = 0;

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
    segMOS1 = LOW;    //Turn off the transistors during transition phase
    segMOS2 = LOW;
    segMOS3 = LOW;
    switch(segmentOn)
    {
      case 0:   //The ones place of seconds will illuminate
        bcdOut1 = segOnesA;
        bcdOut2 = segOnesB;
        bcdOut3 = segOnesC;
        bcdOut4 = segOnesD;
        segMOS1 = HIGH;       //Turn on transistor for ones of match second
        break;
      case 1:
        bcdOut1 = segTensA;
        bcdOut2 = segTensB;
        bcdOut3 = segTensC;
        bcdOut4 = segTensD;
        segMOS2 = HIGH;
        break;
      case 2:
        bcdOut1 = segMinsA;
        bcdOut2 = segMinsB;
        bcdOut3 = segMinsC;
        bcdOut4 = segMinsD;
        segMOS3 = HIGH;
      default:
        Serial.println("How did we get here?");
    }

    if(segmentOn >=2)
    {
      segmentOn = 0;
    }
    else
    {
      segmentOn+= 1;
    }
    prevDispMillis = dispMillis;
    /*
    Serial.print(matchMins);
    Serial.print(":");
    Serial.print(matchSecTens);
    Serial.println(matchSecOnes);*/
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
