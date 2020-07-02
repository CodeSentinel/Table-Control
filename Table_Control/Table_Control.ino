#define REFRESH_INTERVAL 750

int dispMillis;
int prevDispMillis = 0;

String command;

int matchTime;
int matchMin;
int matchSec;
bool matchStatus;

int diffMillis;
int matchMillis;
int prevMatchMillis = 0;

void setup() 
{
  Serial.begin(9600);
  matchStatus = false;
}

void commandHandler()
{
  if(Serial.available() > 0)
  {
    command = Serial.read();
    Serial.print("Recieved Command: ");
    Serial.println(command);
  }

  if(command == ("start match"))
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

void matchTimer()
{
  matchMillis = millis();

  if((matchMillis - prevMatchMillis) > diffMillis)
  {
    prevMatchMillis = matchMillis - diffMillis;
  }

  diffMillis = matchMillis - prevMatchMillis;

  if((matchMillis - prevMatchMillis) >= 1000)
  {
    matchTime--;
    prevMatchMillis = matchMillis;
  }

  if(matchTime = 0)
  {
    matchStatus = false;
  }
}

void timeDisplay()
{
  dispMillis = millis();
  
  if((dispMillis - prevDispMillis) == REFRESH_INTERVAL)
  {
    prevDispMillis = dispMillis;
    
    matchMin = matchTime / 60;
    matchSec = matchTime % 60;

    Serial.print(matchMin);
    Serial.print(":");
    if(matchSec < 10)
    {
      Serial.print("0");
    }
    Serial.println(matchSec);
  }
}

void loop() 
{
  commandHandler();
  
  if(matchStatus)
  {
    matchTimer();
  }

  timeDisplay();
}
