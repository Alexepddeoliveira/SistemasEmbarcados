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

  // Configura os pinos dos motores e periféricos como saída
  pinMode(MCotovelo, OUTPUT);
  pinMode(MOmbro, OUTPUT);
  pinMode(MRotacao, OUTPUT);
  pinMode(MPulso, OUTPUT);
  pinMode(MMao, OUTPUT);

  pinMode(sinal, OUTPUT); // Pino de controle ou sinal
  pinMode(led, OUTPUT);   // Pino do LED

  Serial.println("Pronto para receber comandos.");
}

void loop() {
  if (Serial.available()) {
    String comando = Serial.readStringUntil('\n');
    comando.trim(); // Remove espaços extras

    Serial.print("Recebido comando: ");
    Serial.println(comando);

    // Decodifica o comando recebido para controlar a garra
    if (comando == "cotovelo_cima") {
      moverCotovelo(true);
    } else if (comando == "cotovelo_baixo") {
      moverCotovelo(false);
    } else if (comando == "ombro_frente") {
      moverOmbro(true);
    } else if (comando == "ombro_tras") {
      moverOmbro(false);
    } else if (comando == "rotacao_horario") {
      rotacionarGarra(true);
    } else if (comando == "rotacao_antihorario") {
      rotacionarGarra(false);
    } else if (comando == "pulso_cima") {
      moverPulso(true);
    } else if (comando == "pulso_baixo") {
      moverPulso(false);
    } else if (comando == "mao_abrir") {
      abrirFecharMao(true);
    } else if (comando == "mao_fechar") {
      abrirFecharMao(false);
    } else {
      Serial.println("Comando desconhecido.");
    }
  }
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
