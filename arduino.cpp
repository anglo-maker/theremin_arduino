/**
 * Copyright (c) 2015 by http://www.electrominds.com
 * Simple Arduio Theremin "Theremino" Project
 * Project URL: http://www.electrominds.com/projects/simple-arduino-theremin-theremino
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 *
 * Required libraries:
 * NewPing: https://code.google.com/p/arduino-new-ping/downloads/detail?name=NewPing_v1.5.zip
 * toneAC: https://code.google.com/p/arduino-tone-ac/downloads/detail?name=toneAC_v1.2.zip
 */
 
#include <NewPing.h>
#include <toneAC.h>

#define DEBUG         true // Defina como true para ativar o debug Serial
#define TONE_PIN      8
#define TONE_VOLUME   10   // 1-20
#define TRIGGER_PIN   12   // Pino da placa ligada ao pino trigger do sensor ultrasônico.
#define ECHO_PIN      11   // Pino da placa ligada ao pino echo do sensor ultrasônico.
#define MAX_DISTANCE  200  // Distância máxima que queremos medir (em centímetros). O alcance máximo do sensor é de 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

void setup() {
  if (DEBUG) {
    Serial.begin(115200);
    Serial.println("Theremino starting");
  }
}

void loop() {
  delay(30); // Aguarda 30ms entre medições (aprox. 33 medições/seg). 29ms deve ser o menor intervalo entre medições.
  unsigned long uS = sonar.ping(); // Inicia a medição, recebe o tempo de medição em microssegundos (uS).
  
  if (DEBUG) Serial.println(uS);
    
  if (uS > 2000) { // O alcance é de 0-30cm do sensor.
    toneAC(0); // Desliga o som quando estiver fora do alcance.
    if (DEBUG) Serial.println("No tone");
  } else {
    int freq = 2000 - uS / 1.5; // Recebe a frequência do som
    toneAC(freq, TONE_VOLUME); // Toca!
    if (DEBUG) Serial.println(freq);
  }
}