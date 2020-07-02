String command;

int matchTime;
int matchMin;
int matchSec;
bool matchStatus;

int currentMillis;
int prevMillis = 0;

void setup() 
{
  Serial.begin(9600);
  matchStatus = false;
}

void loop() 
{
  commadHandler();

  if(command == (matchStart))
  {
    matchStatus = true;
    matchTime = 180;
    command = none;
  }
  
  if(matchStatus)
  {
    matchTimer();
  }
}

void commandHandler()
{
  if(Serial.available() > 0)
  {
    command = Serial.read();
    Serial.print("Recieved Command: ");
    Serial.println(command);
  }
}

void matchTimer()
{
  currentMillis = millis();

  if((currentMillis - prevMillis) >= 1000)
  {
    matchTime--;
    prevMillis = currentMillis;
  }

  matchMin = matchTime / 60;
  matchSec = matchTime % 60;

  Serial.print(gameMin);
  Serial.print(":");
  if(matchSec < 10)
  {
    Serial.print("0");
  }
  Serial.println(matchSec);

  if(matchTime = 0)
  {
    matchStatus = false;
  }
}
