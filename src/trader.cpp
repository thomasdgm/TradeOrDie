#include <iostream>
#include "trader.h"
#include <cassert>
using namespace std;

// Constructeur, initialise trader par defaut avec tout vide
Trader::Trader(){
}

// Destructeur
Trader::~Trader(){
    portefeuille.clear();// vide le dictionnaire du portefeuille
}

// Fonction de test, vérifié que la gestion du compte fonctionne
void Trader::testRegression(){
    Trader joueur;
    joueur.ajoutMontant("Euro", 1000); // On ajoute 1000 Euro
    assert(joueur.recupMontant("Euro")== 1000); // On verifie que le joueur possède 1000 Euro

}

// Ajoute une quantité d'un actif
void Trader::ajoutMontant(const string actif, const float val){
    portefeuille[actif] += val; // Ajoute à l'actif la quantité val
}

// Récupère la quantité possédée pour un actif donné avec son nom
float Trader::recupMontant(const string actif)const{
    return portefeuille.at(actif);
}
