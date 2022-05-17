#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

//const char *ssid     = "taketo";
//const char *password = "rbc_electron";

const char *ssid     = "ignas";
const char *password = "theeconclass";

const char* host = "192.168.137.241";


// Defining NTP Client to get time



void setup(){
 
pinMode(LED_BUILTIN, OUTPUT);
Serial.begin(115200);
WiFi.begin(ssid, password);

}






void loop() {
    isit_connected();
    server_connect();
  
      delay(3000);
}

void server_connect(){
  
WiFiClient client;
const int httpPort = 8000;

if (!client.connect(host, httpPort)) {
    Serial.println("Server-bike connection successfully established");
    return;}


String esp_address=WiFi.macAddress();
String url = "/amIClaimed?m="+esp_address;

Serial.print("Requesting URL: ");
Serial.println(url+"\n\n");

client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
unsigned long timeout = millis();

while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }}

// Read all the lines from the server answer
while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

// Close connecting
Serial.println();
Serial.println("closing connection");
}

bool isit_connected(){
  if(WiFi.status() == WL_CONNECTED){
     Serial.println("Server-bike connection successfully established");
      Serial.println(WiFi.macAddress());
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("WiFi connected");
      delay(1000);
      return true;}
      
    else{
      blinks();
      Serial.print("."); 
      return false;}
}

 void blinks(){
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100);   
 }
