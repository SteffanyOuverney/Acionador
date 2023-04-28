// Código de calibração da célula de carga.
//
// Arduino - HX711
// Pin 10 - SCK
// Pin 11 - DT

#include "HX711.h"

#define CELULA_DT  26
#define CELULA_SCK  27

HX711 escala;


void setup() {
  
  Serial.begin(9600);
  Serial.println("Rotina para calibrar a célula.");
  Serial.println("Inicie sem carga.");
  Serial.println("Após iniciarem as leituras, coloque um peso de massa conhecida");
  Serial.println("Para calibrar o fator de ajuste digite + ou -");   

  escala.begin(CELULA_DT, CELULA_SCK);
  escala.set_scale();
  escala.tare(20); // Ajusta o zero da escala no valor de leitura

}

void loop() {

  Serial.print("Leitura: ");
  Serial.print(escala.get_units(1)); // Retorna a média de 10 medidas
  Serial.print(" kg");
  Serial.println();

}
