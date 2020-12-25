/* Configutraciones del Removir */

// SSID y clave de la wifi que sirve 
const char* ssid = "Removir";
const char* password = "12345678";

// MOTOR 
const int velocidades = 2; // de 1 a 4
const int PinRele1 = 13;
const int PinRele2 = 12;
const int PinRele3 = 14;
const int PinRele4 = 16;

// LEDs
const int PIN_STRIP_1 = 0;
/* Velocidad 1=verde, 2=rojo */
	const bool LEDsBinarios = true;
	const int NUMPIXELS_STRIP_1 = 1;
/* Escala de blanco sobre azul 4 velocidades */
	//const bool LEDsBinarios = false;
	//const int NUMPIXELS_STRIP_1 = 15; // No modificar

// Otros parámetros
const int EsperaCambio = 1000; //milisegundos
const int PinBoton = 2;
