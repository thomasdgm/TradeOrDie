#include<ctime>
#include "simulation.h"


int main() {
    Actif btc("Bitcoin",100,"Crypto");
    Trader joueur;
    GestionnaireEvenement gE;
    Evenement e;
    Simulation simu;
    btc.testRegression();
    cout << "Test actif OK" << endl;
    joueur.testRegression();
    cout << "Test trader OK" << endl;
    e.testRegression();
    cout << "Test evenement OK" << endl;
    gE.testRegression();
    cout << "Test gestionnaire evenement OK" << endl;
    simu.testRegression();
    cout << "Test simulation OK" << endl;
    cout << "Tout fonctionne correctement" << endl;
    return 0;
}
