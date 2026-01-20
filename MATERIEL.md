# 🛒 Liste du Matériel Requis

Pour réaliser ce projet en laboratoire, chaque poste étudiant doit disposer des éléments suivants :

| Quantité | Élément | Spécifications Recommandées | Notes Importantes |
| :---: | :--- | :--- | :--- |
| **1** | **Carte ESP32** | ESP32 DevKit V1 (30 ou 38 pins) | Le "cerveau" du projet. Vérifiez que les broches rentrent bien dans la breadboard (parfois trop larges, il faut coupler 2 breadboards ou utiliser un seul côté). |
| **1** | **Capteur Température** | **DHT22** (AM2302) | Préférable au DHT11 (trop imprécis). <br>✅ **Conseil** : Prenez la version "Module" (sur un petit PCB avec 3 broches). Il intègre déjà la résistance nécessaire. |
| **1** | **Buzzer** | **Type : ACTIF** (5V ou 3.3V) | ⚠️ **Crucial** : Il doit être **ACTIF**. <br>Test simple : Connectez-le sur une pile. S'il sonne continu, c'est bon. S'il fait juste "clac", c'est un passif (il faudra changer le code). |
| **1** | **Breadboard** | 400 ou 830 points | Pour connecter les composants sans soudure. |
| **5-10** | **Câbles Dupont** | Mâle-Mâle (et Mâle-Femelle) | Pour les connexions. Prévoyez de différentes couleurs (Rouge=VCC, Noir=GND). |
| **1** | **Câble USB** | Micro-USB (Data + Power) | ⚠️ Beaucoup de câbles bon marché ne font QUE la charge. Assurez-vous qu'il permet le transfert de données. |

## 💡 Détails pour l'encadrant (Approvisionnement)

1.  **Pourquoi DHT22 et pas DHT11 ?**
    *   DHT11 : Précision ±2°C, Plage 0-50°C.
    *   DHT22 : Précision ±0.5°C, Plage -40-80°C.
    *   *Pour un TP sur des seuils (ex: 30°C), le DHT11 est trop imprécis.*

2.  **Comment distinguer Buzzer Actif vs Passif ?**
    *   **Actif** : Souvent un autocollant sur le dessus, dessous scellé (résine noire).
    *   **Passif** : Souvent circuit vert visible dessous.

3.  **Alternative si pas de Wi-Fi en salle de TP**
    *   Le code fonctionnera quand même en mode "Local" (Buzzer uniquement). 
    *   Vous pouvez utiliser le **Partage de connexion** d'un smartphone pour créer un réseau Wi-Fi temporaire pour tester les notifications.
