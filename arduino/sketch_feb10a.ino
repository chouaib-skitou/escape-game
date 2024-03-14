#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "chouaib";
const char* password = "chouaib2021";

// Static IP configuration
// IPAddress staticIP(192, 168, 1, 100); 
// IPAddress gateway(192, 168, 1, 1); 
// IPAddress subnet(255, 255, 255, 0);  
// IPAddress primaryDNS(192, 168, 1, 1);
// IPAddress secondaryDNS(0, 0, 0, 0);

WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "ESP32 Web Server");
}

void handleLEDOn() {
  digitalWrite(LED_BUILTIN, HIGH); // Allume la LED
  server.send(200, "text/plain", "LED is ON");
}

void handleLEDOff() {
  digitalWrite(LED_BUILTIN, LOW); // Éteint la LED
  server.send(200, "text/plain", "LED is OFF");
}

unsigned long lastCheckTime = 0; // Stocke le dernier moment où la connexion a été vérifiée
const long interval = 10000; // Interval de temps pour vérifier la connexion (10 secondes)

void setup() {
  Serial.begin(115200); // Initialise la communication série pour le débogage

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); // Assurez-vous que la LED est éteinte au démarrage

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("WiFi connecté");
  // IPAddress ip = WiFi.localIP();
  // Serial.print("Adresse IP : ");
  // Serial.println(ip);

  server.on("/", handleRoot);
  server.on("/ledon", handleLEDOn);
  server.on("/ledoff", handleLEDOff);

  server.begin();
}

void loop() {
  // Gère les clients du serveur web
  server.handleClient();

  // Vérifie si l'intervalle de 10 secondes est passé
  unsigned long currentTime = millis();
  if (currentTime - lastCheckTime >= interval) {
    // Met à jour le dernier temps de vérification
    lastCheckTime = currentTime;

    // Vérifie l'état de la connexion WiFi
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi déconnecté, tentative de reconnexion...");
      WiFi.reconnect();
      
      // Attend un peu pour la reconnexion
      int maxAttempts = 5;
      while (WiFi.status() != WL_CONNECTED && maxAttempts-- > 0) {
        delay(1000); // Attend 1 seconde entre chaque tentative
        Serial.print(".");
      }
      
      if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Reconnecté au WiFi.");
      } else {
        Serial.println("Échec de la reconnexion au WiFi.");
      }
    }
  }
}


// void setup() {
//   pinMode(LED_BUILTIN, OUTPUT);
//   digitalWrite(LED_BUILTIN, LOW); // Assurez-vous que la LED est éteinte au démarrage
  
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//   }

//   server.on("/", handleRoot);
//   server.on("/ledon", handleLEDOn);
//   server.on("/ledoff", handleLEDOff);

//   server.begin();
// }

// void loop() {
//   server.handleClient();
// }


// #include <WiFi.h>
// #include <WebServer.h>

// const char* ssid = "...";
// const char* password = "chouaib2021";

// // const char* ssid = "Freebox-chouaib";
// // const char* password = "HamzaSkitou@2811@1992";
// #define BUTTON_PIN 0
// void setup() {
//   // Initialiser la LED intégrée comme une sortie
//   pinMode(LED_BUILTIN, OUTPUT);
//   pinMode(BUTTON_PIN, INPUT_PULLUP); 
  
//   // Démarrer la communication série à 115200 bauds
//   Serial.begin(115200);
// }

// void loop() {
//   static bool lastButtonState = HIGH; // Stocke l'état précédent du bouton
//   bool currentButtonState = digitalRead(BUTTON_PIN); // Lire l'état actuel du bouton

//   // Vérifier si des données sont disponibles sur le port série
//   if (Serial.available() > 0) {
//     // Lire la commande jusqu'à ce qu'un saut de ligne (\n) soit détecté
//     String command = Serial.readStringUntil('\n');
    
//     // Supprimer les espaces blancs ou les caractères de nouvelle ligne en excès
//     command.trim();
    
//     // Comparer la commande reçue et agir en conséquence
//     if (command == "LED_ON") {
//       // Allumer la LED intégrée
//       digitalWrite(LED_BUILTIN, HIGH);
//       Serial.println("LED is ON");
//     } else if (command == "LED_OFF") {
//       // Éteindre la LED intégrée
//       digitalWrite(LED_BUILTIN, LOW);
//       Serial.println("LED is OFF");
//     } else if (command == "SENSOR_STATE") {
//       Serial.println("SENSOR_TRUE");
//     } else if (command == "BTN_STATE") {
//       // Vérifie si l'état du bouton a changé
//       if (currentButtonState != lastButtonState) {
//         // Mettre à jour l'état précédent avec l'état actuel
//         lastButtonState = currentButtonState;
        
//         // Vérifier si le bouton est pressé
//         if (currentButtonState == LOW) {
//           Serial.println("Button Pressed");
//         } else {
//           Serial.println("Button Released");
//         }
//       }
//     } else {
//       // Envoyer un message d'erreur si la commande est inconnue
//       Serial.println("Unknown command");
//     }
//   }

  
// }
