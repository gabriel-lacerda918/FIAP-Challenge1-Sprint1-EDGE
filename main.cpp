#include <Servo.h>

// Definição dos pinos dos sensores e atuadores
const int cockpitTempSensorPin = A0;  // Pino do sensor de temperatura do cockpit
const int tireTempSensorPin = A3;  // Pino do sensor de temperatura dos pneus
const int humiditySensorPin = A1;  // Pino do potenciômetro que simula o sensor de umidade
const int lightSensorPin = A2;  // Pino do sensor de luminosidade
const int servoPin = 9;  // Pino do servo motor
const int ledPin = 13;  // Pino do LED

Servo myServo;

void setup() {
  // Inicia a comunicação serial
  Serial.begin(9600);
  
  // Configuração dos pinos de entrada e saída
  pinMode(cockpitTempSensorPin, INPUT);
  pinMode(tireTempSensorPin, INPUT);
  pinMode(humiditySensorPin, INPUT);
  pinMode(lightSensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  // Inicializando o servo motor
  myServo.attach(servoPin);
}

void loop() {
  // Leitura dos sensores
  int cockpitTempValue = analogRead(cockpitTempSensorPin);
  int tireTempValue = analogRead(tireTempSensorPin);
  int humidityValue = analogRead(humiditySensorPin);
  int lightValue = analogRead(lightSensorPin);
  
  // Convertendo as leituras em valores úteis
  float cockpitTemperature = (cockpitTempValue * 5.0 / 1023.0) * 100; // Conversão do valor do sensor de temperatura do cockpit
  float tireTemperature = (tireTempValue * 5.0 / 1023.0) * 100; // Conversão do valor do sensor de temperatura dos pneus
  float humidity = humidityValue * 100.0 / 1023.0; // Conversão do valor do potenciômetro para % de umidade
  float lightIntensity = lightValue; // Conversão do valor do sensor de luminosidade para %

  // Exibindo os valores na Serial Monitor
  Serial.print("Cockpit Temperature: ");
  Serial.print(cockpitTemperature);
  Serial.print(" C || Tire Temperature: ");
  Serial.print(tireTemperature);
  Serial.print(" C || Humidity: ");
  Serial.print(humidity);
  Serial.print("% || Light Intensity: ");
  Serial.print(map(lightIntensity, 1017, 344, 0, 100));
  Serial.println("%");

  // Verifica requisitos
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
  if (lightIntensity < 0 || lightIntensity > 615) { // Assuming light sensor gives a percentage
    conditionsMet = false;
    nonIdealConditions++;
  }

  // Controlando a velocidade do servo motor com base nas condições
  int servoSpeed = 180; // Velocidade máxima
  if (!conditionsMet) {
    servoSpeed -= nonIdealConditions * 27; // Reduz 15% da velocidade máxima para cada condição não ideal (18 de 180 é 10%)
    digitalWrite(ledPin, HIGH); // Acende o LED indicando problema
  } else {
    digitalWrite(ledPin, LOW); // Apaga o LED indicando que todas as condições são ideais
  }

  // Calculando a velocidade máxima do motor em km/h
  int maxSpeedKmh = (map(servoSpeed, 0, 180, 0, 320));

  // Exibindo a velocidade máxima do motor no Serial Monitor
  Serial.print("Max Motor Speed: ");
  Serial.print(maxSpeedKmh);
  Serial.println("Km/h");
  Serial.println("---");

  // Movendo o servo motor
  myServo.write(servoSpeed);

  // Espera de 2 segundos
  delay(2000);
}