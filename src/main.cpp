#include "WiFi.h"
#include "SPIFFS.h"
#include "ESPAsyncWebServer.h"
#include "FS.h" 
 
const char* ssid = "Kamera-Slider";
const char* password =  "123456789";

#define LED 2 
 
AsyncWebServer server(80);
 
void setup(){
  Serial.begin(115200);
 
  if(!SPIFFS.begin()){
     Serial.println("An Error has occurred while mounting SPIFFS");
     return;
  }
 
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);
 
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
 
  Serial.println(WiFi.localIP());
 
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });
 
 * server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.css", "text/css");
  });

  server.on("/test.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/test.js", "text/javascript");
});

  Serial.println("ServerBeginn");
 
  server.begin();

  Serial.println("ServerBEginnDonE");
}
 
void loop(){

  //Laptop TestEdit

  


}

void handleLED() { //Fake LED
 String ledState = "OFF";
 String t_state = server.argv("LEDstate"); //Refer  xhttp.open("GET", "setLED?LEDstate="+led, true);
 Serial.println(t_state);
 if(t_state == "1")
 {
  digitalWrite(LED,LOW); //LED ON
  ledState = "ON"; //Feedback parameter
 }
 else
 {
  digitalWrite(LED,HIGH); //LED OFF
  ledState = "OFF"; //Feedback parameter  
 }
 
 server.send(200, "text/plane", ledState); //Send web page
}