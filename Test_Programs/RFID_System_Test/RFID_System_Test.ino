/*
 * THIS PROGRAM IS MEANT TO TEST THE FUNCTIONALITY OF AN RFID READER
 * NEEDED FOR THE MAIN TableOS. SINCE ALL DATA WILL BE STORED TO
 * AN SD CARD, NO WRITING OF THE RFID CARDS NEEDS TO BE DONE:
 * INSTEAD, THE UID OF EACH CARD WILL BE USED TO SEARCH FOR A
 * SPECIFIC TEAM'S DATA SET
 * 
 * THIS PROGRAM WAS TESTED ON AN ARDUINO MEGA!
 */

//DEFINE ANY REQUIRED LIBRARIES
#include <SPI.h>            //Arduino library for SPI comms
#include <MFRC522.h>        //Library to utilize an RFID Reader

//DEFINE ANY CONSTANTS
#define RST_PIN 5
#define SS_PIN 53
#define ID_SIZE 4

//CREATE THE PRIMARY RFID OBJECT TO INTERACT WITH
MFRC522 rfid(SS_PIN, RST_PIN);

//CREATE STORAGE FOR A CARD'S ID NUMBER
byte currentID[ID_SIZE];        //for current card's ID
byte lastID[ID_SIZE];           //the ID of the card last loop

//CREATE CONSTANT STORAGE FOR SPECIFIC TEAM'S CARD NUMBERS
const byte teamID_1[ID_SIZE] = {57,99,33,179};
const byte teamID_2[ID_SIZE] = {178,211,255,45};

/*
 * NEW FUNCTIONS DEFINED BELOW
 */

//NEXT THREE FUNCTIONS FOR SIMULATING CHECKING SD CARD DATA
//ACCESSES TEAM COLOR, NAME, AND GOAL COUNT USING A TEAM NUMBER
//THIS TEAM NUMBER IS A BYTE
String ReadSD_TeamColor(byte teamNum)
{
  //CREATE STORAGE FOR RETURNABLE
  String colorToReturn = "none";

  //USE TEAM NUMBER TO RETURN TEAM DATA
  switch(teamNum)
  {
    case 1:
      colorToReturn = "Blue";
      break;
    case 2:
      colorToReturn = "Red";
      break;
    default:
      colorToReturn = "error";
  }

  //RETURN DATA TO FUNCTION CALL
  return colorToReturn;
}
uint8_t ReadSD_TeamGoals(byte teamNum)
{
  //CREATE STORAGE FOR RETURNABLE
  byte goalsToReturn = 0;
 
  //USE 
  switch(teamNum)
  {
    case 1:
      goalsToReturn = 5;
      break;
    case 2:
      goalsToReturn = 10;
      break;
    default:
      goalsToReturn = 255;
  }
  return goalsToReturn;
}
String ReadSD_TeamName(byte teamNum)
{
  //CREATE STORAGE FOR RETURNABLE
  String nameToReturn = "none";

  //USE TEAM NUMBER TO RETURN TEAM DATA
  switch(teamNum)
  {
    case 1:
      nameToReturn = "Blue Team";
      break;
    case 2:
      nameToReturn = "Red Team";
      break;
    default:
      nameToReturn = "error";
  }

  //RETURN DATA TO FUNCTION CALL
  return nameToReturn;
}

//ENCAPSULATING FUNCTION FOR GETTING A TEAM'S DATA
//ACCEPTS A RFID CARD'S ID, THEN DETERMINES TEAM NUMBER
//PRINTS OUT ALL TEAM INFORMATION
void RetrieveTeamInformation(byte cardID[])
{
  byte teamNumber = 0;
  //BASED OFF THE CARD ID, DETERMINE WHICH TEAM IS TRYING TO PLAY
  //TEMPORARY SYSTEM TILL TEAM CARD IDs ARE STORED ON THE SD CARD
  if( (cardID[0] == teamID_1[0]) &&
      (cardID[1] == teamID_1[1]) &&
      (cardID[2] == teamID_1[2]) &&
      (cardID[3] == teamID_1[3])    )
  {
    //TEAM THAT SCANNED IN IS TEAM 1
    teamNumber = 1;
  }
  else if(  cardID[0] == teamID_2[0] &&
            cardID[1] == teamID_2[1] &&
            cardID[2] == teamID_2[2] &&
            cardID[3] == teamID_2[3]    )
  {
    //TEAM 2 SCANNED IN
    teamNumber = 2;
  }
  else
  {
    Serial.println("No recognized team scanned in.");
  }

  //GET THE TEAM INFORMATION, IF A VALID TEAM SCANNED IN
  if(teamNumber != 0)
  {
    String teamColor = ReadSD_TeamColor(teamNumber);
    byte teamGoals = ReadSD_TeamGoals(teamNumber);
    String teamName = ReadSD_TeamName(teamNumber);

    //PRINT OUT THE DATA
    Serial.print("Team name: ");
    Serial.print(teamName);
    Serial.print("  |  Team Color: ");
    Serial.println(teamColor);
    Serial.print("Team Goal Count: ");
    Serial.println(teamGoals);
  }
}

//SETUP FUNCTION FOR THE PROGRAM
void setup() 
{
  //INITIALIZE SERIAL MONITOR
  Serial.begin(9600);

  //INITIALIZE SPI COMMUNICATION
  SPI.begin();

  //INITIALIZE RFID READER
  rfid.PCD_Init();
}

/*
 * MAIN LOOP FOR THE PROGRAM
 * 
 * PROGRAM FLOWS AS FOLLOWS:
 * -CHECK IF CARD IS DETECTED
 * -CHECK IF CARD IS SAME AS LAST DETECTION
 * -IF NEW CARD, PRINT OUT A TEAM'S INFORMATION BASED OFF CARD ID
 * -RESET RFID READER AND PREPARE TO LOOP
 */
void loop() 
{
  //START BY CHECKING IF A NEW RFID CARD IS PRESENT
  //THIS FLAG DOES NOT RECOGNIZE WHETHER THIS IS A DIFFERENT
  // CARD FROM THE LAST!
  bool newDetection = rfid.PICC_IsNewCardPresent();
  
  //IF NEW CARD, BEGIN PROCESS OF READING DATA
  if(newDetection == true)
  {
    //VERIFY THAT CARD DATA HAS BEEN READ
    bool cardRead = rfid.PICC_ReadCardSerial();

    //IF SUCCESSFUL, PRINT THE CARD ID
    //OTHERWISE, NOTIFY THE TERMINAL OF AN ERROR
    if(cardRead == true)
    {
      //CREATE FLAG FOR CARD ID COMPARISON
      bool isNewCard = false;

      //COMPARE PREVIOUS ID TO CURRENT ID, CHECK FOR SAME CARD
      for(byte counter = 0; counter < ID_SIZE; counter++)
      {
        if(rfid.uid.uidByte[counter] != lastID[counter])
        {
          //WHEN A DIFFERENCE IN I.D. IS FOUND, UPDATE FLAG
          isNewCard = true;
        }
      }

      //PRINT OUT RELEVANT CARD DATA WHEN NEW CARD IS FOUND
      if(isNewCard == true)
      {
        Serial.print("New card found. ID is: ");
        for(byte counter = 0; counter < ID_SIZE; counter++)
        {
          Serial.print(rfid.uid.uidByte[counter]);
          Serial.print(" ");
        }
        Serial.println("");

        //UPDATE STORED CARD ID TO PREVENT DUPLICATE CARD SCANS
        for(byte counter = 0; counter < ID_SIZE; counter++)
        {
          lastID[counter] = rfid.uid.uidByte[counter];
        }

        //PRINT OUT THE INFORMATION FOR A VALID TEAM
        RetrieveTeamInformation(rfid.uid.uidByte);
      }
      else
      {
        Serial.println("Previously scanned card found.");
      }
    }
    else
    {
      Serial.println("An error occured while reading the card.");
    }
    
    //STOP THE SCANNING PROCESS AND REFRESH READER FOR NEXT DETECTION
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}
