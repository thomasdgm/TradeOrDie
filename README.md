# TradeOrDie
Survivez aux marchés ou faites faillite. Incarnez un trader travaillant de 9h à 17h.
Votre objectif : générer assez de profit pour payer des impôts croissants chaque vendredi soir. Si votre solde tombe à zéro, la partie s'arrête.

## Equipe
* Thomas Dégremont p2512393 - logique financière, actualité, moteur de jeu
* Raiden Hamza p2403473 - moteur de jeu, affichage

## Structure du projet
* `data/` : Fichiers de stockage de données et images `.txt`
* `src/` : Fichiers sources `.cpp`, `.h`
* `obj/` : Fichiers objet `.o`
* `bin/` : Executable générés
* `doc/` : Documentation du projet
*Makefile
*Readme.md

## Compilation et Installation

### Prérequis
* Un compilateur C++ (g++)
* Make
* Librairie -SDL2

### Installation et lancement

### Cloner le dépôt
```
git clone https://forge.univ-lyon1.fr/aspartame/tradeordie
```
### Aller dans le dossier
```
cd tradeordie
```

Le projet utilise un Makefile

### Lancer la version Txt
```
make
./bin/TradeOrDieTxt
```

### Lancer la version graphique
```
cd tradeordie
make TradeOrDie
./bin/TradeOrDie
```

### Générer la documentation
```
make doc
```

### supprimer les fichiers objets et les executables
```
make clean
```

### Tests
Nous avons mis en place une suite de tests unitaires pour chaque module
```
make test
./bin/test
```

# Manuel d'utilisation
## Version Txt
### Démarrage et Interface
* Lancement : Executez le programme et choisissez entre créer une novuelle partie ou charger une partie existante
* Affichage : Le haut de l'écran indique en permanence le jour et l'heure (de 9h à 17h)
* Etat du Portefeuille : Votre solde s'affiche juste en dessous et est de 10 000€ au démarrage
* Tableau du Marché : Une liste détaillé présente pour chaque actif : son nom, son type, la quantité en votre possession, la valeur totale de votre ligne et son cours actuel.

### Commandes de jeu
* a (Acheter) : Sélectionner ensuite l'actif (nom ou numéro) et saisissez la quantité désirée ou tapez all pour investir tout votre capital disponible
* v (Vendre) : Sélectionnez l'actif et la quantité à céder ou all pour liquider la ligne
* p (Passer l'heure) : Avance le temps d'une heure pour faire évoluer les cours

### Mécanismes de Simulation
* Système d'Actualités : Des flahs infos apparaissent aléatoirement. L'impact sur les cours n'a lieu que deux heures après l'annonce.
* Clôture Hebdomadaire : Chaque vendredi à 17h, tous vos actifs sont vendus automatiquement au cours actuel
* Prélèvement impôts : Une taxe est prélevée sur votre solde à chaque fin de semaine (commence à 2000€ et augmente de 10% chaque semaine)
* Condition de défaite : Si votre solde devient nul ou négatif après le prélèvement des impôts, la partie s'arrête

## Version SDL

### Démarrage et Interface
* Lancement : Executez le programme et choisissez entre créer une novuelle partie ou charger une partie existante avec les boutons à disposition
* Affichage : A gauche de l'écran la liste cliquable des actifs, à gauhe les boutons acheter, vendre et tout pour intéragir avec les actifs. En haut de l'écran il y a le jour et l'heure ainsi que le solde. en bas il y a un endroit ou s'affiche les évènements.
* Tableau du Marché : Au centre de l'écran il y a un graphique qui correspond à l'article séléctionné

### Mécanismes de Simulation
* Système d'Actualités : Des flahs infos apparaissent aléatoirement. L'impact sur les cours n'a lieu que deux heures après l'annonce.
* Clôture Hebdomadaire : Chaque vendredi à 17h, tous vos actifs sont vendus automatiquement au cours actuel
* Prélèvement impôts : Une taxe est prélevée sur votre solde à chaque fin de semaine (commence à 2000€ et augmente de 10% chaque semaine)
* Condition de défaite : Si votre solde devient nul ou négatif après le prélèvement des impôts, la partie s'arrête
