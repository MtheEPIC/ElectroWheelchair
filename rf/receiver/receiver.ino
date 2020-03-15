#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;

void setup()
{
    Serial.begin(9600); // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    uint8_t buf[12];
    uint8_t buflen = sizeof(buf);
    char tmp;
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      int i;
      // Message with a good checksum received, dump it.
      tmp = buf[0];
//      Serial.print("Message: ");
//      Serial.println(tmp);        
      if(tmp=='B')
      {
        Serial.println("Going back");
      }
      else if(tmp=='F')
      {
        Serial.println("Going forwords");
      }
      else if(tmp=='R')
      {
        Serial.println("Going to right");
      }
      else if(tmp=='L')
      {
        Serial.println("Going to left");
      }
      else if(tmp=='S')
      {
        Serial.println("Stops");
      }
    }
}
