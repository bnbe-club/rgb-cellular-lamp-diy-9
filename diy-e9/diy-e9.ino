/*************************************************************************************************************************************************
 *  TITLE: WiFi RGB Cellular Lamp Using The Wemos D1 Mini (ESP8266)
 *  We build a beautiful RGB cellular lamp that can be controlled over WiFi. 
 *  The control page consists of a color wheel which allows you to quickly change colours and you can also specify the RGB values directly to 
 *  create a total of over 16 million color combinations. 
 *
 *  By Frenoy Osburn
 *  YouTube Video: https://youtu.be/42MOMQeRjXM
 *  BnBe Post: https://www.bitsnblobs.com/wifi-rgb-cellular-lamp---esp8266
 *************************************************************************************************************************************************/

  /********************************************************************************************************************
 *  Board Settings:
 *  Board: "WeMos D1 R1 or Mini"
 *  Upload Speed: "921600"
 *  CPU Frequency: "80MHz"
 *  Flash Size: "4MB (FS:@MB OTA:~1019KB)"
 *  Debug Port: "Disabled"
 *  Debug Level: "None"
 *  VTables: "Flash"
 *  IwIP Variant: "v2 Lower Memory"
 *  Exception: "Legacy (new can return nullptr)"
 *  Erase Flash: "Only Sketch"
 *  SSL Support: "All SSL ciphers (most compatible)"
 *  COM Port: Depends *On Your System*
 *********************************************************************************************************************/
// Basic RGB lamp using WS2812 controlled by a ESP8266-01
// (C) Jean-Marie Bussat - Creative Commons Attribution 4.0 International Public License
#include "ESP8266WiFi.h"
#include <ESP8266WebServer.h>
#include "html_header.h"
#include <Adafruit_NeoPixel.h>

// Classic web server on port 80
ESP8266WebServer server(80);

#define NUM_PIX 26

const char* ssid     = "Network";
const char* password = "Password";
unsigned char red,green,blue;
String form;

// Number of pixels, pin used to control
// NEO_KHZ800 because we are using WS2812 leds
// NEO_GRB because WS2812 wants pixel data in GRB order
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIX, 0, NEO_GRB + NEO_KHZ800);

// Root handler: basic web page with link to settings page
void handle_root() {
  server.send(200, "text/html", "<html>WS2812 WiFi <a href='./out'>Control</a></html>");
  delay(100);
}

// Output handler: display colorwheel and allow picking a color
void handle_outputs() {
  // Strings to strore the client output
  String RMsg;
  String GMsg;
  String BMsg;

  // Parse client output
  RMsg=server.arg("R");
  GMsg=server.arg("G"); 
  BMsg=server.arg("B");

  // Convert to number to pass to Neopixel library
  red=RMsg.toInt();
  green=GMsg.toInt(); 
  blue=BMsg.toInt();  

  // Update the form and send it back to the client
  form = "<html>";
  form = form + html_header;
  form = form + "</html>";
  // Send the form
  server.send(200, "text/html", form);
}

// Initialize WiFi, web server and handles
void setup() {

  Serial.begin(115200);
  // Connect to network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  //Print out the IP address
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  // Default setting for RGB string: dim white
  red=255;
  green=103;
  blue=23;
  
  // Attach handles to web server
  // Base page
  server.on("/", handle_root);
  // Setting page
  server.on("/out", handle_outputs);
  // Start web server
  server.begin();
  // Initialize Neopixel 
  pixels.begin();
  pixels.setBrightness(255);
}

void loop() {
  int i;
  
  // Process clients requests
  server.handleClient(); 

  // Update the LED string. All LED have same color
  for(i=0;i<NUM_PIX;i++){
    // RGB
    pixels.setPixelColor(i, pixels.Color(red,green,blue));
    pixels.show();
  }
  delay(500);    // Wait a little before trying again
}
