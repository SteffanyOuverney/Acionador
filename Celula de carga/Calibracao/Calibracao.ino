// Código de calibração da célula de carga.
//
// Arduino - HX711
// Pin 10 - SCK
// Pin 11 - DT

#include "HX711.h"

#define CELULA_DT  11
#define CELULA_SCK  10

HX711 escala;

float fator_calib = -10000; // Se esse valor estiver muito distante ao iniciar, ajustar e fazer o upload novamente

void setup() {
  
  Serial.begin(9600);
  Serial.println("Rotina para calibrar a célula.");
  Serial.println("Inicie sem carga.");
  Serial.println("Após iniciarem as leituras, coloque um peso de massa conhecida");
  Serial.println("Para calibrar o fator de ajuste digite + ou -");   

  escala.begin(CELULA_DT, CELULA_SCK);
  escala.set_scale();
  escala.tare(); // Ajusta o zero da escala no valor de leitura

}

void loop() {

  escala.set_scale(fator_calib); // Ajusta a escala para esse fator de calibração

  Serial.print("Leitura: ");
  Serial.print(escala.get_units(10), 2); // Retorna a média de 10 medidas
  Serial.print(" kg");
  Serial.print(" Fator: ");
  Serial.print(fator_calib);
  Serial.println();

  if(Serial.available())
  {
    char tecla = Serial.read();
    if(tecla == '+')
      fator_calib += 10;
    else if(tecla == '-')
      fator_calib -= 10;
  }
}
