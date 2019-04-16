#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h> // Importa a Biblioteca PubSubClient

//MQTT definitions
#define TOPICO_SUBSCRIBE "ledStatus"   //listen channel
#define TOPICO_PUBLISH "controllerLog" //sender channel
#define ID_MQTT "controller1"
const char *BROKER_MQTT = "	m16.cloudmqtt.com"; //URL of MQTT broker
int BROKER_PORT = 10746;                        //MQTT Broker port"

//Global Objects and variables
WiFiClient espClient;         // create espClient object
PubSubClient MQTT(espClient); // create MQTT client object
char outputState = '0';       //stores current output state (could be changed to boolean)

//WiFi constants
const char *ssid = "ImWatchingYou";
const char *password = "99194213";

//Prototypes
void initMQTT();
void initWiFi();
void logMQTT();
void mqtt_callback(char *topic, byte *payload, unsigned int length);

void setup()
{
  // Start serial connection
  Serial.begin(9600);
  // Start IO ports
  pinMode(LED_BUILTIN, OUTPUT);
  //configure WiFi Connection
  initWiFi();
  //Configure MQTT
  initMQTT();
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  logMQTT();
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  // put your main code here, to run repeatedly:
}

void initWiFi()
{
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

void initMQTT()
{
  MQTT.setServer(BROKER_MQTT, BROKER_PORT); //informa qual broker e porta deve ser conectado
  MQTT.setCallback(mqtt_callback);          //atribui função de callback (função chamada quando qualquer informação de um dos tópicos subescritos chega)
  MQTT.connect()
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

  //obtem a string do payload recebido
  for (int i = 0; i < length; i++)
  {
    char c = (char)payload[i];
    msg += c;
  }

  //toma ação dependendo da string recebida:
  //verifica se deve colocar nivel alto de tensão na saída D0:
  //IMPORTANTE: o Led já contido na placa é acionado com lógica invertida (ou seja,
  //enviar HIGH para o output faz o Led apagar / enviar LOW faz o Led acender)
  if (msg.equals("L"))
  {
    digitalWrite(LED_BUILTIN, LOW);
    delay(5000);
  }

  //verifica se deve colocar nivel alto de tensão na saída D0:
  if (msg.equals("D"))
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(5000);
  }
}