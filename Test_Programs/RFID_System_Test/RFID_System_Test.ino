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

//CREATE STORAGE FOR THE CARD'S ID NUMBER
byte currentID[ID_SIZE];        //for current card's ID
byte lastID[ID_SIZE];           //the ID of the card last loop


uint8_t ReadSD_TeamColor(byte teamNum)
{
  return 0;
}
uint8_t ReadSD_TeamGoals(byte teamNum)
{
  return 0;
}
String ReadSD_TeamName(byte teamNum)
{
  return "Null";
}

void RetrieveTeamInformation(byte cardID[])
{
  
}

void setup() 
{
  //INITIALIZE SERIAL MONITOR
  Serial.begin(9600);

  //INITIALIZE SPI COMMUNICATION
  SPI.begin();

  //INITIALIZE RFID READER
  rfid.PCD_Init();
}

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
