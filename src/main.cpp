/*
* Copyright (C) 2017 Orange
*
* This software is distributed under the terms and conditions of the 'Apache-2.0'
* license which can be found in the file 'LICENSE.txt' in this package distribution
* or at 'http://www.apache.org/licenses/LICENSE-2.0'.
*/

/* Orange LoRa Explorer Kit
*
* Version:     1.0-SNAPSHOT
* Created:     2017-02-15 by Karim BAALI
* Modified:    2017-04-21 by Halim BENDIABDALLAH
*			         2017-05-09 by Karim BAALI
*              2017-10-27 by Karim BAALI
*/

#include <OrangeForRN2483.h>

#define debugSerial SerialUSB

#define DHTPIN A8     // what pin we're connected to

/**
 * Déclaration des constantes permettant
 * de définir les broches servant pour
 *  la synchronisation des emissions
 */
static const uint32_t raspiCommande=11;
static const uint32_t finSynchro=8;
static const uint32_t sodaqPrete=12;

// The following keys are for structure purpose only. You must define YOUR OWN

/**
 * Enregistrement de l'AppEUI et l'AppKey définie dans Live Objects
 */
const uint8_t appEUI[8] = { 0xA8, 0x61, 0x0A, 0x33, 0x35, 0x39, 0x74, 0x07 };
const uint8_t appKey[16] = { 0xDA, 0xC5, 0x4C, 0xC7, 0x6D, 0x44, 0x31, 0xD0, 0xA6, 0x0F, 0x12, 0xB1, 0xED, 0xF6, 0x3A, 0x2F };


bool first = true;

bool joinNetwork()
{
    OrangeForRN2483.setDataRate(DATA_RATE_1); // Set DataRate to SF11/125Khz
    return OrangeForRN2483.joinNetwork(appEUI, appKey);
}

void setup() {
    debugSerial.begin(57600);

    /**
     * Définition des connecteur de la carte
     * en entrée/sortie
     */
    pinMode(raspiCommande, INPUT);
    pinMode(finSynchro, OUTPUT);
    pinMode(sodaqPrete, OUTPUT);

    /**
     * Positionne les sortie à l'état haut
     */
    digitalWrite(finSynchro,HIGH);
    digitalWrite(sodaqPrete,HIGH);

    while ((!debugSerial) && (millis() < 10000)) ;

    delay(2000);

    debugSerial.println("2000ms apres, on va commencer");

    OrangeForRN2483.init();
}

bool SendLoRaMessage()
{
    const uint8_t size = 1;
    uint8_t port = 5;
    uint8_t data[size] = { 0x48}; // Payload d'un Octet représentant le caractère 'A' en Ascii

    return OrangeForRN2483.sendMessage(data, size, port); // send unconfirmed message
}

void loop() {

    if(first)
    {
        first = false;
        debugSerial.println("Join Request");
        bool res = joinNetwork();
        if(res)
        {
            digitalWrite(sodaqPrete, LOW);  // Prévient la Raspberry que la carte est prête

            while(digitalRead(raspiCommande));  // Attends la demande d'envoi

            /**
             * Debut de l'émission LoRa
             */
            debugSerial.println("Join Success");
            OrangeForRN2483.enableAdr();

            debugSerial.println("envoie Payload");
            SendLoRaMessage();
            /**
             * Fin emission LoRa
             */

            digitalWrite(finSynchro,LOW);   // Averti la Raspberry que l'emission a eu lieu

        }
        else
            debugSerial.println("Join Failed");

        debugSerial.println("Program Finished");
    }
}


