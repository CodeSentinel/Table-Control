#define REFRESH_INTERVAL 750          // display refresh interval

int dispMillis;         // millis variables for display refresh
int prevDispMillis = 0;

String command;

int matchTime;          // match status variables
int matchMin;
int matchSec;
bool matchStatus;

int diffMillis;         // match timekeeping millis
int matchMillis;
int prevMatchMillis = 0;

void setup() 
{
  Serial.begin(9600);
  matchStatus = false;
}

void commandHandler()         // function to handle serial command (mainly used for serial line commands during prototyping)
{
  if(Serial.available() > 0)          // checks for a command in the serial port and writes it to a string if available
  {
    command = Serial.read();
    Serial.print("Recieved Command: ");
    Serial.println(command);
  }

  if(command == ("start match"))          // start match command resets matchTime variable to 180 before begining the match
  {
    matchStatus = true;
    matchTime = 180;
    command = "none";
  }

  if(command == ("pause"))
  {
    matchStatus = false;
  }

  if(command == ("resume"))
  {
    matchStatus = true;
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

  if((matchMillis - prevMatchMillis) >= 1000)         // decriments the timer every 1 second
  {
    matchTime--;
    prevMatchMillis = matchMillis;
  }

  if(matchTime = 0)         // ends match at 0 second mark
  {
    matchStatus = false;
  }
}

void timeDisplay()          // function to handle the display of the match timer
{
  dispMillis = millis();
  
  if((dispMillis - prevDispMillis) == REFRESH_INTERVAL)         // checks to see if the display needs to be refreshed
  {
    prevDispMillis = dispMillis;
    
    matchMin = matchTime / 60;
    matchSec = matchTime % 60;

    Serial.print(matchMin);
    Serial.print(":");
    if(matchSec < 10) `       /// if the seconds are smaller than 10 it will add a 0 to account for the missing digit
    {
      Serial.print("0");
    }
    Serial.println(matchSec);
  }
}

void loop()         // main loop for calling other functions
{
  commandHandler();
  
  if(matchStatus)
  {
    matchTimer();
  }

  timeDisplay();
}
