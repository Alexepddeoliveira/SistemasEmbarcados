import paho.mqtt.client as mqtt

# Configuração MQTT para o broker online do Mosquitto
MQTT_BROKER = "test.mosquitto.org"  # Endereço do broker online
MQTT_PORT = 1883  # Porta padrão para conexão sem TLS
MQTT_TOPIC = "garra/controle"  # Tópico onde os dados da garra serão enviados

# Criar uma instância global do cliente MQTT para manter a conexão
client = None

# Função chamada quando o cliente se conecta ao broker
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print(f"Conectado ao broker MQTT {MQTT_BROKER} na porta {MQTT_PORT}")
    else:
        print(f"Falha ao conectar. Código de retorno: {rc}")

# Função chamada quando uma mensagem é publicada
def on_publish(client, userdata, mid):
    print(f"Mensagem publicada com sucesso. mid: {mid}")

# Função para conectar ao broker MQTT (somente uma vez)
def conectar_mqtt():
    global client
    if client is None:
        client = mqtt.Client()

        # Atribuir funções de callback
        client.on_connect = on_connect
        client.on_publish = on_publish

        try:
            # Conectar ao broker online
            client.connect(MQTT_BROKER, MQTT_PORT, 60)
            client.loop_start()  # Iniciar o loop para processar as mensagens em segundo plano
        except Exception as e:
            print(f"Erro ao conectar ao broker: {e}")
            return False
    
    return True

# Função para enviar dados via MQTT
def enviar_dados_mqtt(posicao_garra):
    """
    Função que envia os dados da posição da garra via MQTT.
    
    :param posicao_garra: Lista contendo [X, Y, Z, Estado da Mão]
    """
    if not conectar_mqtt():
        print("Não foi possível estabelecer a conexão MQTT.")
        return

    # Formatar a mensagem com os dados da garra
    payload = f"Posição alvo da garra: X={posicao_garra[0]:.2f}, Y={posicao_garra[1]:.2f}, Z={posicao_garra[2]:.2f}, Mão aberta: {posicao_garra[3]}"

    # Publicar no tópico MQTT
    result = client.publish(MQTT_TOPIC, payload)

    if result.rc == mqtt.MQTT_ERR_SUCCESS:
        print(f"Mensagem enviada: {payload}")
    else:
        print(f"Falha ao enviar mensagem. Código de retorno: {result.rc}")
