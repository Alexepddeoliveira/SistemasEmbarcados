# SistemasEmbarcados
Repositorio para a diciplina de sistemas embarcados e internets das coisas 

# 5W2H - Projeto da Garra Controlada por Movimentos

## 1. What (O quê)
**Objetivo:** 
Desenvolver uma ferramenta que possa ser utilizada para realizar operações finas de alto risco à distância, garantindo a segurança do operador.

## 2. Why (Por quê)
**Motivação:** 
Trazer uma nova tecnologia de segurança para operações que exigem precisão e são de alto risco, protegendo o operador de possíveis perigos.

## 3. Who (Quem)
**Equipe de Desenvolvimento:**
- Alex
- Victor
- Luiza

**Usuários Finais:** 
Médicos, cientistas, policiais e militares que necessitam de precisão e segurança em operações arriscadas.

## 4. Where (Onde)
**Local de Desenvolvimento e Uso:** 
O sistema será desenvolvido utilizando Python e Arduino Uno, com a montagem realizada nas instalações da faculdade.

## 5. When (Quando)
**Cronograma:** 
O projeto deve ser finalizado até o final do período acadêmico.

## 6. How (Como)
**Metodologia de Desenvolvimento:** 
O sistema será desenvolvido em três etapas simultâneas:
- **Montagem do Hardware:** Construção da garra e integração com os motores e sensores.
- **Desenvolvimento do Código do Arduino:** Programação do Arduino para controlar a garra via MQTT.
- **Desenvolvimento da Ferramenta de Detecção em Python:** Criação do sistema de detecção de movimentos da mão que enviará comandos ao Arduino.

## 7. How Much (Quanto)
**Recursos:** 
O projeto utilizará apenas o tempo dos estudantes envolvidos e os materiais disponibilizados pela faculdade.

# Requisitos do Projeto - Garra Controlada por Movimentos

## **Requisitos Funcionais**

1. **Controle da Garra:**
   - A garra deve abrir, fechar e se mover conforme os comandos recebidos via MQTT.

2. **Detecção de Movimentos:**
   - O sistema Python deve detectar os movimentos da mão em tempo real e enviar comandos para o Arduino.

3. **Comunicação via MQTT:**
   - O Arduino deve receber e executar os comandos enviados pelo sistema Python através de MQTT.

4. **Controle de Motores:**
   - O Arduino deve controlar os motores da garra de acordo com os comandos recebidos.

5. **Feedback Visual:**
   - O sistema deve fornecer um feedback visual simples sobre a detecção de movimentos e o status da garra.

## **Requisitos Não Funcionais**

1. **Desempenho:**
   - O sistema deve operar em tempo real com latência mínima.

2. **Confiabilidade:**
   - O sistema deve ser estável e funcionar de maneira consistente.

3. **Escalabilidade:**
   - Deve ser fácil adicionar mais componentes (motores/sensores) no futuro.

4. **Segurança:**
   - O sistema deve garantir que a garra opere de forma segura, evitando movimentos perigosos.

5. **Facilidade de Uso:**
   - A interface deve ser intuitiva e fácil de usar.

6. **Portabilidade:**
   - O sistema deve funcionar em diferentes plataformas (Windows, macOS, Linux).

7. **Documentação:**
   - O projeto deve incluir documentação básica para configuração e operação.


