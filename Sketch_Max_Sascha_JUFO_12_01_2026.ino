// Blynk IoT Template-Daten (aus deinem Blynk-Projekt)
#define BLYNK_TEMPLATE_ID "TMPL4x1llU9kI"         // <-- Ersetze mit deiner Template ID
#define BLYNK_TEMPLATE_NAME "Gas und Rauch Sensorik"   // <-- Ersetze mit deinem Template-Namen
#define BLYNK_AUTH_TOKEN "TN6myE1Fii45H_2KejGee2sP3XNZkTnl"       // <-- Ersetze mit deinem Auth Token

// Blynk- und Netzwerk-Bibliotheken
#include <WiFi.h>                // Für WLAN-Verbindung mit dem ESP32
#include <WiFiClient.h>          // Netzwerk-Client für TCP/IP
#include <BlynkSimpleEsp32.h>    // Blynk-Bibliothek für den ESP32

// WLAN-Zugangsdaten (dein WLAN-Name + Passwort)
char ssid[] = "MSSWlan";        // <-- Ersetze mit deinem WLAN-Namen
char pass[] = "HwmG_1708!";    // <-- Ersetze mit deinem WLAN-Passwort

// MQ-2 Sensor ist am analogen Pin GPIO34 angeschlossen
#define MQ2_1_PIN 34  // Analoger Eingang des ESP32
#define MQ2_2_PIN 32  // Analoger Eingang des ESP32


// Blynk-Timer, um Funktionen regelmäßig auszuführen (z. B. alle paar Sekunden)
BlynkTimer timer;


// Funktion zum Auslesen des MQ-2 Sensors und Senden an Blynk
void sendSensor()
{
  // Lese den analogen Sensorwert (zwischen 0 und 4095)
  int sensorValue1 = analogRead(MQ2_1_PIN);
  int sensorValue2 = analogRead(MQ2_2_PIN);

  // Umrechnung des Sensorwerts in Spannung (optional, nur zu Info)
 // float voltage = sensorValue1 * (3.3 / 4095.0);
  // float voltage = sensorValue2 * (3.3 / 4095.0);

  // Serieller Monitor: Ausgabe des Messwerts und der Spannung
  Serial.print("MQ-2_1 Sensorwert: ");
  Serial.print(sensorValue1);
  Serial.print(" | Spannung: ");
  //Serial.println(voltage, 2);

  Serial.print("MQ-2_2 Sensorwert: ");
  Serial.print(sensorValue2);
  Serial.print(" | Spannung: ");
  //Serial.println(voltage, 2);


  // Sende den Sensorwert an die Blynk-App (z. B. Virtual Pin V0)
  Blynk.virtualWrite(V0, sensorValue1);
  Blynk.virtualWrite(V0, sensorValue2);
}

int Feuer = 100; // Variabel Feuer Deklariert diese wird für den alaem wert benötigt 
int Gerade = 1 ; // Pinn eins  für die anzeige Tafel
int Rechts = 2; // Pinn 2 für die anzeige Tafel
int Links = 3; // Pinn 3 für die anzeige Tafel
int Nichts = 0; // Variable Smoke sensor werscheinlich kaputt ? funktionier das ?

// Setup-Funktion: wird einmal beim Start des ESP32 ausgeführt
void setup()
{
  // Starte serielle Kommunikation für Debug-Ausgabe
  Serial.begin(115200);

  // Verbinde ESP32 mit WLAN und Blynk-Server
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Starte einen Timer, der alle 2 Sekunden (2000 Millisekunden)
  // die sendSensor()-Funktion aufruft
  timer.setInterval(2000L, sendSensor);
}

// Loop-Funktion: wird ständig wiederholt
void loop()
{
int sensorValue1 = analogRead(MQ2_1_PIN);
int sensorValue2 = analogRead(MQ2_2_PIN);

  Blynk.run();     // Hält die Verbindung zum Blynk-Server aufrecht
  timer.run();     // Führt geplante Timer-Funktionen aus (z. B. Sensorlesen)

if (sensorValue1 < Feuer){
  digitalWrite(Gerade, HIGH); // keine Gefahr Fluchtweg 1 Frei
  digitalWrite(Links, LOW);
  digitalWrite(Rechts, LOW);
  }
if (sensorValue1 > Feuer)  {
  digitalWrite(Gerade, LOW); // GefahrFluchtweg 1 Verspärt
  digitalWrite(Links, HIGH); // es herst gefahr Fluchtweg 2
  digitalWrite(Rechts, LOW);
}

if (sensorValue1 > Feuer){
  if (sensorValue2 > Feuer){
    digitalWrite(Gerade, LOW); // Gefahr Fluchtweg 1 Verspärt
    digitalWrite(Links, LOW); // Gefahr Fluchtweg 2 Verspärt
    digitalWrite(Rechts, HIGH); // nehme Fluchtweg 3
    }
}
if (sensorValue1 = Nichts){
  if (sensorValue2 = Nichts){
    digitalWrite(Gerade, LOW); // Gefahr Fluchtweg 1 Verspärt
    digitalWrite(Links, LOW); // Gefahr Fluchtweg 2 Verspärt
    digitalWrite(Rechts, LOW); // Gefahr Fluchtweg 3 vermutlich nicht begebar
    Serial.print("Rauchmelder nicht Funktionsfähig");
    }
}
}


