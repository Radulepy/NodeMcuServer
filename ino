/*
 * NODE MCU PIN MAPPING: (since they are different from Arduino)
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


 // LEDS (R,G,B) - PINS: (4, 0, 2);

#include <ESP8266WiFi.h>

  
String ledType1="secondary"; // this is for bootstrap, to make the buttons secondary/primary. (could be changed in future to disable / warning/etc).
String ledType2="secondary";
String ledType3="secondary";
String url="/BTN11";
String url2="/BTN21";
String url3="/BTN31";

const char* ssid = "WIFI_SSID"; //WiFi Credentials - USERNAME / PASSW / (OPTIONAL) IP (of the Node)
const char* password = "WIFI_PASS";
const char* host = "192.168.43.35"; //it will tell you the IP once it starts up (in the SERIAL MONITOR, CTRL+SHIFT+M)
                                        //just write it here afterwards and upload 192.168.0.183

int led1 = 4; // pin 4 = pin D2 on board
int led2 = 0; // D3
int led3 = 2; // D4


int serial=0;
int senzor=0;

WiFiServer server(80); //80 = port number

void setup() {

  pinMode(led1, OUTPUT); // outputs
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  digitalWrite(led1, LOW);// turn off all leds
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  
  Serial.begin(9600);
  delay(10);
  Serial.println(WiFi.localIP());


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

//------------------------------- FIRST LED
    if(ledType1 == "secondary") 
     {
       if (req.indexOf("/BTN11") != -1)
       {
          digitalWrite(led1, HIGH);
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
          digitalWrite(led1, LOW);
          delay(100);
          ledType1 = "secondary";
           Serial.println("BTN1-Primary");
           url="/BTN11";
        }
     }
//-----------------------------------SECOND LED
     if(ledType2 == "secondary") 
     {
       if (req.indexOf("/BTN21") != -1)
       {
          digitalWrite(led2, HIGH);
          delay(100);
          ledType2 = "primary";
           Serial.println("BTN2-Secondary");
           url2="/BTN20";
       }
     }
     if(ledType2 == "primary")
     {
        if (req.indexOf("/BTN20") != -1)
        {
          digitalWrite(led2, LOW);
          delay(100);
          ledType2 = "secondary";
           Serial.println("BTN2-Primary");
           url2="/BTN21";
        }
     }
//-----------------------------------THIRD LED

if(ledType3 == "secondary") 
     {
       if (req.indexOf("/BTN31") != -1)
       {
          digitalWrite(led3, HIGH);
          delay(100);
          ledType3 = "primary";
           Serial.println("BTN3-Secondary");
           url3="/BTN30";
       }
     }
     if(ledType3 == "primary")
     {
        if (req.indexOf("/BTN30") != -1)
        {
          digitalWrite(led3, LOW);
          delay(100);
          ledType3 = "secondary";
           Serial.println("BTN3-Primary");
           url3="/BTN31";
        }
     }
//---------------------------------------



     
    if (req.indexOf("/ON") != -1 || req.indexOf("/led1on") != -1 || req.indexOf("/led1_on") != -1 || req.indexOf("/led1%20on") != -1  ) { 
      digitalWrite(led1, HIGH);
      
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


// (!)THIS REDIRECTS USERS A PAGE BACK EVERY 3 SEC, BCS IF I'LL SIMPLY REFRESH THE PAGE IT WILL ALSO SIMULATE THE BUTTON PRESSED (IF PRESSED): <meta http-equiv = \"refresh\" content = \"3; url = /..\" />

// we put a \ before " to take the " in cosideration -> you can change this \" to only this '  (but not recommended)
  String d = "HTTP/1.1 200 OK\r\n";
  d+="Content-Type: text/html\r\n\r\n";
  d+="<!doctype html><html lang=\"en\">";
  d+="<head><meta http-equiv = \"refresh\" content = \"3; url = /..\" />"; // here goes a page back (see upper comm)
  d+="<meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width,user-scalable=no, initial-scale=1, shrink-to-fit=yes\">";
  d+="<link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css\" integrity=\"sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T\" crossorigin=\"anonymous\">";
  d+="</head>";
  d+="<body style=\"background-color:#D0D0D0;\">";
  d+="<h1 style=\"text-align:center;\">HOME SERVER</h1> <br>";
  d+="<font size='4'>";
  d+="<table class=\"table table-striped table-dark text-center\">";
  d+="<tr><th scope=\"col\" >PIN:</th> <th scope=\"col\">STATE:</th> <th scope=\"col\">CONTROLL:</th></tr>"; // TABLE TITLE
  d+="<tr> <th scope=\"row\"> 1 </th>"; 
  d+="<td>";
  d+=returnTypeString(ledType1);    //d+=" type "; // sensor 1 VALUE
  d+="</td>";
  d+="<td>";
    d+="<button type=\"button\" class=\"btn btn-"; d+=ledType1; d+=" btn-lg btn-block\" onclick=\"location.href='"; d+=url; d+="'\" > "; // the ledType1 is used to change button type (from blue -> black) using bootstrap
    d+=returnbuttonName(ledType1); // function that return a String name
    d+="</button>";
  d+="</td>";
  d+="</tr>";
  d+="<tr><th scope=\"row\"> 2 </th>";
  d+="<td>";
  d+=returnTypeString(ledType2);    // sensor 2 VALUE
  d+="</td>";
  d+="<td>";
  d+="<button type=\"button\" class=\"btn btn-"; d+=ledType2; d+=" btn-lg btn-block\" onclick=\"location.href='"; d+=url2; d+="'\" > "; // the ledType3 is used to change button type (from blue -> black) using bootstrap
    d+=returnbuttonName(ledType2); // function that return a String name
    d+="</button>";
   d+="</td>";
  d+="</tr>";
  d+="<tr><th scope=\"row\"> 3 </th>";
  d+="<td>";
  d+=returnTypeString(ledType3);    // sensor 3 VALUE
  d+="</td>";
  d+="<td>";
  d+="<button type=\"button\" class=\"btn btn-"; d+=ledType3; d+=" btn-lg btn-block\" onclick=\"location.href='"; d+=url3; d+="'\" > "; // the ledType2 is used to change button type (from blue -> black) using bootstrap
    d+=returnbuttonName(ledType3); // function that return a String name
    d+="</button>";
  d+="</td>";
  d+="</tr>";
  d+="</table>";
  d+="<font>";
  d+="</body>";
  d+="</html>";
 
  client.flush();

// starting only the main page:
client.print(d);

  delay(1);
 
// SENSORS *********************************************************************

  senzor = analogRead(0);
  //Serial.println(senzor, DEC); 
  delay(10);


  
} // END OF LOOP -----------------------------------------------

String returnbuttonName(String Name) //function that return string for the button name.
{
  if(Name == "primary")
    return "CLOSE LED";
  else 
    return "OPEN LED";
}

String returnTypeString (String Name) // this function transorms the name of the button and color,
{                         
  if(Name == "secondary")
    return "<font color=\"red\"> OFF </font>"; // will return a red "OFF" 
  else // is "primary"
     return "<font color=\"green\"> ON </font>"; // will return a green "ON"
}
// planuri:
// de facut un program pt pin-uri: porneste la ora aia, porneste cand e mai mic decat o val, etc...
