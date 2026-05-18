#include "gestionnaireEvenement.h"
#include <cassert>

// Constructeur, initialise un gestionnaire vide
GestionnaireEvenement::GestionnaireEvenement(){}

// Destructeur, pas de mémoire dynamique à libérer
GestionnaireEvenement::~GestionnaireEvenement(){}

// Fonction qui vérifie que les fonction de la classe fonctionne correctement
void GestionnaireEvenement::testRegression(){
    GestionnaireEvenement gE;
    Evenement e;
    gE.ajoutEvenement(e);
    string nom = e.recupNom();
    assert(gE.recupIndice(nom) == 0);
    assert((gE.recupEvenement(0)).recupNom() == e.recupNom());
    assert(gE.longueur() == 1);
    gE.supprimerEvenement(e);
    assert(gE.longueur() == 0);
}
// Ajoute un objet Evenement à la fin du vecteur gestionnaireEvenement
void GestionnaireEvenement::ajoutEvenement(Evenement const evenement){
    listeEvenement.push_back(evenement);
}

// Supprime un évènement du vecteur en cherchant son nom
void GestionnaireEvenement::supprimerEvenement(Evenement const evenement){
    string nom = evenement.recupNom();
    int i = recupIndice(nom); // On récupère la position de l'évènement
    if(i!=-1){
            listeEvenement.erase(listeEvenement.begin() + i); // supprime l'élément à l'indice i dans le vecteur
        }else{
            cout << "Evenement non trouvé pour suppression" << endl;// Affiche un message s'il ne trouve pas l'Evenement
        }
}

// Renvoie la position d'un Evenement grâce à son nom
int GestionnaireEvenement::recupIndice(const string Enom)const{
    for (unsigned int i=0 ; i<listeEvenement.size();i++){ // parcourt la liste pour trouver la position de l'évènement
        if(listeEvenement[i].recupNom() == Enom){
            return i; // Retourne l'indice s'il l'évènement est trouvé
        }
    }
    return -1; // renvoie -1 si l'évènement n'est pas trouvé
}

// Récupère un Evènement via sa position dans le vecteur
Evenement GestionnaireEvenement::recupEvenement(const unsigned int indice)const{
        if(indice>=0 && indice<listeEvenement.size()){ // Vérifie que l'indice est dans le vecteur
            return listeEvenement[indice]; // Renvoie l'Evenement à cet indice
        }else{
            cout << "Indice invalide" << endl; // Affiche un message d'erreur
            Evenement event;
            return event; // Renvoie un Evenemenet vide
        }
}

// Renvoie le nombre total d'évènements stockés ou la longueur du vecteur
int GestionnaireEvenement::longueur()const{
    return listeEvenement.size();
}
