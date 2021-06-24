

// MQTT PUBLISHER con MKR WiFi-1010

#include "secrets.h"         
#include <WiFiNINA.h>
#include <PubSubClient.h>

WiFiClient wifi;
int status = WL_IDLE_STATUS;

IPAddress server(192, 168, 178, 130);
PubSubClient client(wifi);

unsigned long t1, dt;
int stato = 0;


void setup() {
  while(!Serial){ ; }   // Attendo che sia pronta la Seriale
  Serial.begin(9600); Serial.println("Ok");   // La configuro e dico ok
  
  Serial.print("Connessione");
  while(status != WL_CONNECTED){
    status = WiFi.begin(WIFI_SSID, WIFI_PASS); Serial.print("."); delay(1000);
  }
  Serial.println("Connesso al WiFi!\n");
  
  client.setServer(server, 1883);   // Settaggio e collegamento col server MQTT
  if(client.connect("arduinopub")){      
    Serial.println("MQTT connesso");
    client.subscribe("/prova");  
  }else{
    Serial.println("MQTT non connesso"); 
    Serial.print("rc = "); Serial.println(client.state());  
  }
  
  t1 = millis();
}


void loop() {
  dt = millis() - t1;
  if(dt > 2000){
    if((stato%2) == 0){
      client.publish("/prova", "on"); Serial.println("on");
    }else{
      client.publish("/prova", "off"); Serial.println("off");
    }
    
    stato++;
    t1 = millis();
    
  }
}



// Fonte Aliverti https://www.youtube.com/watch?v=cLRuWwKkSp4




