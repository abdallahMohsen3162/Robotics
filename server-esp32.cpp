#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>
#include <WiFi.h>
Servo ser;
const char *ssid = "";//wifi name
const char *password = "";//wifi password

WiFiServer server(80);

String header;

String output2State = "right";

const int output2 = 2;

unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 500;

void setup()
{
  ser.attach(5);
  Serial.begin(115200);
  pinMode(output2, OUTPUT);
  digitalWrite(output2, LOW);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop()
{
  WiFiClient client = server.available(); // Listen for incoming clients

  if (client)
  { // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected() && currentTime - previousTime <= timeoutTime)
    {
      currentTime = millis();
      if (client.available())
      {
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n')
        {


          if (currentLine.length() == 0)
          {

            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            if (header.indexOf("GET /2/right") >= 0)
            { // Change to GPIO 2
              Serial.println("GPIO 2 right");
              output2State = "right";
              digitalWrite(output2, HIGH);
            }else if (header.indexOf("GET /2/left") >= 0)
            { // Change to GPIO 2
              Serial.println("GPIO 2 left");
              output2State = "left";
              digitalWrite(output2, LOW);
            }else if(header.indexOf("GET /2/stop") >= 0){
              Serial.println("GPIO 2 stop");
              output2State = "stop";
              digitalWrite(output2, HIGH);
            }else if(header.indexOf("GET /2/forward") >= 0){//forward
              Serial.println("GPIO 2 forward");
              output2State = "forward";
              digitalWrite(output2, HIGH);
              
            }

            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");

            client.println("<body><h1>ESP32 Web Server</h1>");

            client.println("<p>State " + output2State + "</p>");

            client.println("<p><a href=\"/2/right\"><button class=\"button\">-></button></a></p>");
            client.println("<p><a href=\"/2/left\"><button class=\"button\"><-</button></a></p>");
            client.println("<p><a href=\"/2/stop\"><button class=\"button\">stop</button></a></p>");
            client.println("<p><a href=\"/2/forward\"><button class=\"button\">forward</button></a></p>");
            

            client.println("</body></html>");

            client.println();
            break;
          }
          else
          {
            currentLine = "";
          }
        }
        else if (c != '\r')
        {                   // if you got anything else but a carriage return character,
          currentLine += c; // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
  if(output2State == "forward"){
    forward();
  }
}

void forward(){
  ser.write(0);
  delay(500);
  ser.write(90);
  delay(500);
}

