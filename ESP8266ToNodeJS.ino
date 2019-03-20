/*
 * HTTP Client POST Request
 * Copyright (c) 2018, circuits4you.com
 * All rights reserved.
 * https://circuits4you.com 
 * Connects to WiFi HotSpot. */
 
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
 
/* Set these to your desired credentials. */
const char *ssid = "CCRED";  //ENTER YOUR WIFI SETTINGS
const char *password = "CCredEnero2017";
 
//Web/Server address to read/write from 
const char *host = "10.2.1.36";   //https://circuits4you.com website or IP address of server
 
//=======================================================================
//                    Power on setup
//=======================================================================
 

void setup() {
  delay(1000);
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");
 
  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP

}

void loop() {
  HTTPClient http;    //Declare object of class HTTPClient
 
  String EspID, Usuario, Password, postData;
  boolean Gpio01, Gpio02, Gpio03, Gpio04;
  int adcvalue=analogRead(A0);  //Read Analog value of LDR
  EspID = "prueba123ESP";   //String to interger conversion
  Usuario = "DesdeElESP8266";
  Password = "123321";
  Gpio01 = true;
  Gpio02 = false;
  Gpio03 = true;
  Gpio04 = false;
  
 
  //Post Data
  postData = "esp8266_id=" + EspID + "&usuario=" + Usuario + "&password=" + Password + "&gpio01=" + Gpio01 + "&gpio02=" + Gpio02 + "&gpio03=" + Gpio03 + "&gpio04=" + Gpio04 ;
  
  http.begin("http://10.2.1.36:3000/api/esp8266");              //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
 
  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload
 
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload
 
  http.end();  //Close connection
  
  delay(20000);  //Post Data at every 50 seconds

}
