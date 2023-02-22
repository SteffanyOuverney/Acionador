// Código de medida com a célula de carga.
//

#include "HX711.h"

#define CELULA_DT  11
#define CELULA_SCK  10

HX711 escala;

float fator_calib = -10000; // Coloque aqui o valor encontrado na calibração

void setup() {
  
  Serial.begin(9600);
  Serial.println("Rotina de medida com a célula de carga.");

  escala.begin(CELULA_DT, CELULA_SCK);
  escala.set_scale(fator_calib); // Ajusta a escala
  escala.tare(); // Ajusta o zero da escala
}

void loop() {

  Serial.print("Leitura: ");
  Serial.print(escala.get_units(10), 2); // Retorna a média de 10 medidas
  Serial.print(" kg");
  Serial.println();

  delay(1000);
  
}
