String command;

int gameTime;
int gameMin;
int gameSec;
bool gameStatus;

int currentMillis;
int prevMillis = 0;

void setup() 
{
  Serial.begin(9600);
  gameStatus = false;
}

void loop() 
{
  commadHandler();

  if(command == (gameStart))
  {
    gameStatus = true;
    gameTime = 180;
  }
  
  if(gameStatus)
  {
    gameTimer();
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

void gameTimer()
{
  currentMillis = millis();

  if((currentMillis - prevMillis) >= 1000)
  {
    gameTime--;
    prevMillis = currentMillis;
  }

  gameMin = gameTime / 60;
  gameSec = gameTime % 60;

  Serial.print(gameMin);
  Serial.print(":");
  if(gameSec < 10)
  {
    Serial.print("0");
  }
  Serial.println(gameSec);

  if(gameTime = 0)
  {
    gameStatus = false;
  }
}
