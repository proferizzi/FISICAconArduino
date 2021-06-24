// Punto di Accesso + Server Web     3/3


//#include <ESP8266WiFi.h>       // Librerie per gestire il Server
//#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *wifi_ssid = "Rete_per_condividere_dati";   // Rete generata dal Punto di Accesso
const char *wifi_password = "";
IPAddress ip(192,168,11,4);                             // Indirizzo IP e settaggio rete
IPAddress gateway(192,168,11,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);       // Creazione dell'oggetto server in ascolto su porta 80

int n1 = 0;      // Variabili per salvare i dati ricevuti dai client
int x1 = 0;
int n2 = 0;
int x2 = 0;

// Pagine Web -----------------------------------------------------------------
String HeaderPage = "<!DOCTYPE html><html><head><meta http-equiv='refresh' content='5'/><style> header { background: linear-gradient(to right, #1e5799 0%,#7db9e8 100%); color: #fff; padding:10px; text-align: center; vertical-align: middle; } body{ padding:15px; color: #5e5e5e; font-family: Helvetica,Arial,sans-serif; font-variant: small-caps; font-size:1em; text-align: center; } footer { background: linear-gradient(to left, #1e5799 0%,#7db9e8 100%); color: #fff; padding:10px; text-align: right; vertical-align: bottom; } h2 {  padding:10px; text-align: center; vertical-align: middle; font-size:2em; } </style></head><body><header>FISICA CON ARDUINO 2021</header>";
String FooterPage = "<footer>@mr</footer></body></html>";
String rootPageBody = "<h2><TABLE FRAME='VOID' CELLPADDING='10' WIDTH='100%' BORDER='1'><CAPTION>Tabella dei dati raccolti</CAPTION><TR><TD>n1 = "+String(n1)+"</TD><TD>x1 = "+String(x1)+"</TD></TR><TR><TD>n2 = "+String(n2)+"</TD><TD>x2 = "+String(x2)+"</TD></TR></TABLE></h2>";
String rootWebPage;
// -----------------------------------------------------------------------------


 
void setup() {
  Serial.begin(115200);    // Inizializzo la Seriale
  Serial.println();

  configura_wifi();           // Funzione che genera il Punto di Accesso
  
  rootWebPage = HeaderPage;
  rootWebPage += rootPageBody;
  rootWebPage += FooterPage;

  inizializzaServerWeb();       // Funzione che inizializza il server Web
}

 
void loop() { 
  server.handleClient(); 
}

 
// Funzioni -------------------------------------------

void configura_wifi() { 
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip, gateway, subnet);
  WiFi.softAP(wifi_ssid);
  Serial.print("Indirizzo IP: ");
  Serial.println(WiFi.localIP());
}


void inizializzaServerWeb() {
  server.on("/", gestisciRoot);
  server.on("/aggiornamento1", gestisciAggiornamento1);  // Aggiorna i dati dai sensori
  server.on("/aggiornamento2",gestisciAggiornamento2);
  server.begin();
  Serial.println("Server inizializzato!");
}


void gestisciRoot() { 
  String HeaderPage = "<!DOCTYPE html><html><head><meta http-equiv='refresh' content='5'/><style> header { background: linear-gradient(to right, #1e5799 0%,#7db9e8 100%); color: #fff; padding:10px; text-align: center; vertical-align: middle; } body{ padding:15px; color: #5e5e5e; font-family: Helvetica,Arial,sans-serif; font-variant: small-caps; font-size:1em; text-align: center; } footer { background: linear-gradient(to left, #1e5799 0%,#7db9e8 100%); color: #fff; padding:10px; text-align: right; vertical-align: bottom; } h2 {  padding:10px; text-align: center; vertical-align: middle; font-size:2em; } </style></head><body><header>FISICA CON ARDUINO 2021</header>";
  String FooterPage = "<footer>@mr</footer></body></html>";
  String rootPageBody = "<h2><TABLE FRAME='VOID' CELLPADDING='10' WIDTH='100%' BORDER='1'><CAPTION>Tabella dei dati raccolti</CAPTION><TR><TD>n1 = "+String(n1)+"</TD><TD>x1 = "+String(x1)+"</TD></TR><TR><TD>n2 = "+String(n2)+"</TD><TD>x2 = "+String(x2)+"</TD></TR></TABLE></h2>";
  String rootWebPage;
  rootWebPage = HeaderPage;
  rootWebPage += rootPageBody;
  rootWebPage += FooterPage;
  server.send(200, "text/html", rootWebPage);    // Ricaricare pagina ogni volta 
}


void gestisciAggiornamento1() {                   // I dati passano come argomenti URL
  n1 = server.arg("n1").toInt();                  // (es. /aggiornamento1?n1=1&&x1=2)
  //Serial.print("n1 = "); Serial.println(n1);
  x1 = server.arg("x1").toInt();   
  //Serial.print("x1 = "); Serial.println(x1);
  server.send(200,"text/plain","Dati aggiornati dal Client 1");
}


void gestisciAggiornamento2() {                   // I dati passano come argomenti URL 
  n2 = server.arg("n2").toInt();                  // (es. /aggiornamento2?n2=1&&x2=2)
  //Serial.print("n2 = "); Serial.println(n2);
  x2 = server.arg("x2").toInt();   
  //Serial.print("x2 = "); Serial.println(x2);
  server.send(200,"text/plain","Dati aggiornati dal Client 2");
}




// Fonte per Server Web e HTML https://www.mauroalfieri.it/elettronica/wemos-esp8266-webserver.html
// Fonte per Punto di Accesso e dialogo tra client e server https://www.youtube.com/watch?v=gZhUi24_qms

