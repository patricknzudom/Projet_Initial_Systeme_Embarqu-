# Projet initial de système embarqué
Projet Inital de Système Embarqué INF1900 Polymtl

## Introduction

Ce fichier explique le projet initial de système embarqué du INF1900. Le microcontrôleur AVR ATmega324PA est utilisé pour réaliser l'épreuve, avec 2 robots.

Voici les différents objectifs de l'épreuve, pour chacun des deux robot :

Robot 1:

Etape 1: trouver marqueur rouge au centre de la boite
- avancer ou reculer jusqu'au point rouge

Etape 2: s'orienter vers l'ouverture de la boite
- utilise capteur de distance
- faire une rotation stationnaire jusqu'a ce que la capteur distance capte tres grande distance
- utiliser le temps pris pour tourner pour identifier sa position initiale

Etape 3: Attente
- allumer LED rouge
- ouvrir interrupts du boutton
- attendre interrupt du boutton
- activer sequence de son

Etape 4: Reception
- activer la reception IR 
- determiner quand la redception est complete --> etape 5
- retour a attente si erreur de transmission 

4.1: erreur de transmission
- arret de reception 
- emetre sond grave 
- retour a etat attente

Etape 5: RS32
- arret de reception
- allumer LED vert
--> connecter au pc et serieViaUSB option -l 
- activer interrupts boutton
- attendre interrupts boutton
- envoyer contenu par rs232
- clignoter vert a 5 Hz pendant l'envoi
- arret jusqu a fin de transmission
- retour a etape 5


Robot 2:

ligne 0:
avancer jusqu'à tournant
prendre en note le temps nécessaire pour faire la ligne 0 -- >(vitesse)
changer à ligne 1

ligne 1:
avancer jusqu'à tournant
changer à identification

identifications 1
calculer distance d1 = (temps * vitesse) + d1
suit le tournant et calcul(long) jusqua tournant ou brisure
prendre en note distance avant fin (temp)
|| si brisure(fin du chemin): changer a segment top #ajouter des numero de segments --> etat different a selectionner avec compteur
|| sinon(longueur trop longue) changer a ligne intermediaire

segment top:
cree objet segment?
donner attribut top?
donner attribut de numero?
sauvegarder longueur(long) et distance(d1) --> attribut distance et longueur
demi tour
avancer jusqu'à turn --> forcer un turn droit
retour a ligne 1

Ligne intermediaire:
avancer jsuqua turn 
changer a ligne 2

ligne 2:
...

id2:
...
||si turn: changer a ligne finale

segment bot:
...

ligne finale:
avancer jusqu'à turn --> forcer un turn gauche
avancer jusqu'à blanc
ajuster orientation

changer à attente

attente:
... même que robot 1
si bouton interrupt --> IR
si bouton blanc --> transmission rs232

Etape 5 IR
- transmettre données par IR

Etape 6 trnasmission rs232
- identique au robot 1 (sans image du robot 1 ni signature)


## Configuration du Projet

### Matériel Requis

- Microcontrôleur AVR ATmega324PA
- Plateforme de développement ou breadboard
- Connecteurs et câbles assembles avec un sertissage
- Composants périphériques : transducteur piezoelectrique, capteur de suivi de ligne MakerLine, capteur infrarouge
- Programmateur AVR Atmega8

### Environnement de Développement

- Système d'exploitation : Linux avec distribution fedora.
- Utilisation du langage de programmation C++.

## Librairie

### Elements de la librairie
Les éléments principaux de notre librairie comprennent :

- `Led`: Gestion des LED pour les indicateurs visuels.
- `Sonorite`: Generation de sons pour les modes du robot.
- `CapteurDistance`: Détection de la distance entre robot et la boite.
- `Can`: Lecture des entrées sur une des broches du PortA et conversion analogique-numérique pour retourner une valeur.
- `Memoire_24`: Exemple d'utilisation d'une mémoire EEPROM I2C.
- `Wheels`: Permet le réglage de la vitesse et de la direction des roues du robot via la modulation PWM grâce à un objet Timer.
- `Communication`: Communication série (UART) entre le microcontrôleur ATmega324PA et d'autres dispositifs.
- 'Rs232 ou Rs232Robot1': Permet d'envoyer le schema par RS232 au pc lorsque connecte au robot. Il faut ensuite utiliser serieViaUSB.
- 'SIRC': Permet d'envoyer les donnees par infrarouge

## Projet

Pour lancer le projet, il est nécessaire d'installer le code dans la mémoire flash du robot en utilisant la commande suivante :

$ make install

# Organisation du Projet

Ce projet est organisé en plusieurs composants clés, chacun remplissant un rôle spécifique dans la réalisation des objectifs du système embarqué.

## Répertoire `app1`

Le répertoire app1 abrite le code source principal de l'application du premier robot 1.

- `main`: Point d'entrée du programme. Initialise le système et démarre les routines principales.

## Répertoire `app2`

Le répertoire app2 héberge le code source principal de l'application du deuxième robot 2.

- `test`: Point d'entrée du programme. Initialise le système et démarre les routines principales.

## Makefile

- `Makefile`: Ce fichier contient les directives pour compiler le projet et générer l'exécutable.
Pour compiler, utilisez la commande $ make, et pour déployer le programme sur le dispositif, utilisez $ make install.
Chaque répertoire (app1 et app2) possède son propre Makefile.

## Répertoire `lib_dir`

Ce répertoire renferme les librairies.

## Répertoire `serieViaUSB`

Ce répertoire permet de lancer la commande $ serieViaUSB -l.

## Auteurs

- `Patrick Nzudom`
- `Harry Heng`
- `Saad Zouhri`
- `David Lajoi`
