#include <iostream>
#include "actif.h"
#include <cassert>
using namespace std;

// Constructeur par défaut, initialise un actif vide
Actif::Actif(){
    Anom = "";
    Atype = "";

}

// Constructeur avec paramètres, initialise le nom, le type et le prix de départ
Actif::Actif(const string nom, const float prixOrigin, const string type){
    Anom = nom;
    // On place le prix d'origine comme dernier élément de l'historique
    AhistoriqueValeur.push_back(prixOrigin);
    Atype = type;

}

// Destructeur, rien à libérer manuellement
Actif::~Actif(){}

// Fonction de test, sert à vérifier que la classe fonctionne toujours comme prévu après une modification
void Actif::testRegression(){

    Actif btc("Bitcoin", 100, "crypto");
    assert(btc.recupType() == "crypto");
    assert(btc.recupNom() == "Bitcoin");
    assert(btc.recupValActuel() == 100);

    btc.ajouterVal(50); // Test l'ajout d'une valeur
    assert(btc.recupValActuel() == 50); // récupère la valeur actuel de l'actif
    assert(btc.recupVal(0) == 100); // récupère la valeur en indice 0 de l'actif
    assert(btc.recupVal(1) == 50);

    btc.modifNom("Nvidia"); // Test la modification du nom
    btc.modifType("action");
    assert(btc.recupType() == "action");
    assert(btc.recupNom() == "Nvidia");
}

// Modifie le nom de l'actif
void Actif::modifNom(const string nom){
    Anom = nom;
}

// Récupère le nom de l'actif
string Actif::recupNom() const{
    return Anom;
}

//Retourne la dernière valeur enregistrée dans l'historique
float Actif::recupValActuel() const{
    if(!AhistoriqueValeur.empty()){
        int taille = AhistoriqueValeur.size() - 1; // récupère la taille de l'historique des valeurs
        return AhistoriqueValeur[taille];} // Renvoie l'indice du dernier élément
else{
    return -1;
}
}


void Actif::ajouterVal(const float valeur){
    AhistoriqueValeur.push_back(valeur); // Ajoute une nouvelle valeur à la fin de l'historique
}

float Actif::recupVal(const int i){
    return AhistoriqueValeur[i]; // Renvoie la valeur dans l'historique à l'indice i
}

// Retourne le type de l'actif
string Actif::recupType()const{
    return Atype;
}

// Modifie le type de l'actif
void Actif::modifType(const string type){
    Atype = type;
}
