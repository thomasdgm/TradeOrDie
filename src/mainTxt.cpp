#include<ctime>
#include "TradeOrDieTxt.h"



int main() {

    srand (time(NULL)); // Initialise le générateur de nombres aléatoires
    TradeOrDieTxt jeu; // Crée l'instance principale du moteur du jeu
    jeu.debutPartie(); // Lance la boucle principale et la logique du jeu
    return 0;
}
