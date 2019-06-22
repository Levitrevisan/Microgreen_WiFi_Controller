#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
#include "credentials.h"

//MQTT definitions
#define TOPIC_SUBSCRIBE "ledStatus"    //listen channel
#define TOPIC_TEMPERATURE "temperature"
#define TOPICO_PUBLISH "controllerLog" //sender channel
#define ID_MQTT "controller1"
const char *BROKER_MQTT = "m16.cloudmqtt.com"; //URL of MQTT broker
int BROKER_PORT = 10746;                       //MQTT Broker port

//Global Objects and variables
WiFiClient espClient;         // create espClient object
PubSubClient MQTT(espClient); // create MQTT client object
char outputState = '0';       // stores current output state (could be changed to boolean)

//WiFi constants
const char *ssid = wifiSSID;
const char *password = wifiPassword;

//MQTT constants
const char *mqtt_username = MQTTUsername;
const char *mqtt_password = MQTTPassword;

//DHT sensor definitions
DHT dht;

// Debug Variables
bool blinkOrNot = true;
int sleepTime = 10000;

//Prototypes
void initMQTT();
void initWiFi();

void mqtt_callback(char *topic, byte *payload, unsigned int length);

void setup()
{
  // Start serial connection
  Serial.begin(9600);
  // Start IO ports
  pinMode(LED_BUILTIN, OUTPUT);

  //set DHT on pin D1
  dht.setup(D1);

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
  
  delay(dht.getMinimumSamplingPeriod());
  String buf;
  buf = String(dht.getTemperature(),2);
  char buf2[5];
  buf.toCharArray(buf2,5);

  MQTT.publish(TOPIC_TEMPERATURE,buf2);

  MQTT.publish(TOPIC_SUBSCRIBE, "LED IS OFF");
  delay(sleepTime);
  digitalWrite(LED_BUILTIN, LOW);
  MQTT.publish(TOPIC_SUBSCRIBE, "LED IS ON");
  delay(sleepTime);
}

void initWiFi()
{
  Serial.println("");
  Serial.println("[ OK ] Starting microgreen controller");
  Serial.println("       Trying to connect to: ");
  Serial.print("       ");
  Serial.print(ssid);
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
