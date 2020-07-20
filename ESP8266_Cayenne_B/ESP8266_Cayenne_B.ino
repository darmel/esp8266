// This example shows how to connect to Cayenne using an ESP8266 and send/receive sample data.
// Make sure you install the ESP8266 Board Package via the Arduino IDE Board Manager and select the correct ESP8266 board before compiling. 

//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

//del DHT11
#include <ESP8266WiFi.h>
#include <DHT.h>

/*** Definiendo el modelo de sensor y el pin al que estará conectado ***/
#define DHTTYPE DHT11 //DHT21, DHT22
#define DHTPIN  12 // GPIO12

DHT dht(DHTPIN, DHTTYPE, 27); // 11 works fine for ESP8266 threshold => MHZ CPU

/*** Variables para Humedad y Temperatura ****/
float temperatura; // double
float humedad;

// WiFi network info.
char ssid[] = "DIRECTVNET_10E197";
char wifiPassword[] = "0pt10n.5";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "43cd43d0-ca33-11ea-a67f-15e30d90bbf4";
char password[] = "8e1e00dd5e90512e3e3e10596c1ca03dbd6331f7";
char clientID[] = "ff5c4a50-ca34-11ea-a67f-15e30d90bbf4";

unsigned long lastMillis = 0;

void setup() {
	Serial.begin(115200);
	Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {
	Cayenne.loop();
}

// Default function for sending sensor data at intervals to Cayenne.
// You can also use functions for specific channels, e.g CAYENNE_OUT(1) for sending channel 1 data.
CAYENNE_OUT_DEFAULT()
{
	// Write data to Cayenne here. This example just sends the current uptime in milliseconds on virtual channel 0.
	Cayenne.virtualWrite(0, millis());
	// Some examples of other functions you can use to send data.
 leer_datos();
	Cayenne.virtualWrite(1, temperatura);
  Cayenne.virtualWrite(2, humedad);
	//Cayenne.luxWrite(2, 700);
	//Cayenne.virtualWrite(3, 50, TYPE_PROXIMITY, UNIT_CENTIMETER);
}

// Default function for processing actuator commands from the Cayenne Dashboard.
// You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
	CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
	//Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}

void leer_datos()
  {
   temperatura = dht.readTemperature();
      Serial.print("Temperatura actual: ");
   Serial.print(temperatura);
   humedad = dht.readHumidity();
      Serial.print("Humedad actual: "); 
   Serial.print(humedad, 2);
  }
