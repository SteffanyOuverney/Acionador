// Biblioteca para conexão WiFi
#include <WiFi.h>
#include "HX711.h"

// Parametros e biblioteca
float peso, forca;

HX711 escala;

float fator_calib = -10000; // Coloque aqui o valor encontrado na calibração

#define CELULA_DT  27
#define CELULA_SCK  26

// Variaveis do WiFi
const char* ssid     = "NOME_DA_REDE_AQUI";
const char* password = "SENHA_DA_REDE_AQUI";

// Conecta com o IFTTT
const char* resource = "/trigger/{Escreva seu evento}/with/key/{Escreva a key}";
const char* server = "maker.ifttt.com";

void setup() {

// Inicia a porta serial
Serial.begin(9600);

  Serial.println("Rotina de medida com a célula de carga.");
  escala.begin(CELULA_DT, CELULA_SCK);
  escala.set_scale(fator_calib); // Ajusta a escala
  escala.tare(); // Ajusta o zero da escala

  // Inicia a conexão WiFi e IFTTT
  initWifi();
  delay(5000);
  makeIFTTTRequest();

}

void loop() {
  Serial.print("Leitura: ");
  Serial.print(escala.get_units(10), 2); // Retorna a média de 10 medidas
  Serial.print(" kg");
  Serial.println();
  delay(1000);
}

// Função que realiza a conexão WiFi
void initWifi() {
  Serial.print("Conectando a ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);

  // Tempo estipulado para tentativa de conexão
  int timeout = 10 * 4;
  while (WiFi.status() != WL_CONNECTED  && (timeout-- > 0)) {
    delay(250);
    Serial.print(".");
  }
  Serial.println();

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Falha na conexão, voltando ao deep sleep");
  }
  else {
    Serial.print("WiFi conectado em ");
    Serial.print(millis());
    Serial.print(", IP address: ");
    Serial.println(WiFi.localIP());
  }
}

// Conecta e envia dados ao IFTTT
void makeIFTTTRequest() {
  float peso;
  delay(10000);
  
  WiFiClient client;
  int retries = 5;
  while (!!!client.connect(server, 80) && (retries-- > 0)) {
    Serial.print(".");
  }
  Serial.println();
  if (!!!client.connected()) {
    Serial.println("Falha na conexao...");
  }
  
    Serial.print("Request resource: ");
    Serial.println(resource);

    float forca = 0;
    forca = peso*9.81;

    float jsonObject = forca;
    
    client.println(String("POST ") + resource + " HTTP/1.1");
    client.println(String("Host: ") + server);
    client.println("Connection: close\r\nContent-Type: application/json");
    client.print("Content-Length: ");
    client.println();
    client.println(jsonObject);

    int timeout = 5 * 10;
    while (!!!client.available() && (timeout-- > 0)) {
      delay(100);
    }
    if (!!!client.available()) {
      Serial.println("Sem resposta...");
    }
    while (client.available()) {
      Serial.write(client.read());
    }
    Serial.println("\nEncerrando conexao");
    client.stop();
  }
