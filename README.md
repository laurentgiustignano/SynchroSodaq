# LiveObject IoT Client - OrangeForRN2483 library


Pour accéder au dépôt de la bibliothèque d'origine [Suivre ce lien](https://github.com/Orange-OpenSource/Orange-ExpLoRer-Kit-for-LoRa.git)

---

## Ce dépôt représente les développements effectués dans le cadre de l'agrégation SII-II Session 2022.

---

# LiveObjects Iot Device Synchro

L'objectif du programme Syncho est de déterminer la durée de prise en 
charge par la plateforme Live Objects d'une communication avec un 
équipement LoRa. Ce programme est complémentaire du projet [SynchroMqtt](https://github.com/laurentgiustignano/SynchroMqtt) qui s'occupe 
de synchroniser les deux programmes. Cette tâche est effectuée par la lecture de l'état bas sur les broches de communication définies.

La carte Sodaq ExpLoRer attend une demande d'emission pour émettre le caractère 'A'. Lorsque l'emission est effectuée, la carte met à l'état bas le signal `finSynchro`.

---
### Procédure pour synchroniser l'émission  d'une carte Sodaq Explorer et d'un RaspberryPi

1. Relier les masses ensemble. Par exemple la broche 6 du GPIO avec la broche 14 de la carte Sodaq.
2. Relier les broches `11`, `13`, `15` du Raspberry Pi à la carte Sodaq ExpLoRer respectivement aux broches `8`, `11`, `12`. Attention, les broches numérotées du GPIO correspondent à la dénomination WiringPi suivante :  `GPIO0`, `GPIO2`, `GPIO3`
3. Placer dans les variables `appKey` et `appEUI` les valeurs enregistrées dans Live Objects pour cet équipement. 
4. Compiler le programme. Si le Raspberry Pi est prêt à exécuter le programme de `synchro`, lancer l'upload dans la carte Sodaq.
5. Ouvrir le terminal série à la fin de l'upload pour consulter les affichages du mode `debug`. Lancer le programme `synchro` sur le Raspberry Pi.

---
### Analyse des résultats

1. Se connecter sur [Live Objects](https://liveobjects.orange-business.com/#/login).
2. Consulter le timestamp de l'émission LoRa et le comparer au timestamp contenu dans le payload mqtt.
