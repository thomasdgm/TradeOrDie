#include "evenement.h"
#include <cassert>

// Constructeur par défaut, initialise un évènement vide
Evenement::Evenement(){
    Enom = "";
    Edescription = "";
    Eimpact = 0.0;
    Egroupe_actif = false; // par defaut cible un actif seul
    Enom_actif = "";
}

// Constructeur avec paramètres, permet de créer un évènement complet
Evenement::Evenement(const string nom, const string description, const float impact,const bool groupe_actif, const string nom_actif ){
    Enom = nom;
    Edescription = description;
    Eimpact = impact;
    Egroupe_actif = groupe_actif;
    Enom_actif = nom_actif;
}

// Destructeur, rien à libérer
Evenement::~Evenement(){}

// Fonction qui vérifie que les fonction de la classe fonctionne correctement
void Evenement::testRegression(){
    Evenement e1;
    assert(e1.recupNom() == ""); // On vérifie si la fonction recupNom nous renvoie la bonne donnée et donc si l'évènement a bien été crée et que la fonction fonctionne correctement
    assert(e1.recupDescription() == "");
    assert(e1.recupImpact() == 0.0);
    assert(e1.recupGroupeActif() == false);
    assert(e1.recupNomGroupeActif() == "");

    Evenement e2("Augmentation inflation", "Une hausse généralisé des prix touche la France",1.0,0, "Action");// On créer un évènement
    assert(e2.recupNom() == "Augmentation inflation"); // On vérifie si la fonction recupNom nous renvoie la bonne donnée et donc si l'évènement a bien été crée et que la fonction fonctionne correctement
    assert(e2.recupDescription() == "Une hausse généralisé des prix touche la France");
    assert(e2.recupImpact() == 1.0);
    assert(e2.recupGroupeActif() == 0);
    assert(e2.recupNomGroupeActif() == "Action");
}

// Retourne le titre/nom de l'évènement
string Evenement::recupNom()const{
    return Enom;
}

// Retourne la description de l'évènement
string Evenement::recupDescription()const{
    return Edescription;
}

// Retourne la valeur de l'impact de l'évènement
float Evenement::recupImpact()const{
    return Eimpact;
}

// Indique si l'évènement cible un groupe d'actif (Crypto, Action,...) ou un actif précis (Orange, Bitcoin, ...)
bool Evenement::recupGroupeActif()const{
    return Egroupe_actif;
}

// Retourne le nom du groupe ou de l'actif visé par l'impact
string Evenement::recupNomGroupeActif()const{
        return Enom_actif;
}

/* Structure de données pour la file d'attente, elle lie un objet
Evenement à un compte à rebours
*/

