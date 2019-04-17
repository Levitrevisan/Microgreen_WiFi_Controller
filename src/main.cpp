#include <Arduino.h>
#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
#include <PubSubClient.h> // Importa a Biblioteca PubSubClient
#include <DS1307.h>

//MQTT definitions
#define TOPICO_SUBSCRIBE "ledStatus"   //listen channel
#define TOPICO_PUBLISH "controllerLog" //sender channel
#define ID_MQTT "controller1"
const char *BROKER_MQTT = "m16.cloudmqtt.com"; //URL of MQTT broker
int BROKER_PORT = 10746;                       //MQTT Broker port

//Global Objects and variables
WiFiClient espClient;         // create espClient object
PubSubClient MQTT(espClient); // create MQTT client object
char outputState = '0';       //stores current output state (could be changed to boolean)
DS1307 rtc(D1, D2);

//WiFi constants
const char *ssid = "ImWatchingYou";
const char *password = "99194213";

//MQTT constants
const char *mqtt_username = "paiqlirh";
const char *mqtt_password = "V4ig-DwmZsCA";

// Debug Variables
bool blinkOrNot = true;

//Prototypes
void initMQTT();
void initWiFi();
void initRTC();
void logMQTT();

void mqtt_callback(char *topic, byte *payload, unsigned int length);

void setup()
{
  // Start serial connection
  Serial.begin(9600);
  // Start IO ports
  pinMode(LED_BUILTIN, OUTPUT);
  // Start RTC Module
  initRTC();
  //configure WiFi Connection
  initWiFi();
  //Configure MQTT
  initMQTT();
}

void loop()
{
  if (blinkOrNot)
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  delay(1000);
  logMQTT();
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  // put your main code here, to run repeatedly:
}

void initWiFi()
{
  Serial.println("");
  Serial.print("       Trying to connect to: ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("[ OK ] Connected with ip: ");
  Serial.print(WiFi.localIP());
  Serial.println("");
}

void initMQTT()
{
  MQTT.setServer(BROKER_MQTT, BROKER_PORT); //informa qual broker e porta deve ser conectado
  MQTT.setCallback(mqtt_callback);          //atribui função de callback (função chamada quando qualquer informação de um dos tópicos subescritos chega)
  while (!MQTT.connected())
  {
    if (MQTT.connect(ID_MQTT, mqtt_username, mqtt_password))
    {
      Serial.println("[ OK ] MQTT conection estabilished");
    }
    else
    {
      Serial.print("");
      Serial.print("[FAIL] MQTT connection error : ");
      Serial.print(MQTT.state());
      Serial.println("");
      delay(2000);
    }
  }
}

void logMQTT()
{
  MQTT.publish(TOPICO_PUBLISH, "Sent Message");
}

//Função: função de callback
//        esta função é chamada toda vez que uma informação de
//        um dos tópicos subescritos chega)
//Parâmetros: nenhum
//Retorno: nenhum
void mqtt_callback(char *topic, byte *payload, unsigned int length)
{
  String msg;

  for (int i = 0; i < length; i++)
  {
    char c = (char)payload[i];
    msg += c;
  }

  Serial.println("");
  Serial.print("[ OK ] Message received: ");
  Serial.print(msg);
  Serial.println("");

  //IMPORTANTE: o Led já contido na placa é acionado com lógica invertida (ou seja,
  //enviar HIGH para o output faz o Led apagar / enviar LOW faz o Led acender)
  if (msg.equals("L"))
  {
    blinkOrNot = true;
    delay(5000);
  }

  if (msg.equals("D"))
  {
    blinkOrNot = false;
    delay(5000);
  }
}

void initRTC()
{
  rtc.halt(false);
  rtc.setDOW(FRIDAY);
  rtc.setTime(10, 40, 0);
  rtc.setDate(17, 04, 2019);
  //Definitions of SQW/Out pin
  rtc.setSQWRate(SQW_RATE_1);
  rtc.enableSQW(true);

  if (strcmp(rtc.getDOWStr(), "xxxxxxxxx") == 0)
  {
    Serial.print("[FAIL] RTC is not working, check");
  }
  else
  {
    Serial.print("[ OK ] RTC working");
  }
}

