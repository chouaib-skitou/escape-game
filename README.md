# escape-game
 Infrastructure modulaire pour Escape Game


    Le but de ce projet est de développer les bases d’un jeu d’escape-game, à savoir le poste
 de contrôle du maître du jeu, et un certain nombre de « détecteurs » et d’actuateurs
pour les différentes énigmes, partageant une interface de branchement et un protocole
de communication communs de manière à pouvoir facilement échanger ou rajouter des
modules

Le poste de contrôle devra permettre de :

    – contrôler des automatismes, par exemple quand le bon code est tapé sur un
    clavier, déclencher l’ouverture de la trappe secrète correspondante…
    – activer en mode manuel les principaux actionneurs, dont rallumer la lumière et
    déverrouiller la sortie en cas de panique d’un joueur claustrophobe
    – voir et écouter les joueurs via plusieurs caméras
    – leur parler en cas de problème
    – leur envoyer des messages / indices sur un écran dans la salle de jeu
    – surveiller le temps et le script théorique du déroulement du jeu
    – une (re-)programmation simple des automatismes

    On vous propose de vous appuyer sur un système logiciel pour maison “intelligente”, tel
que par exemple Home Assistant + Node-Red


Pour l’intérieur de la salle de jeu, on vous demande de développer un certain nombre (à
négocier) de dispositifs détecteurs/actionneurs qui communiquent avec le poste de
contrôle via un bus commun à choisir, où chaque module a son adresse propre et où on
puisse les brancher les uns à la suite des autres via des câbles standard, par exemple
RJ45

Exemples d’idées de détecteurs/actionneurs:

    - digicode, clavier de PC, télécommande IR
    - gros bouton rotatif, façon coffre fort
    - accéléromètre / boussole qui détecte l’orientation d’un cube
    - détection de la couleur d’un objet
    - identification d’un objet par puce RFID
    - barrière laser
    - afficheur de message LCD
    - haut-parleur pouvant diffuser un message/son (reprogrammable) de 5s
    - lampe de couleur programmable
    - ouverture/déverrouillage de trappe, tiroir, coffre
