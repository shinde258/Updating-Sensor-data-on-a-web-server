#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "DEADSHOT"; //Enter Wi-Fi SSID
const char* password =  "Htauifg2632"; //Enter Wi-Fi Password

ESP8266WebServer server(80);   //instantiate server at port 80 (http port)

String page = "";
double data;
void setup(void) {

  pinMode(A0, INPUT);

  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password); //begin WiFi connection
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
  server.on("/", []() {
    page = "<h1>Sensor to Node MCU Web Server</h1><h3>Data:</h3> <h4>" + String(data) + "</h4>";
    server.send(200, "text/html", page);
  });

  server.begin();
  Serial.println("Web server started!");
}

void loop(void) {
  float data1 = analogRead(A0);
  data=100-((data1/1024)*100);  //percent
  if (data>=60)
  Serial.println("Soil is good");
  else
  Serial.println("Need to see water");
  delay(1000);
  server.handleClient();
}
