#include <Arduino.h>
#include <ESP8266WiFi.h>

const char *ssid = "Trevisan";
const char *password = "99194213";

void setup()
{
  // Start serial connection
  Serial.begin(9600);
  // Start IO ports
  pinMode(LED_BUILTIN, OUTPUT);
  //configure WiFi Connection
  Serial.println("");
  Serial.print("Trying to connect to: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected with ip: ");
  Serial.print(WiFi.localIP());
  Serial.println("");
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  // put your main code here, to run repeatedly:
}