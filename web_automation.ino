#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char* ssid = "Joseph";
const char* password = "00000000";

String ledon = "on";
String ledoff = "off";


char homepage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
   <head>
      <meta name="viewport" content="width=device=width, initial-scale=1\">
      <title>WEB AUTOMATION</title>
      <style>
        html{font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; background-color: aqua;}
        body{margin-top: 50px;}
        h1{color: #444444; margin: 50px auto 30px;}
        h3{margin-bottom: 50px; color: #444444;}
        .button{background-color: green}
        footer{font-size: 15px; color: blue;}
      </style>
      <script>
        function onled1(){document.getElementById("redled").innerHTML="Led is On"};
        function onled2(){document.getElementById("greenled").innerHTML="Led is On"};
        function onled3(){document.getElementById("blueled").innerHTML="Led is On"};
        
        function offled1(){document.getElementById("redled").innerHTML=""};
        function offled2(){document.getElementById("greenled").innerHTML=""};
        function offled3(){document.getElementById("blueled").innerHTML=""};
      
      </script>
    </head>
  <body>
    <h1>Pasu Jay Web Automation </h1>
    <h3>This is An Automation Project</h3>
    <p>This is a simple esp32 project to control some devices via the web</P>
    <p>Turn on or off RED LED</p>
    <p id="redled"></p>
    <a href="/redledon"><button type="button" class="button button-on redclr" onclick="onled1()">ON</button></a>
    <a href="/redledoff"><button type="button" class="button button-off" onclick="offled1()">OFF</button></a>
    <p>Turn on or off GREEN LED</p>
    <p id="greenled"></p>
    <a href="/greenledon"><button type="button" class="button button-on greenclr" onclick="onled2()">ON</button></a>
    <a href="/greenledoff"><button type="button" class="button button-off" onclick="offled2()">OFF</button></a>
    <p>Turn on or off BLUE LED</p>
    <p id="blueled"></p>
    <a href="/blueledon"><button type="button" class="button button-on greenclr" onclick="onled3()">ON</button></a>
    <a href="/blueledoff"><button type="button" class="button button-off" onclick="offled3()">OFF</button></a>
    <br>
    <br>
    <br>
    <footer><B>AUTOMATION BY JOSEPH</B></footer>
  </body>
  </html>)=====";


WebServer server(80);

const int led =  2;
const int red =  12;
const int green =  13;
const int buzzermode =  14;
const int blue = 15;



void redon(){
    digitalWrite(red, HIGH);
    Serial.println("the red led is being turn on");
    server.send(200, "text/html", homepage);
    }
    
void greenon(){
    digitalWrite(green, HIGH);
    Serial.println("the green led is being turn on");
    server.send(200, "text/html", homepage);
    }

void blueon(){
    digitalWrite(blue, HIGH);
    Serial.println("the blue led is being turn on");
    server.send(200, "text/html", homepage);
    }

void redoff(){
    digitalWrite(red, LOW);
    Serial.println("the red led is being turned off");
    server.send(200, "text/html", homepage);
    }
    
void greenoff(){
    digitalWrite(green, LOW);
    Serial.println("the green led is being turned off");
    server.send(200, "text/html", homepage);
    }

void blueoff(){
    digitalWrite(blue, LOW);
    Serial.println("the blue led is being turned off");
    server.send(200, "text/html", homepage);
    }

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/html", homepage);
  digitalWrite(led, 0);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(buzzermode, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("webautomation")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/redledon", redon);
  server.on("/redledoff", redoff);
  server.on("/greenledon", greenon);
  server.on("/greenledoff", greenoff);
  server.on("/blueledon", blueon);
  server.on("/blueledoff", blueoff);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
