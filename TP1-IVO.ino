#include <WiFi.h>
#include <WebServer.h>


const char* nombreRed = "TuSSID";
const char* claveRed = "TuPassword";


WebServer servidor(80);


const int pinRele = 5;


void paginaPrincipal() {
  String pagina = "<html>\
  <head><title>Control del Relé</title></head>\
  <body>\
  <h1>Control del Relé</h1>\
  <button onclick=\"window.location.href='/encender'\">Encender</button>\
  <button onclick=\"window.location.href='/apagar'\">Apagar</button>\
  </body>\
  </html>";
  servidor.send(200, "text/html", pagina);
}


void encenderRele() {
  digitalWrite(pinRele, LOW);
  servidor.send(200, "text/html", "<h1>Relé Encendido</h1><a href='/'>Volver</a>");
}


void apagarRele() {
  digitalWrite(pinRele, HIGH);
  servidor.send(200, "text/html", "<h1>Relé Apagado</h1><a href='/'>Volver</a>");
}


void setup() {
  Serial.begin(115200);
  pinMode(pinRele, OUTPUT);
  digitalWrite(pinRele, HIGH);


  WiFi.begin(nombreRed, claveRed);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a la red WiFi...");
  }


  Serial.println("Conectado a WiFi");
  Serial.println(WiFi.localIP());


  servidor.on("/", paginaPrincipal);
  servidor.on("/encender", encenderRele);
  servidor.on("/apagar", apagarRele);


  servidor.begin();
  Serial.println("Servidor web en funcionamiento");
}


void loop() {
  servidor.handleClient();
}
