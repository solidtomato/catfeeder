#include "arduino_secrets.h"
/*
  WiFi Web Server LED Blink

 A simple web server that lets you blink an LED via the web.
 This sketch will print the IP address of your WiFi module (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to turn on and off the LED on pin 9.

 If the IP address of your board is yourAddress:
 http://yourAddress/H turns the LED on
 http://yourAddress/L turns it off

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 Circuit:
 * Board with NINA module (Arduino MKR WiFi 1010, MKR VIDOR 4000 and UNO WiFi Rev.2)
 * LED attached to pin 9

 created 25 Nov 2012
 by Tom Igoe
 */
#include <SPI.h>
#include <WiFiNINA.h>

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
WiFiServer server(80);

void setup() {
  Serial.begin(9600);      // initialize serial communication
  Serial.println("begin");
  pinMode(LED_BUILTIN, OUTPUT);      // set the LED pin mode

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  server.begin();                           // start the web server on port 80
  printWifiStatus();                        // you're connected now, so print out the status
}


void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            // client.println("Content-Type: application/json");
          // client.println("{ \"answer\": 42 }");
            // client.println();

            // the content of the HTTP response follows the header:
            // client.print("<input type=button value='LED_BUILTIN On' onclick='{location=\"/H\"}'>");
            // client.print("<input type=button value='LED_BUILTIN Off' onclick='{location=\"/L\"}'>");

            // The HTTP response ends with another blank line:
            client.println();    
            Serial.println("response sent");
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(LED_BUILTIN, 1);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(LED_BUILTIN, 0);                // GET /L turns the LED off
        }
        int turns = -1;
        if (currentLine.endsWith("GET /0")) turns = 0;
        else if (currentLine.endsWith("GET /1")) turns = 1;
        else if (currentLine.endsWith("GET /2")) turns = 2;
        else if (currentLine.endsWith("GET /3")) turns = 3;
        else if (currentLine.endsWith("GET /4")) turns = 4;
        else if (currentLine.endsWith("GET /5")) turns = 5;
        else if (currentLine.endsWith("GET /6")) turns = 6;
        else if (currentLine.endsWith("GET /7")) turns = 7;
        else if (currentLine.endsWith("GET /8")) turns = 8;
        else if (currentLine.endsWith("GET /9")) turns = 9;
        if (turns >= 0) {
          Serial.print("turns: ");
          Serial.println(turns);
          blinkLed(turns + 1);
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}

void blinkLed(int n) {
  digitalWrite(LED_BUILTIN, LOW);   
  delay(500);                        
    for (int i = 0; i < n; i++) {
        digitalWrite(LED_BUILTIN, HIGH);   // Turn the LED on
        delay(500);                        // Wait for half a second
        digitalWrite(LED_BUILTIN, LOW);    // Turn the LED off
        delay(500);                        // Wait for half a second
    }
}
