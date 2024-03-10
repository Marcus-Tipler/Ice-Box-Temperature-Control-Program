// Programme Arduino Uno pour la Glacière Autonome
// Membres de Groupe: Jinami Reyan, Fournier Alexis, Tipler Marcus.
// Compilleur / assembleur: Tipler Marcus.

#include <Wire.h> // Inclusion de librairie de la par de TinkerCad.
#include "rgb_lcd.h" // Inclure la Librairie pour l'écran LCD de simulation.
rgb_lcd lcd; // Déclaration du nom de l'écran LCD.

// Déclaration pour les pin(s) partie "void MesureU()":
float ubat; // Déclaration de la variable pour le calcule de la tension réelle reçu par le capteur.
const int TensionPin = A2; // Déclaration de l'emplacement du capteur de Tension (Pond diviseur de tension)
int N = 0; // Initialisation de la variable N, valeur du Convertisseur Analogique Numérique
float tension; // Déclaration de la variable de Tension; "Tension"

// Déclaration pour les pin(s) partie "void MesureI()":
int sensorPin = A1; // Déclaration integer pour le capteur d'entensité.
int sensorValue = 0; // Déclaration de la variable "sensorValue" à 0.
float tensionI; // Déclaration de la variable "tensionI" pour le calcule de la Tension de Capteur D'Intensité.
float intense; // Déclaration de la variable "intense" pour le calcule de la valeur d'intensité reçu par le capteur d'intensité.
float offset; // Déclaration de l'offset "offset" pour mettre a niveau les valeurs de capteurs au demmarage du système.

// Déclaration pour les pin(s) partie "void Puissance()":
float puissance; // Déclaration de la variable de puissance pour le calcule de puissance.

// Déclaration pour les pin(s) partie "void Energy()":
float timer; // Déclaration de variable "timer" pour le fonctionnement de l'horloge intégré de l'Arduino.
float energy; // Déclaration de variable "energy" pour le calcule de l'énergie utilisé par le système.
float energycons; // Déclaration de la variable "energycons" pour le calcule de la consomation totale d'énergie.
float CalcEmoy; // Déclaration de la variable pour le calcule de la moyenne d'énergie (celle d'avant et celle actuelle).

// Déclaration pour les pin(s) partie "void MesureDegC()":
int tempCons = A3;
int relais = 5; // Déclaration de la variable Relais "relais".
int valeurAdcMesure; // Déclaration de la variable ADC detecter par le capteur de Température.
int valeurAdcConsigne; // Déclaration de la variable de Consigne mise par l'utilisateur.
float TensionT; // Déclaration de la variable de Tension du capteur de Température.
float Temperature; // Déclaration de la variable de Température Calculé par le capteur de Température.
float Consigne; // Déclaration de la variable du capteur de consigne calculé.
int StateRelais;

// Déclarations Integer pour LCD:
const int colorR = 255; // Déclaration de la couleur Rouge dans le LCD (R).
const int colorG = 0; // Déclaration de la couleur Verte dans le LCD (G).
const int colorB = 100; // Déclaration de la couleur Bleue dans le LCD (B).

// Déclaration Long pour Horloge Intégré, soit Millis:
unsigned long startMillis = 0; // Déclaration du debut de la fonction Millis.
unsigned long previousMillis = 0; // Déclaration de "L'avant Fonctionnement" de la fonction Millis.
const unsigned long period = 1000; // Déclaration de la valeur attendu de L'Horloge Intégré Millis.
boolean Running = false; // Déclaration du debut du fonctionnement du Timer pour la variable prédéclaré: (timer).
unsigned long StartTime = 0; // Déclaration du Début de la fonction Millis.
unsigned long StopTime = 0; // Déclaration de la Fin de la fonction Millis. (0 = Jamais).

//Millis pour Graph Mesure
unsigned long startMillis2 = 0; // Déclaration du debut de la fonction Millis.
unsigned long previousMillis2 = 0; // Déclaration de "L'avant Fonctionnement" de la fonction Millis.
const unsigned long period2 = 1000; // Déclaration de la valeur attendu de L'Horloge Intégré Millis.
unsigned long MesureTime2 = 5000;

// Le "void setup()" soit les préparations et déclarations avant le loop:
void setup(){
  Serial.begin(9600); // Commencer le Serial Moniteur avec un Baudrate de 9600.
  sensorValue = analogRead(sensorPin); // Déclaration de valeur que "sensorValue" vaut la lecture analogique de "sensorPin".
  tensionI = sensorValue * 5.0/1024.0; // Déclaration de valeur que "tensionI" vaut "sensorValue" suivis d'une fonction mathématiques déterminé par les tests réelles de la glacière.
  offset = (tensionI - 2.5) / 0.185; // Déclaration d'un "Off-set" qui permet de calibrer les valeurs au démarrage.
  lcd.begin(16, 2); // Commencer / Démarrer l'écran LCD.
  lcd.setRGB(colorR, colorG, colorB); // Dire a l'écran LCD d'appliquer les couleurs de #"Déclaration Integer poir LCD".
  CalcEmoy = 0; // Met la valeur de départ de la moyenne a 0 pour le calcule de consomation totale d'énergie.
  startMillis = millis(); // Démarre l'Horloge intégré de l'arduino.
  pinMode(relais, OUTPUT); // Déclare le fait que le Relais: "relais" soit une Sortie.
}

// Le "void loop()" soit les fonctions a répéter a l'infini:
void loop(){ 
  lcd.display(); // Faire fonctionner l'écran et le préparré pour un flux de données.
  MesureU(); // Appelle a la Fonction de Tension: "void MesureU()".
  MesureI(); // Apelle a la Fonction d'intensité': "void MesureI()".
  Puissance(); // Apelle a la Fonction de Puissance: "void Puissance()".
  Energie(); // Apelle a la Fonction de la consomation énergétique: "void Energie()".
  MesureDegC(); // Apelle a la Fonction de Température: "void MesureDegC()".
  //Serial.println("--------------------------------"); // Écrit une ligne de séparation pour meilleur lecture dans le Serial Moniteur.
  delay (1000); // Fait un delay de fonctionnement du programme entier pendant une seconde soit 1000ms.
}

// Fonction de la Tension "void MesureU()":
void MesureU(){
  N = analogRead(TensionPin); // Déclare la valeur N en tant que la lecture analogique de la Tension du capteur de tension.
  tension = N*5.0/1024.0; // Déclare la valeur de tension avec N et la formule mathématiques trouver pour la conversion de la tension lissible de l'arduino vers la trension réelle.
  //Serial.println("Tension Mesure = " + String(tension) + " V"); // Impression de la mesure de tension sur le Serial Moniteur.
  ubat = tension*2.4; // Déclare que "ubat" vaut la valeur de "tension" avec ca formaule mathématique pour le transformé en tension réelle de la batterie du produit.
  //Serial.println("UBatterie = " + String(ubat) + " V"); // Impression de la valeur réelle de la batterie sur le serial moniteur.
}

// Fonction de l'Intensité "void MesureI()":
void MesureI(){
  sensorValue = analogRead(sensorPin); // Déclare que la valeur "sensorValue" vaut une lecture analogique de "sensorPin".
  tensionI = sensorValue * 5.0/1024.0; // Déclare que "tensionI" vaut "sensorValue" et une fonction mathématiques trouvé sur les testes réelles sur Excel.
  intense = ((tensionI - 2.5) / 0.185) - offset; // Déclare que "intense" vaut "tensionI" dans une formule mathématiques moins son Offset pour le paramettrer d'une manière précise.
  if (intense < 0) { // Si la tension est Inférieur a 0, faire:
    intense = 0; // Transformer une intensité négative a 0 pour pas mal-informer l'utilisateur de ca consomation.
  }
  //Serial.println("Adc : " + String(sensorValue)); // Impression de la valeur ADC du capteur d'intensité sur le serial moniteur.
  //Serial.println("TensionI : " + String(tensionI) + " V"); // Impression de la valeur de tension reçu par le capteur d'intensité sur le serial moniteur.
  //Serial.println("Intensité : " + String(intense) + " A"); // Impression de la valeur d'Intenisité calculer par le capteur d'intensité sur le serial moniteur.
}

// Fonction de la Puissance "void Puissance()":
void Puissance(){
  puissance = (ubat * intense); // Calcule et Déclaration de la puissance avec les variables de "ubat" et de "intense" qui représente la tension et l'intensité (P = U*I).
  //Serial.println("Psys " + String(puissance) + " W"); // Impression de la valeur de puissance sur le serial moniteur.
}

// Fonction de l'Énergie "void Energie()":
void Energie(){
  lcd.setCursor(0, 1); // Paramettrer le Cursor de l'écran LCD pour la seconde ligne.
    unsigned long currentTime = millis(); // Mettre temps actuelle sur Millis (l'heure).
    if (! Running) // Detecter si le Boolean est actuellement en marche.
  {
    StartTime = currentTime; // Quand l'évennement de départ est acquis, il faut paramettrer le temps départ au temps actuelle.
    Running = true; // et activer le fonctionnement du Boolean.
  }
timer = ((currentTime - StartTime)/1000); // Déclare la variable de "timer" qui vaut le temps actuelle - le temps de depart diviser par mille.
  if (! Running); // Detecter si le Boolean est actuellement en marche.
  {
    //Serial.println("Temps de fonctionnement = " + String(timer) + " s"); // Impression du temps de fonctionnement de l'arduino.
  }
  energy = (puissance * 60)/3600; // Calcule la consomation d'énergie du système.
  energycons = (CalcEmoy + energy); // Calcule l'énergie totale consommé du système.
  CalcEmoy = energycons; // Remplacer la valeur de CalcEMoy avec celle de Energycons pour ajouter a la consomation totale au prochain loop du programme.
  //Serial.println("Energy = " + String(energy) + " Wh"); // Impression de la consomation d'énergie actuelle du système dans le Serial Moniteur.
  //Serial.println("Energy Consomme = " + String(energycons) + " Wh"); // Impression de l'énergie totale consommé du système dans le Serial Moniteur.
  lcd.print("Cons =  " + String(energycons) + " Wh "); // Impression de la consomation actuelle du système sur le LCD.
}

// Fonction de la Température "void MesureDegC()":
void MesureDegC(){
  unsigned long currentTime2 = millis();
  lcd.setCursor(0, 0); // Paramettrer le Cursor de l'écran LCD pour la première ligne.
  valeurAdcMesure = analogRead(A0); // Déclarer la vraiable "valeurAdcMesure" en tant que la lecture analogique du capteur de température.
  //Serial.println("N = " + String(valeurAdcMesure)); // Impression de la valeur Adc du capteur de température sur le Moniteur Série.
  TensionT = ((valeurAdcMesure*5.0)/1024); // Déclarer la variable de TensionT par une fontion mathématiques avec les valeurs adc mesurées "valeurAdcMesure".
  Temperature = (TensionT-0.5)/0.01; // Déclarer la température "Temperature" par une fonction mathématiques avec l'utilité de la Tension récupéré du capteur.
  //Serial.println(Temperature); // Impression de la valeur de température en Degrées Celcius sur le Serial Moniteur.
  //Serial.println("TensionTemp = " + String(TensionT) + " V"); // Impression de la valeur de Tension du capteur de température dans le Serial Moniteur.
  lcd.print("Temp = " + String(Temperature) + " DegC"); // Impression de la température calculé du capteur de température sur la première ligne de l'Écran LCD.
  valeurAdcConsigne = 15; // Déclarer la valeur consigne ADC avec la lecture analogique de "tempCons".
  Consigne = 14; // Déclarer la consigne avec la valeur de consigne ADC et une fonctione mathématiques.
  //Serial.println("Consigne = " + String(Consigne) + " DegC"); // Impression de la Consigne mise par l'utilisateur sur le Serial Moniteur.

  if (Consigne > Temperature) { // Si la consigne est supérieur a la température, faire:
    digitalWrite (relais, LOW); // Allumer le relais pour refroidire la glacière.
    StateRelais = 0;
  } else { // Si la consigne est inférieur a la température, faire:
    digitalWrite (relais, HIGH); // Éteindre le relais pour laisser la glacière éteinte.
    StateRelais = 1;
  }
  if(currentTime2 - previousMillis2 >= MesureTime2)
    //Si le Clignotant Gauche du système est allumer et que L'horloge actuelle - l'horloge précédent du clignotant
    //est superieur ou égale au temps allumé de la DEL Gauche, faire les commandes suivantes.
      {
        Serial.print("Temperature:");
        Serial.println(Temperature);

        Serial.print("Etat:");
        Serial.println(StateRelais);

        Serial.print("Consigne:");
        Serial.println(Consigne);

        previousMillis2 = currentTime2;
        }
}

