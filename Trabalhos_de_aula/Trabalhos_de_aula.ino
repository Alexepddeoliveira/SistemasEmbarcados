#include <WiFi.h>
#include <PubSubClient.h>

// Defina os parâmetros de Wi-Fi
const char* ssid = "WIFIZONEEe";
const char* password = "SISTEMASEMBARCADOS";

// Parâmetros do Broker MQTT
const char* mqtt_server = "Test.Mosquitto.org";
const char* mqtt_topic = "IBMEC";

WiFiClient espClient;
PubSubClient client(espClient);

// Função para conectar ao Wi-Fi
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando-se a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

// Callback que será chamada quando uma mensagem MQTT for recebida
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida no tópico: ");
  Serial.print(topic);
  Serial.print(". Mensagem: ");
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);
}

// Função para se conectar ao Broker MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conectar ao broker MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Conectado!");
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("Falha ao conectar, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);  // Porta padrão MQTT: 1883
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Publica uma mensagem a cada 5 segundos
  static unsigned long lastMsg = 0;
  unsigned long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    String message = "Olá MQTT";
    Serial.print("Enviando mensagem: ");
    Serial.println(message);
    client.publish(mqtt_topic, message.c_str());
  }
}
