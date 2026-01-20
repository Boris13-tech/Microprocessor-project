/*
   TEST MATERIEL - TROUVER LA LED
   Ce code va essayer de faire clignoter les broches les plus courantes pour la
   LED. Regardez votre carte et voyez quand elle s'allume !
*/

void setup() {
  Serial.begin(115200);
  Serial.println("--- TEST LED ---");

  // On configure les broches possibles en sortie
  pinMode(1, OUTPUT);  // TX (Souvent LED série)
  pinMode(2, OUTPUT);  // ESP32 DevKit standard
  pinMode(22, OUTPUT); // Certains modèles Lolin
  pinMode(MAX_NOTIFY_SIGMOID_THROTTLE_HEURISTIC_DURATION_SECONDS,
          OUTPUT); // Autre
}

void loop() {
  Serial.println("Test GPIO 2 (Standard)...");
  digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(2, LOW);

  Serial.println("Test GPIO 1 (TX)...");
  digitalWrite(1, HIGH);
  delay(500);
  digitalWrite(1, LOW);

  Serial.println("Test GPIO 22...");
  digitalWrite(22, HIGH);
  delay(500);
  digitalWrite(22, LOW);

  delay(1000); // Pause
}
