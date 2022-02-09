/*
  Titre      : Clapet Servo Moteur Controle
  Auteur     : Bilel Belhadj
  Date       : 09/02/2022
  Description: le programme sert a controller un servo moteur qui varie de 0 a 90 avec un capteur de rotation
  Version    : 0.0.1
*/

#include <Arduino.h>
#include <Servo.h>
#include "MQTTConnector.h"
#include "WIFIConnector_MKR1000.h"

//#include "WIFIConnector_mkrwifi1010.h"

const int rotation_Sensor = A4 ;
const int servo_Moteur = 7 ;
int angle_Capteur = 0 ;
int angle_Moteur = 0;

Servo myservo ;


void setup() {
  myservo.attach(7);
  Serial.begin(9600);
   wifiConnect();                  
   MQTTConnect(); 
}

void loop() {
  angle_Capteur = analogRead(rotation_Sensor);
  angle_Moteur = map(angle_Capteur, 0, 1023, 0, 90);
  myservo.write(angle_Moteur);
  Serial.println("Position de moteur");
  Serial.println(angle_Moteur);
  
  
  appendPayload("valeur de capteur de rotation", angle_Capteur);
  appendPayload("Position de servo moteur", angle_Moteur);
  sendPayload();
  
}