#include <SoftwareSerial.h>
#include <WiFiEsp.h>
#include <PubSubClient.h>

// Pinos de SoftwareSerial
SoftwareSerial espSerial(2, 3); // RX, TX

WiFiEspClient espClient;
PubSubClient client(espClient);

// Variáveis de rede e MQTT
const char* ssid = "nome_da_rede";
const char* password = "senha_da_rede";
const char* mqtt_server = "192.168.0.100"; // IP do seu PC com o broker MQTT

// Controle da garra
const int MCotovelo = 4;
const int MOmbro = 5;
const int MRotacao = 6;
const int MPulso = 7;
const int MMao = 8;

const int sinal = 9;
const int led = 10;

// Limite de tempo de ativação para cada motor (em milissegundos)
const unsigned int tempoCotovelo = 1000;
const unsigned int tempoOmbro = 1000;
const unsigned int tempoRotacao = 800;
const unsigned int tempoPulso = 500;
const unsigned int tempoMao = 300;

void setup() {
  Serial.begin(115200);
  espSerial.begin(9600); // Inicializa o SoftwareSerial para o ESP8266

  // Configura os pinos dos motores e periféricos como saída
  pinMode(MCotovelo, OUTPUT);
  pinMode(MOmbro, OUTPUT);
  pinMode(MRotacao, OUTPUT);
  pinMode(MPulso, OUTPUT);
  pinMode(MMao, OUTPUT);

  pinMode(sinal, OUTPUT); // Pino de controle ou sinal
  pinMode(led, OUTPUT);   // Pino do LED

  // Inicializa WiFi no ESP8266
  WiFi.init(&espSerial);
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("ESP8266 não encontrado!");
    while (true);
  }

  // Conectando ao WiFi
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  // Aguarda a conexão com o WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado ao WiFi!");

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

// Funções para controlar o movimento da garra
void moverCotovelo(bool paraCima) {
  digitalWrite(MCotovelo, HIGH);
  if (paraCima) {
    delay(tempoCotovelo); // Movimenta para cima por um tempo limitado
  } else {
    delay(tempoCotovelo); // Movimenta para baixo por um tempo limitado
  }
  digitalWrite(MCotovelo, LOW); // Para o movimento
}

void moverOmbro(bool paraFrente) {
  digitalWrite(MOmbro, HIGH);
  if (paraFrente) {
    delay(tempoOmbro); // Movimenta o ombro para frente
  } else {
    delay(tempoOmbro); // Movimenta o ombro para trás
  }
  digitalWrite(MOmbro, LOW);
}

void rotacionarGarra(bool sentidoHorario) {
  digitalWrite(MRotacao, HIGH);
  if (sentidoHorario) {
    delay(tempoRotacao); // Rotaciona a garra no sentido horário
  } else {
    delay(tempoRotacao); // Rotaciona a garra no sentido anti-horário
  }
  digitalWrite(MRotacao, LOW);
}

void moverPulso(bool paraCima) {
  digitalWrite(MPulso, HIGH);
  if (paraCima) {
    delay(tempoPulso); // Movimenta o pulso para cima
  } else {
    delay(tempoPulso); // Movimenta o pulso para baixo
  }
  digitalWrite(MPulso, LOW);
}

void abrirFecharMao(bool abrir) {
  digitalWrite(MMao, HIGH);
  if (abrir) {
    delay(tempoMao); // Abre a mão
  } else {
    delay(tempoMao); // Fecha a mão
  }
  digitalWrite(MMao, LOW);
}

// Callback que é chamada ao receber uma mensagem MQTT
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Mensagem no tópico: ");
  Serial.print(topic);
  Serial.print(". Mensagem: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    messageTemp += (char)message[i];
  }
  Serial.println(messageTemp);

  // Decodifica a mensagem recebida para controlar a garra
  if (messageTemp == "cotovelo_cima") {
    moverCotovelo(true);
  } else if (messageTemp == "cotovelo_baixo") {
    moverCotovelo(false);
  } else if (messageTemp == "ombro_frente") {
    moverOmbro(true);
  } else if (messageTemp == "ombro_tras") {
    moverOmbro(false);
  } else if (messageTemp == "rotacao_horario") {
    rotacionarGarra(true);
  } else if (messageTemp == "rotacao_antihorario") {
    rotacionarGarra(false);
  } else if (messageTemp == "pulso_cima") {
    moverPulso(true);
  } else if (messageTemp == "pulso_baixo") {
    moverPulso(false);
  } else if (messageTemp == "mao_abrir") {
    abrirFecharMao(true);
  } else if (messageTemp == "mao_fechar") {
    abrirFecharMao(false);
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando se reconectar ao MQTT...");
    if (client.connect("ESP8266Client")) {
      Serial.println("Conectado!");
      client.subscribe("garra/controle"); // Inscreve-se no tópico de controle da garra
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

void loop() {
  // Mantém a conexão MQTT e recebe novas mensagens
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); // Processa as mensagens MQTT e chama o callback se houver nova mensagem
}
