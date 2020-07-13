#define REFRESH_INTERVAL 500          // display refresh interval

int dispMillis;         // millis variables for display refresh
int prevDispMillis = 0;

String command;

int matchTime;          // match status variables
int matchMin;
int matchSec;
int matchSecTens;
int matchSecOnes;
bool matchStatus = false;
bool goalScored = false;          // code test parameter

int diffMillis  = 100;         // match timekeeping variables
int matchMillis;
int prevMatchMillis = 0;

bool startAni = false;
bool endAni = false;
bool goalAni = false;

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

  if(command == ("start"))          // start match command resets matchTime variable to 180 before begining the match
  {
    matchStatus = true;
    matchTime = 180;
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

  if((matchMillis - prevMatchMillis) > diffMillis)          // determines if the match was paused and corrects for time shift
  {
    prevMatchMillis = matchMillis - diffMillis;
  }

  diffMillis = matchMillis - prevMatchMillis;         // determines time difference for later referencing during match resume
  diffMillis = diffMillis + 100;            // buffer to prevent infinite loop

  if((matchMillis - prevMatchMillis) >= 1000)         // decriments the timer every 1 second
  {
    matchTime = matchTime - 1;
    prevMatchMillis = matchMillis;
  }

  if(matchTime == 0)         // ends match at 0 second mark
  {
    matchStatus = false;
  }
}

void timeDisplay()          // function to handle the display of the match timer
{
  dispMillis = millis();
  
  if((dispMillis - prevDispMillis) >= REFRESH_INTERVAL)         // checks to see if the display needs to be refreshed
  {
    prevDispMillis = dispMillis;
    
    matchMin = matchTime / 60;
    matchSec = matchTime % 60;
    matchSecTens = matchSec / 10;
    matchSecOnes = matchSec % 10;

    Serial.print(matchMin);
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
    goalAni = true
  }
}

void animationHandler()
{
  if(startAni)
  {
    //startup animation
    startAni = false;
  }

  if(endAni);
  {
    //match end animation
    endAni = false;
  }
  if(goalAni)
  {
    //goal animation
    goalAni = false;
  }
}

void loop()         // main loop for calling other functions
{
  commandHandler();

  goalDetection();
  
  if(matchStatus)
  {
    matchTimer();
  }

  timeDisplay();

  animationHandler();
}
