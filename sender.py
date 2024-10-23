import pika

# Configurações de conexão
url = 'amqps://ssukwgcy:VaAaWFMHdoQP2jfyPVNHw663D74OTzZP@jackal.rmq.cloudamqp.com/ssukwgcy'  # Substitua pelas suas credenciais
params = pika.URLParameters(url)
connection = pika.BlockingConnection(params)
channel = connection.channel()

# Declaração de uma fila
channel.queue_declare(queue='hello')

# Envia a mensagem
channel.basic_publish(exchange='', routing_key='hello', body='Hello World!')
print(" [x] Enviado 'Hello World!'")

# Fecha a conexão
connection.close()
