#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "settings.h"

/* IP direcciones */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

/* variables */
int period = 10000;
int time_now = 0;
boolean BotonPulsado = 0;
int velocidad = 0;
int pvelocidad = 0;
bool REL1status = LOW;
bool REL2status = LOW;
bool REL3status = LOW;
bool REL4status = LOW;

/* Configuración led NEOPIXEL */
Adafruit_NeoPixel pixels_STRIP_1  = Adafruit_NeoPixel(NUMPIXELS_STRIP_1, PIN_STRIP_1, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);

  /* Activación de la wifi */
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);

  server.on("/", handle_OnConnect);
  server.on("/rel1on", handle_rel1on);
  server.on("/rel1off", handle_rel1off);
  server.on("/rel2on", handle_rel2on);
  server.on("/rel2off", handle_rel2off);
  server.on("/rel3on", handle_rel3on);
  server.on("/rel3off", handle_rel3off);
  server.on("/rel4on", handle_rel4on);
  server.on("/rel4off", handle_rel4off);
  server.onNotFound(handle_NotFound);
  
  server.begin();
  Serial.println("HTTP server started");

  /* Iniciar RELEs */
  switch (velocidades) {
  case 4:
    pinMode(PinRele4 , OUTPUT); 
    digitalWrite(PinRele4, LOW );
  case 3:
    pinMode(PinRele3 , OUTPUT); 
    digitalWrite(PinRele3, LOW );
  case 2:
    pinMode(PinRele2 , OUTPUT); 
    digitalWrite(PinRele2, LOW );
  case 1:
    pinMode(PinRele1 , OUTPUT);
    digitalWrite(PinRele1, LOW );
  }
  
  /* Iniciar pulsador */
  pinMode(PinBoton , INPUT);

  /* Iniciar NEOPIXEL */
  pixels_STRIP_1.begin(); // This initializes the NeoPixel library. 
  for(int i=0;i<NUMPIXELS_STRIP_1;i++){
     pixels_STRIP_1.setPixelColor(i, pixels_STRIP_1.Color(0,0,255)); // blue color.
     pixels_STRIP_1.show(); // This sends the updated pixel color to the hardware.
     delay (100);
  }
}

void loop() {
  server.handleClient();

  /* Comandos desde la página web */
  if(REL1status){
    velocidad = 1;
    }
  else {
    if(REL2status){
      velocidad = 2;
      }
    else {
      if(REL3status){
        velocidad = 3;
        }
      else {
        if(REL4status){
          velocidad = 4;
          }
        else {
          velocidad = 0;
        }
      }
    }
  }
  
  /* Comandos desde el botón */
  BotonPulsado = digitalRead(PinBoton);
  if (BotonPulsado == LOW) {
    Serial.println("Boton pulsado");
    velocidad += 1;
    delay (EsperaCambio);    
    if (velocidad == velocidades+1) {
      velocidad = 0;      
    }
  }

  switch (velocidad) {
    case 0:
      REL1status = LOW;
      REL2status = LOW;
      REL3status = LOW;
      REL4status = LOW;
      digitalWrite(PinRele1, LOW );
      digitalWrite(PinRele2, LOW );
      digitalWrite(PinRele3, LOW );
      digitalWrite(PinRele4, LOW );
      break;
    case 1:
      REL1status = HIGH;
      REL2status = LOW;
      REL3status = LOW;
      REL4status = LOW;
      digitalWrite(PinRele1, HIGH );
      digitalWrite(PinRele2, LOW );
      digitalWrite(PinRele3, LOW );
      digitalWrite(PinRele4, LOW );
      break;
    case 2:
      REL1status = LOW;
      REL2status = HIGH;
      REL3status = LOW;
      REL4status = LOW;
      digitalWrite(PinRele1, LOW );
      digitalWrite(PinRele2, HIGH );
      digitalWrite(PinRele3, LOW );
      digitalWrite(PinRele4, LOW );
      break;
    case 3:
      REL1status = LOW;
      REL2status = LOW;
      REL3status = HIGH;
      REL4status = LOW;
      digitalWrite(PinRele1, LOW );
      digitalWrite(PinRele2, LOW );
      digitalWrite(PinRele3, HIGH );
      digitalWrite(PinRele4, LOW );
      break;
    case 4:
      REL1status = LOW;
      REL2status = LOW;
      REL3status = LOW;
      REL4status = HIGH;
      digitalWrite(PinRele1, LOW );
      digitalWrite(PinRele2, LOW );
      digitalWrite(PinRele3, LOW );
      digitalWrite(PinRele4, HIGH );
      break;
  }
  if (velocidad != pvelocidad) {
    Serial.print("velocidad: ");
    Serial.println(velocidad);
    server.send(200, "text/html", SendHTML(REL1status,REL2status,REL3status,REL4status));
    leds ();
    pvelocidad = velocidad;
  }
}

void leds(){
  if (LEDsBinarios) {
    if (velocidad == 0) {
      pixels_STRIP_1.fill(pixels_STRIP_1.Color(0, 0, 0),0, pixels_STRIP_1.numPixels()); // black  
    } else {
      if (velocidad == 1) {
        pixels_STRIP_1.fill(pixels_STRIP_1.Color(0,255,0),0, pixels_STRIP_1.numPixels()); // green  
      } else {
        pixels_STRIP_1.fill(pixels_STRIP_1.Color(255,0,0),0, pixels_STRIP_1.numPixels()); // red 
      }
    }
  } else { 
    if (velocidad == 0) {
      pixels_STRIP_1.fill(pixels_STRIP_1.Color(0, 0, 0),0, pixels_STRIP_1.numPixels()); // black  
    } else {
      if (velocidad == 4) {
        pixels_STRIP_1.fill(pixels_STRIP_1.Color(255, 255, 255),0, pixels_STRIP_1.numPixels()); // white  
      } else {
        for(int i=0;i<NUMPIXELS_STRIP_1;i++){
          pixels_STRIP_1.setPixelColor(i, pixels_STRIP_1.Color(0,0,255)); // blue color.
        } 
        switch (velocidad) {
          case 3:
            pixels_STRIP_1.setPixelColor(2, pixels_STRIP_1.Color(255,255,255)); // blue color.
            pixels_STRIP_1.setPixelColor(3, pixels_STRIP_1.Color(255,255,255)); // blue color.
            pixels_STRIP_1.setPixelColor(11, pixels_STRIP_1.Color(255,255,255)); // blue color.
            pixels_STRIP_1.setPixelColor(12, pixels_STRIP_1.Color(255,255,255)); // blue color.
          case 2:             
            pixels_STRIP_1.setPixelColor(4, pixels_STRIP_1.Color(255,255,255)); // blue color.
            pixels_STRIP_1.setPixelColor(5, pixels_STRIP_1.Color(255,255,255)); // blue color.
            pixels_STRIP_1.setPixelColor(9, pixels_STRIP_1.Color(255,255,255)); // blue color.
            pixels_STRIP_1.setPixelColor(10, pixels_STRIP_1.Color(255,255,255)); // blue color.
          case 1:             
            pixels_STRIP_1.setPixelColor(6, pixels_STRIP_1.Color(255,255,255)); // blue color.
            pixels_STRIP_1.setPixelColor(7, pixels_STRIP_1.Color(255,255,255)); // blue color.
            pixels_STRIP_1.setPixelColor(8, pixels_STRIP_1.Color(255,255,255)); // blue color.
        }
      }
    }
  }
  pixels_STRIP_1.show(); // This sends the updated pixel color to the hardware.
}    
      
void handle_OnConnect() {
  REL1status = LOW;
  REL2status = LOW;
  REL3status = LOW;
  REL4status = LOW;
  Serial.println("handle_OnConnect");
  server.send(200, "text/html", SendHTML(REL1status,REL2status,REL3status,REL4status)); 
}

void handle_rel1on() {
  REL1status = HIGH;
  REL2status = LOW;
  REL3status = LOW;
  REL4status = LOW;
  Serial.println("handle_rel1on");
  server.send(200, "text/html", SendHTML(true,REL2status,REL3status,REL4status)); 
}
void handle_rel1off() {
  REL1status = LOW; 
  Serial.println("handle_rel1off");
  server.send(200, "text/html", SendHTML(false,REL2status,REL3status,REL4status)); 
}

void handle_rel2on() {
  REL1status = LOW;
  REL2status = HIGH;
  REL3status = LOW;
  REL4status = LOW;    
  Serial.println("handle_rel2on");
  server.send(200, "text/html", SendHTML(REL1status,true,REL3status,REL4status)); 
}
void handle_rel2off() {
  REL2status = LOW;
  Serial.println("handle_rel2off");
  server.send(200, "text/html", SendHTML(REL1status,false,REL3status,REL4status)); 
}

void handle_rel3on() {
  REL1status = LOW;
  REL2status = LOW;
  REL3status = HIGH;
  REL4status = LOW;    
  Serial.println("handle_rel3on");
  server.send(200, "text/html", SendHTML(REL1status,REL2status,true,REL4status)); 
}
void handle_rel3off() {
  REL3status = LOW;
  Serial.println("handle_rel3off");
  server.send(200, "text/html", SendHTML(REL1status,REL2status,false,REL4status)); 
}

void handle_rel4on() {
  REL1status = LOW;
  REL2status = LOW;
  REL3status = LOW;
  REL4status = HIGH;  
  Serial.println("handle_rel4on");
  server.send(200, "text/html", SendHTML(REL1status,REL2status,REL3status,true)); 
}
void handle_rel4off() {
  REL4status = LOW;
  Serial.println("handle_rel4off");
  server.send(200, "text/html", SendHTML(REL1status,REL2status,REL3status,false)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(uint8_t rel1stat,uint8_t rel2stat,uint8_t rel3stat,uint8_t rel4stat){
  Serial.print("SendHTML");
  Serial.print(rel1stat);
  Serial.print(rel2stat);
  Serial.print(rel3stat);
  Serial.println(rel4stat);
  
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Removir</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 5px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>Removir</h1>\n";
  ptr +="<h2>Filtro HEPA de reciclaje</h2>\n";
  ptr +="<h3>Velocidad del motor:</h3>\n";
  switch (velocidades) {
  case 4:
    if(rel4stat)
        {ptr +="<a class=\"button button-off\" href=\"/rel4off\">OFF</a>\n";}
    else
        {ptr +="<a class=\"button button-on\" href=\"/rel4on\">4</a>\n";}
  case 3:
    if(rel3stat)
        {ptr +="<a class=\"button button-off\" href=\"/rel3off\">OFF</a>\n";}
    else 
        {ptr +="<a class=\"button button-on\" href=\"/rel3on\">3</a>\n";}
  case 2:
    if(rel2stat)
      {ptr +="<a class=\"button button-off\" href=\"/rel2off\">OFF</a>\n";}
    else
      {ptr +="<a class=\"button button-on\" href=\"/rel2on\">2</a>\n";}
  case 1:
    if(rel1stat)
      {ptr +="<a class=\"button button-off\" href=\"/rel1off\">OFF</a>\n";}
    else
      {ptr +="<a class=\"button button-on\" href=\"/rel1on\">1</a>\n";}
  }
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
