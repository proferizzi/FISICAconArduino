// MQTT PUBLISHER con MKR WiFi-1010 e TMP36

//#include "secrets.h"  // inserire un nuovo file nella stessa cartella del filo *.ino con i dati ID e PW della rete       
#include <WiFiNINA.h>
#include <PubSubClient.h>
#include <avr/dtostrf.h>

const char WIFI_SSID[] = "metti il nome della rete";  // commentare queste due righe se si usa "secrets.h"
const char WIFI_PASS[] = "metti la password";

WiFiClient wifi;
int status = WL_IDLE_STATUS;

IPAddress server(192, 168, 1, 52);
PubSubClient client(wifi);

unsigned long t1, dt;
int stato = 0;

// VARIABILI PER IL TERMOMETRO
int val_Adc = 0;
float temp = 0;
const int Pin_TMP36 = A6; //variabile lettura sensore

char result[8]; // Buffer big enough for 7-character float


void setup() {
  //while(!Serial){ ; }   // Attendo che sia pronta la Seriale
  Serial.begin(9600);   // La configuro 
  Serial.println("Connessione");
  while(status != WL_CONNECTED){
    status = WiFi.begin(WIFI_SSID, WIFI_PASS); Serial.print("."); delay(1000);
  }
  Serial.println("Connesso al WiFi!\n");
  
  client.setServer(server, 1883);   // Settaggio e collegamento col server MQTT
  if(client.connect("arduinopub2")){      
    Serial.println("MQTT connesso");
    client.subscribe("/temp2");  
  }else{
    Serial.println("MQTT non connesso"); 
    Serial.print("rc = "); Serial.println(client.state());  
  }
}


void loop() {
  //Legge il valore dalla porta analogica
  val_Adc = analogRead(Pin_TMP36);
  // Converte il valore in temperatura
  float temp = ((val_Adc /1024.0) * 3.15 - .5) * 100;
  //Pausa di mezzo secondo tra le misure
  delay( 500 );  
  dtostrf(temp, 6, 2, result); // Leave room for too large numbers!
  client.publish("/temp2", result);
  Serial.print(temp);  
  Serial.println(" °C");
}



// Fonte Aliverti https://www.youtube.com/watch?v=cLRuWwKkSp4
//                e per secrets.h https://www.youtube.com/watch?v=k5HJ6G0YeWw
// MKR1010 Hardware https://www.mischianti.org/it/2021/06/14/arduino-mkr-wifi-1010-piedinatura-ad-alta-risoluzione-e-specifiche/

// Fonte per TMP36 Adrirobot http://win.adrirobot.it/sensori/tmp36/scheda_arduino_tmp36.htm#Listato_del_programma

// Fonte https://forum.arduino.cc/t/dtostrf-was-not-declared-in-this-scope/166609/2

// NOTA BENE PER FAR ANDARE MOSQUITTO BISOGNA CAMBIARE IL FILE mosquitto.conf e inserire 
// listener 1883
// allow_anonymous true
// e poi usare mosquitto -c mosquitto.conf





/*

// MQTT SUBSCRIBER con MKR WiFi-1010


#include "secrets.h"
#include <WiFiNINA.h>
#include <PubSubClient.h>

WiFiClient wifi;
int status = WL_IDLE_STATUS;

IPAddress server(192, 168, 178, 130);
PubSubClient client(wifi);


void setup() {
  pinMode(13, OUTPUT);
  while(!Serial){ ; } Serial.begin(9600); Serial.println("Ok");
  Serial.print("Connessione");
  while(status != WL_CONNECTED){
    status = WiFi.begin(WIFI_SSID, WIFI_PASS); Serial.print("."); delay(1000);
  }
  Serial.println("Connesso al WiFi!\n");
  client.setServer(server, 1883);
  client.setCallback(callback);
  if(client.connect("arduinosub")){
    Serial.println("MQTT connesso");
    client.subscribe("/prova");  
  }else{
    Serial.println("MQTT non connesso"); 
    Serial.print("rc = "); Serial.println(client.state());  
  }
}


void loop() {
  client.loop();
}


void callback(char* topic, byte* payload, unsigned int length){
  String msg;
  for(int i = 0; i < length; i++){
    msg += (char)payload[i];
  }
  if(strcmp(topic, "/prova") == 0){
    if(msg == "on"){
      digitalWrite(13, HIGH); Serial.println("on");    
    }else{
      digitalWrite(13, LOW); Serial.println("off");
    }
  }
}



// Fonte https://www.youtube.com/watch?v=k5HJ6G0YeWw


*/
