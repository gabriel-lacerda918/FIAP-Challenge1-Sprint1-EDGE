# Sistema de sensoriamento de carros - Fórmula E

![Technologies](https://img.shields.io/badge/Arduino-Uno-blue) ![Technologies](https://img.shields.io/badge/Language-C++-brightgreen) ![Technologies](https://img.shields.io/badge/Simulator-Tinkercad-orange)

## Projeto

Este projeto simula um sistema de sensores para um carro de corrida de Formula E utilizando como protótipo um sistema baseado no controle a partir de um Arduino Uno. O sistema lê dados de sensores de temperatura, umidade, e luminosidade, controla um servo motor, e utiliza um LED para alertas problemas. A simulação é realizada via <a href="https://www.tinkercad.com/" target="_blank"> Tinkercad.</a>

## Componentes Utilizados

- **Arduino Uno**
- **Sensor de Temperatura TMP36** (Temperatura do cockpit)
- **Sensor de Temperatura TMP36** (Temperatura dos pneus)
- **Potenciômetro** (Simular Leitura de umidade)
- **Sensor de Luminosidade (LDR com resistor de pull-down)**
- **Servo Motor**
- **LED**

## Imagem do Circuito Simulado
![Circuito-TinkerCad](https://github.com/gabriel-lacerda918/FIAP-Challenge1-Sprint1-EDGE/assets/161903643/f2797ce9-ff4f-4ec7-820b-9f3cd0745288)

<a href="https://www.tinkercad.com/things/9xBMJEK323j-challenge1-sprint1-edge?sharecode=zMt9DEdOuqW8SeCp_UdwNkqQrzVewSrc2efRNhLq834" target="_blank">Link para visuação do projeto - Tinkercad</a>



## Funcionamento do Sistema

O sistema lê dados dos sensores para monitorar as condições do cockpit e dos pneus de um carro de Formula E. Baseado nas leituras de temperatura, umidade e luminosidade, o servo motor ajusta sua velocidade para simular o comportamento do carro em diferentes condições. Se qualquer leitura estiver fora dos parâmetros ideais, a velocidade do motor é reduzida e um LED é aceso para indicar um problema.

### Condições Ideais

- **Temperatura do Cockpit:** até 60°C
- **Temperatura dos Pneus:** entre 80°C e 100°C
- **Umidade:** entre 35% e 60%
- **Intensidade de Luz:** Alta (Acima de 60%)

### Controle do Servo Motor

- **Velocidade Máxima:** 320 km/h (quando todas as condições são ideais)
- **Redução de Velocidade:** 10% para cada condição fora do ideal

## Explicação do Código

O código lê os valores dos sensores e converte esses valores para unidades significativas. Em seguida, verifica se as leituras estão dentro dos limites ideais e ajusta a velocidade do servo motor de acordo. A velocidade do servo é mapeada para um valor entre 0 e 320 km/h e exibida no Monitor Serial. Se alguma condição estiver fora dos limites, o LED é aceso e a velocidade do servo é reduzida.

### Código
**Pinagem Sensores/atuadores**
```cpp
const int cockpitTempSensorPin = A0;  // Pino do sensor de temperatura do cockpit
const int tireTempSensorPin = A3;  // Pino do sensor de temperatura dos pneus
const int humiditySensorPin = A1;  // Pino do potenciômetro que simula o sensor de umidade
const int lightSensorPin = A2;  // Pino do sensor de luminosidade
const int servoPin = 9;  // Pino do servo motor
const int ledPin = 13;  // Pino do LED
```
<br> **Definição de entradas e saídas**
  ```cpp
  pinMode(cockpitTempSensorPin, INPUT);
  pinMode(tireTempSensorPin, INPUT);
  pinMode(humiditySensorPin, INPUT);
  pinMode(lightSensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
```
  
<br> **Variáveis de leitura**
```cpp
void loop() {
  int cockpitTempValue = analogRead(cockpitTempSensorPin);
  int tireTempValue = analogRead(tireTempSensorPin);
  int humidityValue = analogRead(humiditySensorPin);
  int lightValue = analogRead(lightSensorPin);
``` 
  <br> **Requisitos de controle**
```cpp
  bool conditionsMet = true;
  int nonIdealConditions = 0;
  if (cockpitTemperature > 60) {
    conditionsMet = false;
    nonIdealConditions++;
  }
  if (tireTemperature < 80 || tireTemperature > 100) {
    conditionsMet = false;
    nonIdealConditions++;
  }
  if (humidity < 35 || humidity > 60) {
    conditionsMet = false;
    nonIdealConditions++;
  }
  if (lightIntensity < 0 || lightIntensity > 20) { // Assuming light sensor gives a percentage
    conditionsMet = false;
    nonIdealConditions++;
  }
```
<br> **Controle e cálculo de velocidade do motor**
```cpp
  int servoSpeed = 180; // Velocidade máxima
  if (!conditionsMet) {
    servoSpeed -= nonIdealConditions * 18; // Reduz 10% da velocidade máxima para cada condição não ideal (18 de 180 é 10%)
    digitalWrite(ledPin, HIGH); // Acende o LED indicando problema
  } else {
    digitalWrite(ledPin, LOW); // Apaga o LED indicando que todas as condições são ideais
  }

  // Calculando a velocidade máxima do motor em km/h
  int maxSpeedKmh = map(servoSpeed, 0, 180, 0, 320);
```
<br>**Exibição de leituras**
```cpp
  Serial.print("Cockpit Temperature: ");
  Serial.print(cockpitTemperature);
  Serial.print(" C, Tire Temperature: ");
  Serial.print(tireTemperature);
  Serial.print(" C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Light Intensity: ");
  Serial.print(lightIntensity);
  Serial.println(" %");
  Serial.print("Max Motor Speed: ");
  Serial.print(maxSpeedKmh);
  Serial.println(" km/h");
  ```

## Autor(es)

Este projeto foi desenvolvido por:
- Gabriel Machado Lacerda                RM:556714
- João Pedro Signor Avelar               RM:558375
- Roger Cardoso Ferreira                 RM:557230
- Vinicius Augusto Siqueira Gonçalves    RM:557065
- TURMA: 1ESPW
