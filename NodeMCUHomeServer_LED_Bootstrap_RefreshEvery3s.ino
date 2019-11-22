/*
 * NODE MCU PIN MAPPING:
static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D2   = 4;
static const uint8_t D3   = 0;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;
static const uint8_t D9   = 3;
static const uint8_t D10  = 1;
 */

#include <ESP8266WiFi.h>

String ledType1="secondary";
String url="/BTN11";

const char* ssid = "MiLepy"; //WiFi Credentials - USERNAME / PASSW / (OPTIONAL) IP (of the Node)
const char* password = "123456789";
const char* host = "192.168.43.35"; //it will tell you the IP once it starts up
                                        //just write it here afterwards and upload 192.168.0.183
int ledPin = LED_BUILTIN; // D3
int led1 = 15; // led2 D5
int serial=0;
int senzor=0;

WiFiServer server(80); //just pick any port number you like

void setup() {
  Serial.begin(9600);
  delay(10);
Serial.println(WiFi.localIP());
  // prepare GPIO2
  pinMode(ledPin, OUTPUT);
  pinMode(led1, OUTPUT);
  digitalWrite(0, LOW); //D3
  digitalWrite(2, LOW); // D4

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  if(Serial.available() >0 )
    { serial=Serial.read();
      Serial.print(serial);
      Serial.println("XXX");
    }
  // Check if a client has connected
  
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  client.flush();

  // Match the request
  if (req.indexOf("") != -10) {  //checks if you're on the main page

   /* if (req.indexOf("/OFF") != -1 || req.indexOf("/led1off") != -1 || req.indexOf("/led1_off") != -1 || req.indexOf("/led1%20off") != -1  ) { 
      digitalWrite(ledPin, LOW);
      Serial.println("You clicked OFF");
    }
    */
    if(ledType1 == "secondary")
     {
       if (req.indexOf("/BTN11") != -1)
       {
          digitalWrite(ledPin, HIGH);
          delay(100);
          ledType1 = "primary";
           Serial.println("BTN1-Secondary");

           url="/BTN10";
           
       }
     }
     if(ledType1 == "primary")
     {
        if (req.indexOf("/BTN10") != -1)
        {
          digitalWrite(ledPin, LOW);
          delay(100);
          ledType1 = "secondary";
           Serial.println("BTN1-Primary");
           url="/BTN11";
        }
     }



     
    if (req.indexOf("/ON") != -1 || req.indexOf("/led1on") != -1 || req.indexOf("/led1_on") != -1 || req.indexOf("/led1%20on") != -1  ) { 
      digitalWrite(ledPin, HIGH);
      
      Serial.println("You clicked ON");
    }
    if (req.indexOf("/nu") != -1 || req.indexOf("/led2off") != -1 || req.indexOf("/led2_off") != -1 || req.indexOf("/led2%20off") != -1 ) { 
      digitalWrite(led1, LOW);
      Serial.println("You clicked OFF P2");
    }
    if (req.indexOf("/da") != -1 || req.indexOf("/led2on") != -1 || req.indexOf("/led2_on") != -1 || req.indexOf("/led2%20on") != -1 ) { 
      digitalWrite(led1, HIGH);
      Serial.println("You clicked ON P2");
    }
     
  }

  else {
    Serial.println("invalid request");
   client.stop();
    return;
  }

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n";
  s += "<body bgcolor=#c2a3a3>";
  s += "<p> LED 1 </p> <input type=\"button\" name=\"bl\" value=\"Turn LED ON \" onclick=\"location.href='/ON'\">" ;
  s += "&nbsp;&nbsp;&nbsp;<input type=\"button\" name=\"bl\" value=\"Turn LED OFF\" onclick=\"location.href='/OFF'\">";
  s += "<br><br>";
  s += "<p> LED 2 </p> <input type=\"button\" name=\"b2\" value=\"PIN 2 ON\" onclick=\"location.href='/da'\">";
  s += "&nbsp;&nbsp;&nbsp;<input type=\"button\" name=\"b2\" value=\"PIN 2 OFF\" onclick=\"location.href='/nu'\">";
  s += "<br><br>Ruleaza: <input type=\"text\" id=\"text1\" value="">";
  s += "&nbsp;&nbsp;<input type=\"button\" value=\"RUN\" onclick=location.href=document.getElementById(\"text1\").value>";
  s += "<br><br>";
  s += "<h2>Senzor Value (Analog 0 pin): ";
  s += senzor;
  s += " </h2>";
  s += "</body>";
  s += "</html>\n";

    String p = "HTTP/1.1 200 OK\r\n";
  p += "Content-Type: text/html\r\n\r\n";
  p += "<!DOCTYPE HTML>\r\n<html>\r\n";
  p += "<body bgcolor=#53c653>";
  p +=  "<p><h3> MOD: ADMINISTRATOR </h3></p>";
  p += "<p> LED 1 </p> <input type=\"button\" name=\"bl\" value=\"Turn LED ON \" onclick=\"location.href='/ON'\">" ;
  p += "&nbsp;&nbsp;&nbsp;<input type=\"button\" name=\"bl\" value=\"Turn LED OFF\" onclick=\"location.href='/OFF'\">";
  p += "<br>";
  p += "<p> LED 2 </p> <input type=\"button\" name=\"b2\" value=\"PIN 2 ON\" onclick=\"location.href='/da'\">";
  p += "&nbsp;&nbsp;&nbsp;<input type=\"button\" name=\"b2\" value=\"PIN 2 OFF\" onclick=\"location.href='/nu'\">";
  p += "<br>";
  p += "<p> LED 3 (OFF) </p> <input type=\"button\" name=\"bl\" value=\"Turn LED ON \" >" ;
  p += "&nbsp;&nbsp;&nbsp;<input type=\"button\" name=\"bl\" value=\"Turn LED OFF\" >";
  p += "<br>";
  p += "<p> LED 4 (OFF) </p> <input type=\"button\" name=\"bl\" value=\"Turn LED ON \" >" ;
  p += "&nbsp;&nbsp;&nbsp;<input type=\"button\" name=\"bl\" value=\"Turn LED OFF\" >";
  p += "<br>";
  p += "<p> LED 5 (OFF) </p> <input type=\"button\" name=\"bl\" value=\"Turn LED ON \" >" ;
  p += "&nbsp;&nbsp;&nbsp;<input type=\"button\" name=\"bl\" value=\"Turn LED OFF\" >";
  p += "<br>";
  p += "<p> REFRESH RATE : 5000 ms (5 sec) </p>";
  p += "<meta http-equiv=\"refresh\" content=\"5\" >";
  p += "<br><br>";
  p += "<h3> Valoare Senzori: </h3> <br>";
  p += "SENZOR 1: ";
  p += senzor;
  p += "<br> SENZOR 2: ";
  p += 0;
  p += "</body>";
  p += "</html>\n";

  
// THIS REDIRECTS USERS A PAGE BACK EVERY 3 SEC, BCS IF I'LL SIMPLY REFRESH THE PAGE IT WILL ALSO SIMULATE THE BUTTON PRESSED (IF PRESSED) <meta http-equiv = \"refresh\" content = \"3; url = /..\" />


  String d = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n <!doctype html><html lang=\"en\"><head><meta http-equiv = \"refresh\" content = \"3; url = /..\" /><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=yes\"><link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css\" integrity=\"sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T\" crossorigin=\"anonymous\"></head><body><h1 style=\"text-align:center;\">LED1</h1><button type=\"button\" class=\"btn btn-"; d+=ledType1; d+=" btn-lg btn-block\" onclick=\"location.href='"; d+=url; d+="'\" >";
  if(ledType1 == "primary")
    d+="OPEN LED 1";
  else
    d+="CLOSE LED 1";
  d+="</button></body></html>";
 
  client.flush();


  // Send the response to the client
  if(serial==0 || serial == 48)
  client.print(s);
  else
    if(serial==1 || serial ==49)
    client.print(p);
     else
   if(serial==2 || serial == 50)
    client.print(d);
  delay(1);
  
// ****************************************************************************

  senzor = analogRead(0);
  //Serial.println(senzor, DEC); 
  delay(10);

  
}
