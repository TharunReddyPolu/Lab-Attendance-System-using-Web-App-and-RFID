#include <Wire.h>
#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`
SSD1306Wire  display(0x3c, D2, D1);  //D2=SDK  D1=SCK  As per labeling on NodeMCU

#include <SPI.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#define ERROR_PIN D0
#define SUCCESS_PIN D8

#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {{'1','2','3','4'}};

byte rowPins[ROWS] = {D7}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {D4, D3, D6, D5}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

const char *ssid = "realme 6"; //WIFI NAME OR HOTSPOT
const char *password = "harshavardhan"; //WIFI PASSWORD POR MOBILE HOTSPOT PASSWORD.
int count=0;
String input="";
void setup() {
   display.init();                   //setup display
   display.flipScreenVertically();
   display.setFont(ArialMT_Plain_10);
   delay(1000);
   WiFi.mode(WIFI_OFF);    
   delay(1000);
   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, password);
   pinMode(SUCCESS_PIN, OUTPUT);
   pinMode(ERROR_PIN, OUTPUT);
   /*Display wifi connecting status*/
   display.clear();
   display.setTextAlignment(TEXT_ALIGN_LEFT);
   display.setFont(ArialMT_Plain_16);
   display.drawString(0, 10, "Connecting...");
   display.display();
   delay(1000);
   display.clear();
   display.setTextAlignment(TEXT_ALIGN_LEFT);
   display.setFont(ArialMT_Plain_16);
   /*Display wifi name and IP address*/
   display.drawString(0, 0, "Connected to ");
   display.drawString(0, 16, String(ssid));
   display.drawString(0, 32, "IP address: ");
   display.display();
   delay(2000);
   SPI.begin();
   Serial.begin(9600);

}

void sendRfidLog(String cardid,char key_input)
{
  if(WiFi.status() == WL_CONNECTED)
  {
    if(key_input=='1') // if key pressed is 1 inert the record in time
    {
      HTTPClient http;
      String postData = "cardid=" + String(cardid) + "&action=insertinRecord";
      http.begin("http://192.168.43.157/RFIDandPHP/process.php");        
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");  
      int httpCode = http.POST(postData);
      String payload = http.getString();
      /*Displaying the http message payload*/
      display.clear();
      display.setTextAlignment(TEXT_ALIGN_LEFT);
      display.setFont(ArialMT_Plain_16);
      payload.toUpperCase();
      display.drawString(0, 20, "     "+String(payload));
      display.display();

      if(payload.equals("success"))
      {
       digitalWrite(SUCCESS_PIN, HIGH); //Glowing green led if http inserting is successful.
      } else
      {
       digitalWrite(ERROR_PIN, HIGH);  //Glowing red led if http inserting is not successful.
      }
      http.end();
    }
   else if(key_input=='2')
    {
      HTTPClient http;
      String postData = "cardid=" + String(cardid) + "&action=insertoutRecord";
     
      http.begin("http://192.168.43.157/RFIDandPHP/process.php");        
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");  
      int httpCode = http.POST(postData);
      String payload = http.getString();
      /*Displaying the http message payload*/
      display.clear();
      display.setTextAlignment(TEXT_ALIGN_LEFT);
      display.setFont(ArialMT_Plain_16);
      payload.toUpperCase();
      display.drawString(0, 20, "     "+String(payload));
      display.display();

      if(payload.equals("success"))
      {
       digitalWrite(SUCCESS_PIN, HIGH);  //Glowing green led if http inserting is successful.
      } else
      {
       digitalWrite(ERROR_PIN, HIGH);  //Glowing red led if http inserting is not successful.
      }
      http.end();
    }
   else if(key_input=='3')
    {
      HTTPClient http;
      String postData = "cardid=" + String(cardid) + "&action=checkRecord";
     
      http.begin("http://192.168.43.157/RFIDandPHP/process.php");        
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");  
      int httpCode = http.POST(postData);
      String payload = http.getString();
      /*Displaying the http message payload*/
      display.clear();
      display.setTextAlignment(TEXT_ALIGN_LEFT);
      display.setFont(ArialMT_Plain_16);
      payload.toUpperCase();
      display.drawString(0, 20, "     "+String(payload));
      display.display();
      Serial.println(String(payload));
      if(payload.equals("yes"))
      {
       digitalWrite(SUCCESS_PIN, HIGH); //Glowing green led if attendance is marked.
      } else
      {
       digitalWrite(ERROR_PIN, HIGH);  //Glowing red led if attendance is not marked.
      }
      http.end();
    }
  }
}

void serial_flush_buffer(){
  while (Serial.read() >= 0);
}

void loop() {
    /*Display select option menu*/
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 0, "SELECT OPTION");
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 20, "1>MARK IN ATTENDANCE");
    display.drawString(0, 36, "2>MARK OUT ATTENDANCE");
    display.drawString(0, 52, "3>CHECK ATTENDANCE");
    display.display();
    char key = keypad.getKey();// just print the pressed key
    /*Checking if key is pressed or not*/  
   if (key)
   {
    /*Display the selected key*/
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 10, "Key selected: "+String(key));
    /*Display the selected option using switch case*/    
    switch(key) {
     case '1'  :
        display.setFont(ArialMT_Plain_10);
        display.drawString(0, 36, "MARK IN ATTENDANCE");
        break;
   
     case '2'  :
        display.setFont(ArialMT_Plain_10);
        display.drawString(0, 36, "MARK OUT ATTENDANCE");
        break;
       
     case '3'  :
        display.setFont(ArialMT_Plain_10);
        display.drawString(0, 36, "CHECK ATTENDANCE");
        break;
    }
 
      display.display();
      delay(2000);
      /*flush the buffer storage from EM-18 module*/
      serial_flush_buffer();
      delay(1000);
      /*Display message -Place your id card*/
      display.clear();
      display.setTextAlignment(TEXT_ALIGN_LEFT);
      display.setFont(ArialMT_Plain_16);
      display.drawString(0, 10, "Place your card");
      display.display();

      while(1)
      {
        if(Serial.available())// Check if there is incoming data in the RFID Reader Serial Buffer.
        {
          input="";
          count = 0; // Reset the counter to zero
          /* Keep reading Byte by Byte from the Buffer till the RFID Reader Buffer is empty or till 12 Bytes (the ID size of our Tag) is read */
          for(count=0;count<11,Serial.available();count++)
          {
            /* Read 1 Byte of data and store it in the input[] variable*/
            input+=(char(Serial.read())); // Read 1 Byte of data and store it in the input[] variable
            delay(5);
          }
          sendRfidLog(input.substring(1),key);  // Calling function sendRfidLog
          delay (2000);
          digitalWrite(SUCCESS_PIN, LOW);
          digitalWrite(ERROR_PIN, LOW);
          if(count!=0) //if rfid is scanned break the loop.
          {
            break;
          }
        }
      }
    }
} 
