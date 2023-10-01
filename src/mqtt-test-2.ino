// This #include statement was automatically added by the Particle IDE.
#include "MQTT.h"



// Server information
//const char* mqttServer = "https://153.104.61.218";
//const char* mqttServer = "152.104.61.218";
uint8_t mqttServer[] = {152, 104, 61, 218};
uint16_t mqttPort = 1883;
const char* mqttUsername = "ece2431";
const char* mqttPassword = "villaNova";
const char* clientId = "photon60_iqiyjvaja";
void callback(char* topic, byte* payload, unsigned int length);

// Calling server using MQTT protocol and TCP protocol
MQTT MQTTclient(mqttServer, mqttPort, callback);
IPAddress IPServer(mqttServer);
TCPClient TCPclient;

// This function is called when a message is received
void callback(char* topic, byte* payload, unsigned int length) {
    char msg[length + 1];
    memcpy(msg, payload, length);
    msg[length] = '\0';
    Serial.print("Received a message on topic: ");
    Serial.print(topic);
    Serial.print(". Message: ");
    Serial.println(msg);
}

void setup() {
    Serial.begin(9600);

    // Connect to Wi-Fi
    //  WiFi.begin(ssid, password);                                    Wifi credentials already in this Photon
    while (WiFi.connecting()) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    // Connect to the MQTT broker using MQTT
    if (MQTTclient.connect(clientId, mqttUsername, mqttPassword)) {
        Serial.println("Connected to MQTT Broker");
        MQTTclient.subscribe("test/topic");
    } else {
        Serial.println("Failed to connect to MQTT Broker");
    }

    // Connect to the MQTT broker using TCPClient
    if (TCPclient.connect(mqttServer, mqttPort))
    {
      Serial.println("connected");
      TCPclient.println();
    }
    else
    {
      Serial.println("connection failed");
    }
}

void loop() {
}