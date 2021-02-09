#include <PubSubClient.h>
#include <UIPEthernet.h>
#include <utility/logging.h>
#include <SPI.h>

byte mac[] = {0x44, 0x6E, 0x0F, 0x7F, 0xA4, 0xFE};
int pino2 = 2;
bool estado_sensor;
bool mensagem;

EthernetClient client;
PubSubClient mqttClient(client);

void setup() {
  pinMode(pino2, INPUT_PULLUP);
  
  Ethernet.begin(mac);
  Serial.begin(9600);  

  Serial.print("O IP do Arduino é: ");
  Serial.println(Ethernet.localIP());

  Serial.print("A mascara de Rede do arduino é: ");
  Serial.println(Ethernet.subnetMask());

  Serial.print("O Gateway do arduino é: " );
  Serial.println(Ethernet.gatewayIP());

  mqttClient.setServer("548921833", 1883);

}

void loop() {
  mqttClient.connect("lucasGoncalves");

  estado_sensor = digitalRead(pino2);

  if(estado_sensor == 1){
    mensagem = mqttClient.publish("Rack","A porta está aberta");
  }
  else{
    mensagem = mqttClient.publish("Rack","A porta está fechada)";
  }
  
  Serial.print("O estado do sensor é: ");
  Serial.println(estado_sensor);

  mqttClient.loop();
  delay(500);
}
