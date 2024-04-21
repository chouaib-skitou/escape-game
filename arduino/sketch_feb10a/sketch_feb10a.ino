#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>

// Network credentials
const char* ssid = "Freebox-chouaib";
const char* password = "HamzaSkitou@2811@1992";
const char* djangoURL = "http://192.168.1.30:8000/api/update_ip";

// Create a web server object that listens for HTTP request on port 80
WebServer server(80);

unsigned long lastFlashTime = 0;
int flashCount = 0;
int flashLimit = 0;
int flashInterval = 1000; // Default to 1 second
int doorNumberFlashing = 0;

void handleRoot() {
  server.send(200, "text/plain", "ESP32 Web Server");
}

void turnLEDOn() {
  digitalWrite(LED_BUILTIN, HIGH);
}

void turnLEDOff() {
  digitalWrite(LED_BUILTIN, LOW);
}

void handlePing() {
  server.send(200, "text/plain", "Pong");
}

void handleSensorStatus(int sensor_number) {
  bool sensor_status = digitalRead(sensor_number);  // Example for obtaining sensor status
  server.send(200, "application/json", "{\"status\":\"" + String(sensor_status ? "activated" : "deactivated") + "\"}");
}


void handleLEDControl(int door, bool open) {
  if (open) {
    switch (door) {
      case 1:
        turnLEDOn();
        flashLimit = 0; // No flashing, just stay on
        break;
      case 2:
        doorNumberFlashing = 2;
        flashInterval = 1000; // Flash every second
        flashLimit = -1; // Infinite flash
        break;
      case 3:
        doorNumberFlashing = 3;
        flashInterval = 1000; // Flash two times every second
        flashLimit = -1; // Infinite flash
        break;
      case 4:
        doorNumberFlashing = 4;
        flashInterval = 2000; // Flash three times every two seconds
        flashLimit = -1; // Infinite flash
        break;
    }
    lastFlashTime = millis(); // Reset timer
    flashCount = 0; // Reset flash counter
  } else {
    turnLEDOff();
    flashLimit = 0; // Stop flashing
  }
  server.send(200, "text/plain", "Door " + String(door) + (open ? " opened." : " closed."));
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  turnLEDOff();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  HTTPClient http;
  http.begin(djangoURL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String httpRequestData = "ip=" + WiFi.localIP().toString();
  int httpResponseCode = http.POST(httpRequestData);
  http.end();

  server.on("/", handleRoot);
  server.on("/action/door_1/open", []() { handleLEDControl(1, true); });
  server.on("/action/door_1/close", []() { handleLEDControl(1, false); });
  server.on("/action/door_2/open", []() { handleLEDControl(2, true); });
  server.on("/action/door_2/close", []() { handleLEDControl(2, false); });
  server.on("/action/door_3/open", []() { handleLEDControl(3, true); });
  server.on("/action/door_3/close", []() { handleLEDControl(3, false); });
  server.on("/action/door_4/open", []() { handleLEDControl(4, true); });
  server.on("/action/door_4/close", []() { handleLEDControl(4, false); });

  server.on("/status/sensor_1", []() { handleSensorStatus(1); });
  server.on("/status/sensor_2", []() { handleSensorStatus(2); });
  server.on("/status/sensor_3", []() { handleSensorStatus(3); });
  server.on("/status/sensor_4", []() { handleSensorStatus(4); });

  server.on("/ping", handlePing);

  server.begin();
}

void loop() {
  server.handleClient();

  // Handle LED flashing logic
  if (flashLimit != 0 && (millis() - lastFlashTime >= flashInterval)) {
    if (digitalRead(LED_BUILTIN) == HIGH) {
      turnLEDOff();
    } else {
      turnLEDOn();
      flashCount++;
    }
    lastFlashTime = millis();
    if (flashLimit > 0 && flashCount >= flashLimit) {
      turnLEDOff(); // Optionally turn off after limit
      flashLimit = 0; // Stop flashing
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
