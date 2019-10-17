#include "WiFi.h"
#include "SPIFFS.h"
#include "ESPAsyncWebServer.h"
 
const char* ssid = "Kamera-Slider";
const char* password =  "123456789";
 
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
 
  server.on("/dashboard", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/dashboard.html", "text/html");
  });
 
  server.on("/dashboard.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/dashboard.css", "text/css");
  });

  Serial.println("ServerBeginn");
 
  server.begin();

  Serial.println("ServerBEginnDonE");
}
 
void loop(){

  //Laptop TestEdit

  


}