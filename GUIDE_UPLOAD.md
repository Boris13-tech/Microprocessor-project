# 🛠️ Guide : Comment mettre le code dans l'ESP32

Suivez ces 4 étapes simples. Ne sautez rien !

## 1. Ouvrir le Code
1.  Lancez le logiciel **Arduino IDE**.
2.  Allez dans **Fichier** > **Ouvrir...**
3.  Cherchez le fichier :
    `C:\Users\OWANDJA BORIS\.gemini\antigravity\scratch\BuzzerTempNotifications\BuzzerTempNotifications.ino`
4.  Cliquez sur **Ouvrir**.

## 2. Choisir la Carte et le Port
C'est l'étape critique. L'ordinateur doit savoir à qui il parle.
1.  Branchez votre ESP32 au PC (si ce n'est pas fait).
2.  En haut de la fenêtre Arduino, il y a une liste déroulante (souvent marquée "Select Board").
3.  Cliquez dessus et choisissez :
    *   **Carte** : `DOIT ESP32 DEVKIT V1` (ou `ESP32 Dev Module`).
    *   **Port** : `COM3`, `COM4`... (Celui qui apparaît quand vous branchez le câble).
    *   *Si le Port est grisé : changez de câble USB !*

## 3. Téléverser (Upload)
1.  Cliquez sur la **Flèche vers la droite** (➡️) en haut à gauche.
2.  Regardez tout en bas de la fenêtre (zone noire).
3.  Vous allez voir défiler du texte orange/blanc.
4.  Attendez de voir : **"Done uploading."** (ou Téléversement terminé).
    *   *Si ça bloque sur "Connecting...", appuyez 2 secondes sur le bouton `BOOT` de la carte ESP32.*

## 4. Voir le Résultat
1.  Cliquez sur la **Loupe** (🔎) tout en haut à droite.
2.  Une fenêtre s'ouvre : c'est le **Moniteur Série**.
3.  En bas de cette fenêtre, vérifiez la vitesse : **115200 baud**.
4.  Appuyez une fois sur le bouton `EN` (Reset) de votre carte ESP32.
5.  👀 **Regardez !** Vous devez voir le texte "Démarrage..." et la température qui change.

---
**Besoin d'aide ?**
Si vous avez une erreur rouge à l'étape 3, copiez-collez l'erreur ici !
