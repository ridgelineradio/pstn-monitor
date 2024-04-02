#include <SoftwareSerial.h>

SoftwareSerial cellSerial(7, 8);
String readingMessage;
String replyNumber;

void setup()
{
  Serial.begin(19200);
  cellSerial.begin(19200);
}

void loop()
{
  while(Serial.available()) 
  {
    cellSerial.write(Serial.read());
  }

  while (cellSerial.available()) 
  {
    String cmdRead = cellSerial.readString();
    cmdRead.trim();
    Serial.println(cmdRead);
    if (cmdRead.indexOf("RING") >= 0) // phone call incoming
    {
      Serial.println("Answering the call...");
      cellSerial.println("ATA");
    }
    else if (cmdRead.indexOf("CMTI") >= 0) // text message received
    {
      // Get the ID of the message
      int newlinePosition = cmdRead.indexOf('\r');
      if (newlinePosition < 0)
      {
        newlinePosition = cmdRead.length();
      }
      String lineMessage = cmdRead.substring(0, newlinePosition);
      readingMessage = lineMessage.substring(lineMessage.lastIndexOf(",") + 1);
      readingMessage.trim();
      Serial.println("Reading message ID: " + readingMessage);
      cellSerial.println("AT+CMGR=" + readingMessage);
    }
    else if (cmdRead.indexOf("CMGR") >= 0) // contents of the text message received
    {
      /*
      +CMGR: "REC UNREAD","+19705551234","","24/04/01,20:25:57-20"
      Let's try this now!

      OK*/

      // "+10001114444" length is 14 + 1 for index
      replyNumber = cmdRead.substring(cmdRead.indexOf(",") + 1, cmdRead.indexOf(",") + 15);
      Serial.println("Reply number is: " + replyNumber);

      // Delete the message
      cellSerial.println("AT+CMGD=" + readingMessage);
      delay(1000);
      while (cellSerial.available())
      {
        Serial.write(cellSerial.read());
      }

      readingMessage = "";

      // TODO: whitelist certain phone numbers?
      if (cmdRead.indexOf("Status") >= 0)
      {
        // Respond with some interesting facts.
        cellSerial.println("AT+CSQ");
      }
    }
    else if (cmdRead.indexOf("CSQ:") >= 0) // response from singal strength query
    {
      Serial.println("Responding with interesting facts");
      cellSerial.println("AT+CMGF=1");
      delay(1000);
      while (cellSerial.available())
      {
        Serial.write(cellSerial.read());
      }
      cellSerial.println("AT+CMGS=" + replyNumber);
      delay(1000);
      cellSerial.print("Signal strength: " + cmdRead);
      delay(1000);
      cellSerial.write(0x1a);
      Serial.println("Done sending the text to the cellular shield...");
    }
  }
}