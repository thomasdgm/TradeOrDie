#include <iostream>
#include "simulation.h"
#include <cassert>
#include <math.h>
#include <random>
#include <stdlib.h>
#include <fstream>
#include <sstream>
using namespace std;

// Découpe une chaîne de caractères en mots basés sur les espaces
std::vector<std::string> split(const std::string& str) {
    std::vector<std::string> tokens;
    std::istringstream iss(str);
    std::string token;
    
    while (iss >> token) {
        tokens.push_back(token);
    }
    
    return tokens;
}

// Constructeurs, initialise le capital de départ et l'heure
Simulation::Simulation(){
    allActif.push_back(Actif("Euro", 1, "Devise")); // Ajoute un actif Euro qui vaut 1 et fait partie de type Devise
    joueur.ajoutMontant("Euro", 10000); // Ajoute 10 000 euro au portefeuille du joueur
    h = 9; // Initialise l'heure à 9
    j = 0; // Initialise le jour à 0
    
}

// Destructeur, rien à libéré
Simulation::~Simulation(){}

// Fonction pour tester les fonctions de la classe
void Simulation::testRegression(){
    Simulation simu; // Initialise un objet Simulation
    simu.tabAct.push_back("Euro");
    simu.pru.push_back(0);
    simu.ajoutActifPartie("Bitcoin", 100, "Crypto"); // Ajout d'un actif Bitcoin à un prix 100 qui fait partie du type Crypto'
    assert(simu.recupTotalValeur() == 10000); // On verifie si la valeur total est égal à 1000
    assert(simu.recupValeur("Euro") == 10000); // On verifie si la valeur de Euro est 1000
    assert(simu.recupValeur("Bitcoin") == 0); // On vérifie si la valeur de Bitcoin possédé est 0
    assert(simu.recupValActif("Bitcoin") == 100); // On vérifie si la valeur de de Bitcoin est 100
    assert(simu.recupValActifTemp("Bitcoin",0) == 100);
    simu.modifValActif("Bitcoin",120);
    assert(simu.recupValActif("Bitcoin") == 120);
    simu.variationActifs();
    float newVal = simu.recupValActif("Bitcoin");
    cout << "Nouvel valeur : " << newVal << endl;
    simu.modifValActif("Bitcoin",120);
    assert(simu.recupTotalValeur() == 10000);
    simu.achatActif("Bitcoin", 2);
    assert(simu.recupMontantActif("Bitcoin") == 2);
    assert(simu.recupTotalValeur() == 10000);
    simu.vendreActif("Bitcoin", 1);
    assert(simu.recupMontantActif("Bitcoin") == 1);
    assert(simu.recupValActif("Bitcoin") == 120);
    assert(simu.recupIndice("Bitcoin") == 1);
    float solde = simu.recupValeur("Euro");
    simu.prelevementImpots("Euro",1000);
    assert(simu.recupValeur("Euro") == (solde - 1000));
    assert(simu.recupTypeActif("Bitcoin") == "Crypto");
    simu.ajoutActifPartie("Solana",200,"Crypto");
    assert(simu.recupValActif("Solana") == 200);
    assert(simu.recupTypeActif("Solana") == "Crypto");
    assert(simu.verifieActif("Bitcoin") == true);
    assert(simu.verifieActif("Orange") == false);
    assert(simu.actifNom(1) == "Bitcoin");
    assert(simu.nbrActif() == 3);

    simu.nouvellePartie();
    simu.prochaineHeure();
    assert(simu.jourActuel() == 0);
    assert(simu.heureActuel() == 10);
    assert(simu.partiePresente() == true);
    simu.supprimerPartie();
    assert(simu.partiePresente() == false);
    simu.prelevementImpots("Euro",100000);
    assert(simu.partiePerdu() == true);

}

// Retourne la valeur de l'actif pour lequel le nom correspond à celui pris en paramètre
float Simulation::recupValActif(const string nomActif)const{
    Actif actif; // Création d'un actif
    for(unsigned int i = 0; i < allActif.size(); i++ ){ // On parcourt le vecteur qui stocke tout les actifs
        if(allActif[i].recupNom() == nomActif){ // On cherche si le nom de l'actif d'indice i est celui qu'on cherche
            actif = allActif[i]; // S'il correspond alors on récupère l'actif
        }
    }
    return actif.recupValActuel(); // On retourne sa valeur

}

// Retourne la valeur d'un actif à un indice temporel 't' donné
float Simulation::recupValActifTemp(const string nomActif, const int t)const{
    Actif actif; // Création d'un objet actif
    for(unsigned int i = 0; i < allActif.size(); i++){ // On parcourt le vecteur qui stocke tout les actifs
        if(allActif[i].recupNom()==nomActif){ // Si le nom de l'actif à l'indice i correspond au nom recherché
            actif = allActif[i]; // Copie l'actif trouvé dans la variable temporaire
        }
    }
    return actif.recupVal(t); // Appelle la méthode recupVal de la classe Actif pour obtenir le prix au temps 't'
}

// Ajoute une nouvelle valeur de prix dans l'historique d'un actif
void Simulation::modifValActif(const string nomActif, const float val){
    for(unsigned int i = 0; i < allActif.size(); i++){ // On parcourte tous les actif stocké
        if(allActif[i].recupNom()==nomActif){// Si le nom de l'actif à l'indice i correspond au nom recherché
            allActif[i].ajouterVal(val); // On ajoute la nouvelle valeur 'val' à la fin de son historique de prix
        }
    }
}

// Ajoute un nouvel actif à la simulation et initialise le compte du joueur
void Simulation::ajoutActif(const Actif actif){
    allActif.push_back(actif); // Ajoute l'objet 'actif' à la fin du vecteur 'allActif'
    joueur.ajoutMontant(actif.recupNom(), 0); // Initialise la quantité possédée par le joueur pour cet actif à 0
}

void Simulation::variationActifs(){
    float valeurActuel;
    float nouvelleVal;
    for(unsigned int i = 1; i< allActif.size() ; i++ ){// On commence la boucle à i=1 pour ignorer l'Euro (index 0) qui ne varie pas
        if (allActif[i].recupType()=="Crypto"){// On vérifie si le type de l'actif est Crypto
            double esperance =0.0;// Tendance à long terme
            double variance = 0.5;// Volatilité élevée
            double dt = 10.0/365.0;
            random_device rd;// Initialisation de l'aléatoire
            mt19937 gen(rd());
            normal_distribution<double> dist(0.0, 1.0);// Loi normale centrée réduite
            double Z = dist(gen);
            valeurActuel = allActif[i].recupValActuel();
            nouvelleVal = valeurActuel * exp((esperance - 0.5*variance*variance)*dt+variance * sqrt(dt) * Z);// Formule mathématique du prix : S(t+dt) = S(t) * exp((r - sigma²/2)dt
            allActif[i].ajouterVal(nouvelleVal);
        }
        else if (allActif[i].recupType()=="Action"){// On vérifie si le type de l'actif est Action
            double esperance =0.0;
            double variance = 0.25;// Variance plus faible que la crypto
            double dt = 10.0/365.0;
            random_device rd;// Initialisation de l'aléatoire
            mt19937 gen(rd());
            normal_distribution<double> dist(0.0, 1.0);
            double Z = dist(gen);
            valeurActuel = allActif[i].recupValActuel();
            nouvelleVal = valeurActuel * exp((esperance - 0.5*variance*variance)*dt+variance * sqrt(dt) * Z);
            allActif[i].ajouterVal(nouvelleVal);
        }else if (allActif[i].recupType()=="Obligation"){// On vérifie si l'actif est une Obligation'
            valeurActuel = allActif[i].recupValActuel();
            nouvelleVal = valeurActuel * 1.00068765033; // Augmentation linéaire
            allActif[i].ajouterVal(nouvelleVal);
        }
    }

}

// Calcule la valeur totale d'UN SEUL actif possédé par le joueur
float Simulation::recupValeur(const string nomActif)const{
    Actif actif;
    for(unsigned int i = 0; i < allActif.size(); i++ ){// On parcourt le vecteur qui stocke les actifs
        if(allActif[i].recupNom() == nomActif){// On vérifie si le nom de l'actif est celui qu'on recherche
            actif = allActif[i];
        }
    }
    return actif.recupValActuel() * joueur.recupMontant(nomActif);// Renvoie le prix de l'actif * sa quantité

}

// Calcule la richesse totale du joueur
float Simulation::recupTotalValeur() const{
    float sum = 0;
    for(unsigned int i = 0; i < allActif.size(); i++ ){// On parcourt le vecteur qui stocke les actifs
        sum += allActif[i].recupValActuel() * joueur.recupMontant(allActif[i].recupNom());// Cumul de la valeur de chaque ligne du portefeuille
    }
    return sum;
}

// Gère la revente d'un actif contre des Euros
bool Simulation::vendreActif(const string actif, const float quantite){
    float q = quantite;
    unsigned int i = recupIndice(actif);

    if(recupTypeActif(tabAct[i]) == "Action"){q = (int)q;}// Règle : On ne peut vendre que des actions entières
    if(joueur.recupMontant(actif) >= q && q!= 0){// Verifie si le joueur a assez de titres pour vendre
         if(recupMontantActif(tabAct[i]) == quantite){pru[i] = 0;}// Si on vend tout le stock, on réinitialise le Prix de Revient (PRU) à 0
        joueur.ajoutMontant(actif, -1*q);
        joueur.ajoutMontant("Euro", q * recupValActif(actif));
        return true;

    }
    else{return false;}// Si la vente n'est pas possible on renvoie false
}

// Gère l'achat d'un actif en dépensant des Euros
bool Simulation::achatActif(const string actif, const float quantite){
    float q = quantite;
    unsigned int i = recupIndice(actif);
    if(recupTypeActif(tabAct[i]) == "Action"){q = (int)q;}
    if(joueur.recupMontant("Euro") >= q * recupValActif(actif)  && q!= 0){// Vérifie si le joueur a assez d'euros pour acheter l'actif
            pru[i] = (pru[i]*recupMontantActif(tabAct[i]) + quantite*recupValActif(tabAct[i]))/(recupMontantActif(tabAct[i]) + quantite);// On met à jour le prix moyen d'achat pour suivre la rentabilité
        joueur.ajoutMontant(actif, q );// Ajoute les titres acheté
        joueur.ajoutMontant("Euro", -1 * q * recupValActif(actif) );// Retire les euros utilisés
        return true;

    }
    else{return false;}
}

// Retourne combien d'unités d'un actif le joueur possède
float Simulation::recupMontantActif(const string nomActif)const{

    return joueur.recupMontant(nomActif);
}

// Recherche l'index d'un actif dans le tableau allActif par son nom
int Simulation::recupIndice(const string nomActif)const{
    for (unsigned int i=0 ; i<allActif.size();i++){// Parcourt le vecteur qui stocke tout les actifs
        if(allActif[i].recupNom() == nomActif){
            return i;
        }
    }
    return -1;
}

// Prélève ou ajoute un nombre pour un actif
void Simulation::prelevementImpots(const string nomActif, float const taxe){
    joueur.ajoutMontant(nomActif, -taxe);
}

// Récupère le type d'un actif via son nom
string Simulation::recupTypeActif(const string nomActif)const{
    return allActif[recupIndice(nomActif)].recupType();
}

// Ajoute un nouvel actif dans le jeu et initialise son PRU à 0
void Simulation::ajoutActifPartie(const string nom, const float val, const string type){
    tabAct.push_back(nom);
    pru.push_back(0);
    ajoutActif(Actif(nom, val, type));


}

// Vérifie si un nom d'actif est présent dans liste des actifs du jeu
bool Simulation::verifieActif(const string nomActif)const{
    for (unsigned int i = 0; i < tabAct.size(); i++) {
        if (tabAct[i] == nomActif) {
            return true;
        }
    }
    return false;
}

/**
 * Retourne le nombre total d'actifs enregistrés dans la simulation.
 * Inclut l'Euro et les différents titres (Actions, Cryptos, ...).
 */
unsigned int Simulation::nbrActif() const{
    return tabAct.size();
}

/**
 * Récupère le nom d'un actif via son indice dans le tableau.
 */
string Simulation::actifNom(const int i){
    return tabAct[i];
}

/**
 * Retourne le vecteur contenant les noms de tous les actifs.
 */
vector<string> Simulation::returnTabAct(){
    return tabAct;
}

/**
 * Retourne le vecteur des Prix de Revient Unitaires (PRU).
 */
vector<float> Simulation::returnPru(){
    return pru;
}

vector<EvenementEnAttente> Simulation::returnEvent(){
    return fileAttente;
}

// Vérifie si un fichier de sauvegarde existe et s'il est vide ou non (si une partie en cours existe)
bool Simulation::partiePresente()const{
    ifstream fichier("data/save.txt", ios::in);
    string ligne;
    if(std::getline( fichier, ligne )){
        return true;}
    else{return false;}
    return false;

}

// Charge les données depuis le fichier save.txt pour restaurer la partie
void Simulation::reprendrePartie(){
    ifstream fichier("data/save.txt", ios::in);
    string nom, type, ligne;
    float val, quantite, achat;
    int indice = 0;
    // lecture du fichier
    std::getline( fichier, ligne );

    // initialisation de la quantité d'Euro par defaut
    tabAct.push_back("Euro");
    pru.push_back(0);
    prelevementImpots("Euro", 10000); 

    j = stoi(split(ligne)[0]);
    h = stoi(split(ligne)[1]);
            
    unsigned int t = j*9 + (h-9)%17;
    // Lecture de chaque ligne du fichier
    while(std::getline( fichier, ligne )){

    nom = split(ligne)[0]; // Récuperation du nom de l'actif
    val = stof(split(ligne)[1]); // récuperation de la valeur de l'actif
    type = split(ligne)[2];
    quantite = stof(split(ligne)[3]);
    achat = stof(split(ligne)[4]);

    if(nom != "Euro"){
        std::getline( fichier, ligne );
        ajoutActifPartie(nom, stof(split(ligne)[0]), type);
        for(unsigned int i = 1; i < t; i++ ){
        modifValActif(nom, stof(split(ligne)[i]));}
        modifValActif(nom, val);
        pru[indice] = achat;             
    }
    // Restauration du montant possédé par le trader
    prelevementImpots(nom, -quantite);
                
    indice ++;}


}

// Initialise une partie avec les actifs par defauts
void Simulation::nouvellePartie(){
    tabAct.push_back("Euro");
    pru.push_back(0);
    ajoutActifPartie("Bitcoin", 1000, "Crypto");// Ajout de l'actif Bitcoin
    ajoutActifPartie("Solana", 20, "Crypto");
    ajoutActifPartie("Nvidia", 500, "Action");
    ajoutActifPartie("Orange", 20, "Action");
    ajoutActifPartie("AirLiquid", 150,"Action");
    ajoutActifPartie("OAT_France", 100,"Obligation");

    if(partiePresente()){
        remove("data/save.txt");} // Suppression de la sauvegarde

    chargerBddEvenements();
    srand(time(0));// Initialisation de l'aléatoire

}

// Supprime le fichier de sauvegarde
void Simulation::supprimerPartie()const{
    remove("data/save.txt");
}

// Avancement du temps (1h par 1h) et gestion des événements
void Simulation::prochaineHeure(){
    unsigned int t = j*9 + (h-9)%17;
    if(h == 17){
    h = 9; 
    j++; 
    if(j%5 == 0 && j != 0){ // Chaque vendredi (tous les 5 jours), impôts et liquidation
        float prelevement = 2000 * pow(1.1,(j/5) -1);
        for(unsigned int i = 1; i < tabAct.size(); i++){
            vendreActif(tabAct[i], recupMontantActif(tabAct[i]) );
            pru[i] = 0;
        }

        prelevementImpots("Euro", prelevement);}}
    
    else{h++;}
    variationActifs(); // Evolution naturelle des prix

    // Sauvegarde automatique 
    ofstream fichier("data/save.txt", ios::out | ios::trunc);
    fichier << j << " " << h << endl;
    for(unsigned int i = 0; i < tabAct.size(); i++){
    fichier << tabAct[i] << " " << recupValActif(tabAct[i]) << " " << recupTypeActif(tabAct[i]) << " " << recupMontantActif(tabAct[i]) << " " << pru[i] << endl;
    if( tabAct[i] != "Euro"){
    for(unsigned int j = 0; j < t+1; j++){
        fichier << recupValActifTemp(tabAct[i], j) << " ";} 
    fichier << endl;
    }}

    // Gestion des évènements aleatoires
    GestionnaireEvenement listeEvenementPartie;
    if ((rand() % 100) < 5) { // On mets 5% de chances qu'un evenement est lieu toutes les heures
        // On vérifie qu'on n'a pas déjà eu trop d'événements (ton compteur)
        if (compteur < 1) {
            int indiceAleatoire = rand() % bdd.longueur();
            Evenement e = bdd.recupEvenement(indiceAleatoire);;
            bdd.supprimerEvenement(e);
            listeEvenementPartie.ajoutEvenement(e);
            EvenementEnAttente nouvelEvenement = {e , 2};// On place l'événement dans une file d'attente
            fileAttente.push_back(nouvelEvenement);

            compteur++;
        }
    }
        if(!fileAttente.empty()){
            EvenementEnAttente& nouvelEvenement = fileAttente.front();
        if(nouvelEvenement.heureActivation <= 0){// On vérifie si l'heure d'activation d'un evenement est maintenant et s'il faut traiter l'évènement
            Evenement e = fileAttente.front().e;
            float impactE = e.recupImpact();
            string cible = e.recupNomGroupeActif();
            bool estUnGroupe = e.recupGroupeActif();
            for (unsigned int i = 0; i < allActif.size(); i++) {// Application de l'impact sur les prix
                    bool match = false;
                    if (estUnGroupe) {
                        if (allActif[i].recupType() == cible) match = true;
                    } else {
                        if (allActif[i].recupNom() == cible) match = true;
                    }
                    if (match) {
                        float currentVal = allActif[i].recupValActuel();
                        float newVal = currentVal * impactE;
                        allActif[i].ajouterVal(newVal);
                        cout << ">>> " << allActif[i].recupNom()
                        << " : " << currentVal << " -> " << newVal
                        << " (Impact: " << impactE << ")" << endl;
                    }
                }fileAttente.erase(fileAttente.begin());
            }

    // Réinitialisation du compteur en fin de journée ou selon le cycle 'h'
    if (h == 17) {
        compteur = 0;
    }
    if(!fileAttente.empty()){
        (fileAttente.front()).heureActivation--;
    }
}}

// Charge les événements depuis un fichier dans un vector
void Simulation::chargerBddEvenements(){
    ifstream evenementListe("data/evenementListe.txt", ios::in);
    if(!evenementListe.is_open()){
        cout << "Erreur : Impossible d'ouvrir evenementListe.txt" << endl;
        return;
    }
    string nom, description, nomActif, ligne;
    float impact;
    bool groupeActif;
    while(std::getline(evenementListe, ligne)){
        std::stringstream ss(ligne);
        std::getline(ss, nom, ',');
        std::getline(ss, description, ',');
        ss >> impact;
        ss.ignore(); // Saute la virgule
        ss >> groupeActif;
        ss.ignore(); // Saute la virgule
        std::getline(ss, nomActif);

        Evenement e(nom, description, impact, groupeActif, nomActif);
        bdd.ajoutEvenement(e);
    }
    evenementListe.close();

}

/**
 * Retourne l'indice du jour actuel.
 */
int Simulation::jourActuel()const{
    return j;
}

/**
 * Retourne l'heure actuelle de la simulation.
 */
int Simulation::heureActuel()const{
    return h;
}

/**
 * Vérifie si la condition de défaite est remplie.
 * La partie s'arrête si la valeur totale du portefeuille (euro + actifs) 
 * descend à zéro ou en dessous.
 */
bool Simulation::partiePerdu() const{

    return recupTotalValeur() <= 0;
}
