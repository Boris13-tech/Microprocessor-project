# Guide de Configuration des Notifications (Telegram / CallMeBot)

Pour recevoir des notifications sur votre téléphone sans compliquer le code Arduino, nous utilisons le service gratuit **CallMeBot**. C'est une passerelle qui permet d'envoyer des messages Telegram via une simple URL (Webhook).

## Étape 1 : Obtenir votre clé API Telegram

1.  Ouvrez l'application **Telegram** sur votre téléphone.
2.  Cherchez le contact **`@CallMeBot_txtbot`** (assurez-vous que c'est bien celui-ci, il y a des imitations).
3.  Lancez la conversation (cliquez sur **Démarrer** ou **Start**).
4.  Envoyez le message : `/start`
5.  Le bot va vous répondre avec votre **API Key** (une suite de chiffres ou lettres) et un lien d'exemple.

> **Note :** Si le bot ne répond pas immédiatement, essayez d'attendre une minute ou réessayez. Parfois les serveurs gratuits sont chargés.

## Étape 2 : Tester l'URL dans votre navigateur

Avant de mettre le code dans l'Arduino, testez le lien sur votre PC.
L'URL ressemble à ceci :

```
https://api.callmebot.com/text.php?user=@votre_username&text=Test+Buzzer
```
*Ou selon la version du bot, parfois c'est via numéro de téléphone :*
```
https://api.callmebot.com/signal/send.php?phone=+33612345678&apikey=123456&text=Test
```

**Utilisez le lien fourni par le Bot dans sa réponse.** :
1. Copiez le lien donné par le Bot.
2. Collez-le dans votre navigateur (Chrome/Edge).
3. Changez le texte à la fin pour tester.
4. Si vous recevez le message sur Telegram, c'est bon !

## Étape 3 : Intégrer dans le code Arduino

1.  Ouvrez le fichier `BuzzerTempNotifications.ino`.
2.  Repérez la ligne :
    ```cpp
    String NOTIF_URL = "https://example.com/webhook?event=temp_alert";
    ```
3.  Remplacez l'URL entre guillemets par **votre URL CallMeBot** qui a fonctionné.

**Attention aux caractères spéciaux !**
Dans l'URL, les espaces doivent être remplacés par `%20` ou `+`.
Exemple : `Alerte+Temperature+Trop+Haute`

---
## Alternative : IFTTT (Si Telegram ne marche pas)

Si vous préférez IFTTT :
1. Créez une applet **Webhooks** -> **Notifications** (ou Email/SMS).
2. L'URL sera du type : `https://maker.ifttt.com/trigger/{event_name}/with/key/{votre_cle_ifttt}`
3. Collez cette URL dans le code Arduino.
