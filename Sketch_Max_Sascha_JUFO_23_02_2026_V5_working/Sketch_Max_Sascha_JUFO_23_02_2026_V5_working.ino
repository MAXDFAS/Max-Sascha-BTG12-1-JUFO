// Blynk IoT Template-Daten (aus deinem Blynk-Projekt)
#define BLYNK_TEMPLATE_ID "TMPL4x1llU9kI"         // <-- Ersetze mit deiner Template ID
#define BLYNK_TEMPLATE_NAME "Gas und Rauch Sensorik"   // <-- Ersetze mit deinem Template-Namen
#define BLYNK_AUTH_TOKEN "TN6myE1Fii45H_2KejGee2sP3XNZkTnl"       // <-- Ersetze mit deinem Auth Token

// Blynk- und Netzwerk-Bibliotheken
#include <WiFi.h>                // Für WLAN-Verbindung mit dem ESP32
#include <WiFiClient.h>          // Netzwerk-Client für TCP/IP
#include <BlynkSimpleEsp32.h>    // Blynk-Bibliothek für den ESP32

// WLAN-Zugangsdaten (dein WLAN-Name + Passwort)
char ssid[] = "RinWEB";        // <-- Ersetze mit deinem WLAN-Namen
char pass[] = "18312555077400557770";    // <-- Ersetze mit deinem WLAN-Passwort

// MQ-2 Sensor ist am analogen Pin GPIO34 angeschlossen
int MQ2_1_PIN = 39;  // Analoger Eingang des ESP32
int MQ2_2_PIN = 34;  // Analoger Eingang des ESP32
int MQ2_3_PIN = 35;  // Analoger Eingang des ESP32
int Feuer1 = 200; // Variabel Feuer Deklariert diese wird für den alaem wert benötigt 
int Feuer2 = 250;
int Feuer3= 200;
int Gerade = 14;
int Links = 25;
int Rechts = 26;

BlynkTimer timer;
// Setup-Funktion: wird einmal beim Start des ESP32 ausgeführt

void setup()
{
  timer.setInterval(1000, sendSensor);
  // Verbinde ESP32 mit WLAN und Blynk-Server
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

 pinMode(Gerade, OUTPUT);
 pinMode(Links, OUTPUT);
 pinMode(Rechts, OUTPUT);

}

void sendSensor()
{
 Serial.begin(115200);

 int sensorValue1 = analogRead(MQ2_1_PIN);
 int sensorValue2 = analogRead(MQ2_2_PIN);
 int sensorValue3 = analogRead(MQ2_3_PIN);

  // Sende den Sensorwert an die Blynk-App (z. B. Virtual Pin V0)
  Blynk.virtualWrite(V0, sensorValue1);
  Blynk.virtualWrite(V1, sensorValue2);
  Blynk.virtualWrite(V3, sensorValue3);

  Serial.print("Sensor 1: ");
  Serial.print(sensorValue1); 
  Serial.print(" | Sensor 2: ");
  Serial.print(sensorValue2);
  Serial.print(" | Sensor 3: ");
  Serial.println(sensorValue3);


 digitalWrite(Gerade, HIGH); // Fluchtweg 1 Frei standart
 digitalWrite(Links, LOW); // Fluchtweg 1 Frei standart
 digitalWrite(Rechts, LOW); // Fluchtweg 1 Frei standart


if (sensorValue1 > Feuer1)  { // GefahrFluchtweg 1 Verspärt
  if (sensorValue2 < Feuer2)  { // es herst keine gefahr bei Fluchtweg 2
  digitalWrite(Gerade, LOW); 
  digitalWrite(Links, HIGH); 
  digitalWrite(Rechts, LOW);
}
}
if (sensorValue1 > Feuer1){ // Gefahr Fluchtweg 1 Verspärt
  if (sensorValue2 > Feuer2){ // Gefahr Fluchtweg 2 Verspärt
    if (sensorValue3 < Feuer3){ // Fluchtweg 3 ist frei diesen nutzen
    digitalWrite(Gerade, LOW); 
    digitalWrite(Links, LOW); 
    digitalWrite(Rechts, HIGH); 
    }
}
}
if (sensorValue1 > Feuer1){ // Gefahr Fluchtweg 1 Verspärt die andere bergen trotzdem eine Gefahr, verstand nutzen wen möglich kürzester Fluchtweg 
  if (sensorValue2 > Feuer2){ // Gefahr Fluchtweg 2 Verspärt
    if (sensorValue3 > Feuer3){ // Fluchtweg 3 Verspärt
    digitalWrite(Gerade, HIGH); 
    digitalWrite(Links, LOW); 
    digitalWrite(Rechts, LOW); 
    }
}
}
}

void loop()
{
 Blynk.run();     // Hält die Verbindung zum Blynk-Server aufrecht
 timer.run();     // Führt geplante Timer-Funktionen aus (z. B. Sensorlesen)
}