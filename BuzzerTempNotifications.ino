/*
   PROJET : BuzzerTemp Notifications

   CONFIGURATION DU MODE :
   - Si vous avez le matériel (DHT22 + Buzzer) : Mettez la ligne "#define
   SIMULATION_MODE" en commentaire (ajout de // devant).
   - Si vous avez juste l'ESP32 : Laissez "#define SIMULATION_MODE".
*/

// ==========================================
// CHOIX DU MODE (A MODIFIER ICI)
// ==========================================
#define SIMULATION_MODE // <--- LAISSER CELA POUR TESTER SANS CAPTEURS (Flash
                        // LED + Température Virtuelle)

// ==========================================
// INCLUSION DES BIBLIOTHEQUES
// ==========================================
#include <HTTPClient.h>
#include <WiFi.h>

#ifndef SIMULATION_MODE
#include <DHT.h>
#endif

// ==========================================
// CONFIGURATION UTILISATEUR
// ==========================================

const char *ssid = "VOTRE_SSID_WIFI";
const char *password = "VOTRE_MOT_DE_PASSE_WIFI";
// URL CallMeBot / IFTTT
const String NOTIF_URL = "https://example.com/webhook?event=temp_alert";

// --- Configuration Seuil ---
const float TEMP_THRESHOLD = 30.0;
const float TEMP_HYSTERESIS = 1.0;
const unsigned long NOTIF_COOLDOWN = 60000; // 60 secondes

// --- Pinout (Mode Reel) ---
#define DHTPIN 4
#define DHTTYPE DHT22
#define BUZZER_PIN 5

// --- Pinout (Mode Simulation) ---
// La plupart des ESP32 ont la LED sur GPIO 2. Si rien ne s'allume, essayez 1
// ou 22.
#define LED_PIN 2

// ==========================================
// VARIABLES GLOBALES
// ==========================================

#ifndef SIMULATION_MODE
DHT dht(DHTPIN, DHTTYPE);
#endif

bool alarmState = false;
unsigned long lastNotifTime = 0;
unsigned long lastReadTime = 0;
// Lecture plus rapide en mode simulation (1s) pour voir les changements vite
#ifdef SIMULATION_MODE
const unsigned long READ_INTERVAL = 1000;
#else
const unsigned long READ_INTERVAL = 2000;
#endif

// Variables pour la simulation uniquement
float simTemp = 25.0;
bool simGoingUp = true;

// ==========================================
// FONCTIONS
// ==========================================

void setup() {
  Serial.begin(115200);
  delay(1000); // Petit temps pour ouvrir le moniteur
  Serial.println("\n--- Démarrage BuzzerTemp (V2 Debug) ---");

#ifdef SIMULATION_MODE
  Serial.println("MODE : SIMULATION");
  pinMode(LED_PIN, OUTPUT);

  // --- SIGNAL DE VIE (3 clignotements rapides) ---
  // Cela permet de vérifier que la LED marche bien au démarrage
  Serial.println("Test LED : Clignotement...");
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
  }
  Serial.println("Fin Test LED.");
#else
  Serial.println("MODE : REEL (Capteur DHT22 + Buzzer)");
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  dht.begin();
#endif

  // Connexion Wi-Fi
  Serial.print("Connexion au Wi-Fi ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);

  int attempt = 0;
  while (WiFi.status() != WL_CONNECTED && attempt < 20) {
    delay(500);
    Serial.print(".");
    attempt++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWi-Fi connecté !");
    Serial.print("Adresse IP : ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nPas de Wi-Fi. (Mode hors ligne)");
  }
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastReadTime >= READ_INTERVAL) {
    lastReadTime = currentMillis;
    float t = 0.0;

    // --- 1. ACQUISITION DE LA TEMPÉRATURE ---
#ifdef SIMULATION_MODE
    // Simulation : On monte vite de +2°C pour atteindre 30°C rapidement
    if (simGoingUp) {
      simTemp += 2.0;
      if (simTemp > 38.0)
        simGoingUp = false;
    } else {
      simTemp -= 2.0;
      if (simTemp < 20.0)
        simGoingUp = true;
    }
    t = simTemp;
    Serial.print("[SIMU] ");
#else
    // Lecture Réelle
    t = dht.readTemperature();
    if (isnan(t)) {
      Serial.println("Erreur lecture DHT !");
      return;
    }
#endif

    Serial.print("Temp : ");
    Serial.print(t);
    Serial.println(" °C");

    // --- 2. LOGIQUE D'ALERTE ---
    if (t >= TEMP_THRESHOLD) {
      // Si l'alarme n'était pas encore active
      if (!alarmState) {
        Serial.println("!!! ALERTE ACTIVÉE !!!");
        activateAlarm(true);
        alarmState = true;
      }

// En SIMULATION, on fait clignoter la LED à chaque lecture quand > 30°C
// pour être sûr que ça se voit, même si elle était déjà allumée.
#ifdef SIMULATION_MODE
      digitalWrite(LED_PIN, LOW);
      delay(100);
      digitalWrite(LED_PIN, HIGH);
#endif

      // Envoi notif si cooldown écoulé
      if (currentMillis - lastNotifTime >= NOTIF_COOLDOWN) {
        sendNotification(t);
        lastNotifTime = currentMillis;
      }
    } else if (t < (TEMP_THRESHOLD - TEMP_HYSTERESIS)) {
      if (alarmState) {
        Serial.println("Température OK. Arrêt alerte.");
        activateAlarm(false);
        alarmState = false;
      }
    }
  }
}

// Active soit le Buzzer (Réel) soit la LED (Simulation)
void activateAlarm(bool on) {
#ifdef SIMULATION_MODE
  digitalWrite(LED_PIN, on ? HIGH : LOW);
#else
  digitalWrite(BUZZER_PIN, on ? HIGH : LOW);
#endif
}

void sendNotification(float temp) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    Serial.println(">> Envoi Webhook...");

    // On pourrait ajouter la valeur de temp dans l'URL ici si l'API le permet
    http.begin(NOTIF_URL);
    int code = http.GET();

    if (code > 0)
      Serial.printf(">> Envoyé (Code: %d)\n", code);
    else
      Serial.printf(">> Erreur (%s)\n", http.errorToString(code).c_str());

    http.end();
  } else {
    Serial.println(">> Pas de Wi-Fi.");
  }
}
