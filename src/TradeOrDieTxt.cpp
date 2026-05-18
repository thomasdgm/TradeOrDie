#include <iostream>
#include "TradeOrDieTxt.h"
#include <cassert>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <regex>
using namespace std;

// Initialise les couleurs pour afficher des couleurs sur la ligne de commande
const regex pattern("[1234567890]+(.[1234567890]+)?");
const string RESET = "\033[0m";
const string GREEN = "\033[32m";
const string RED = "\033[31m";

// Constructeur par defaut vide
TradeOrDieTxt::TradeOrDieTxt(){}
// Destructeur qui n'a besoin de rien libéré manuellement
TradeOrDieTxt::~TradeOrDieTxt(){}

// Affiche les règle du jeu pour le début de partie
void TradeOrDieTxt::debutPartie(){
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif// Nettoie la console
    cout << RESET << "================================================================================================================================================================" << endl;
    cout << "Bienvenue dans TradeOrDie" << endl ;
    cout << "Dans ce jeu, vous devrez spéculer sur différents actifs pour vous enrichir le plus possible" << endl ;
    cout << "Chaque jour, vous commencez à 9h, et finissez à 17h. Vous travaillerez tous les jours de la semaine (pas le week-end)" << endl;
    cout << "À la fin de chaque semaine, l'intégralité de vos actifs sont vendus, et une somme vous est prélevé" << endl;
    cout << "Vous pouvez acheter des fractions de crypto, mais vous êtes obligé d'acheter des actions entières" << endl;




    cout << "Bonne chance !" << endl;
    cout << "================================================================================================================================================================" << endl;
    // Affichage des règles du jeu
    
    if(simu.partiePresente()){
        char continuer = ' ';
        while(continuer !='y' && continuer != 'n'){
        
        cout << endl << "Voulez vous reprendre votre partie de la dernière fois ? (y/n)" << endl;
        cin >> continuer;}

        if(continuer == 'y'){
            simu.reprendrePartie();// Si l'utilisateur entre y alors il reprend sa partie précedente si elle existe

        }
        else{
    
        simu.nouvellePartie();// Si l'utilisateur entre n alors il recommence une partie
}

    }
    else{
    
    simu.nouvellePartie();}// S'il n'y a aucune partie sauvegardé alors on recommence direct une nouvelle partie

    loop();// Lance la boucle du jeu

}

void TradeOrDieTxt::testRegression(){
    TradeOrDieTxt partie;
    partie.loop();
    partie.finPartie();
}

// Gère la fin de partie
void TradeOrDieTxt::finPartie(){

    cout << "Vous avez perdu au bout de " << simu.jourActuel() << " jours" << endl;// Affichage lorsque l'on perd, on affiche le nombre de jour qu'a duré la partie
    simu.supprimerPartie();// On supprime la partie du fichier sauvegarde
}


void TradeOrDieTxt::loop(){
    if(simu.partiePerdu()){ finPartie(); }// Vérifie si le joueur a perdu ou non
    else{
        int j = simu.jourActuel();
        int h = simu.heureActuel();// Affichage du nombre de jour et heures à laquelle le joueur est

        if(h == 9 && j != 0){
        if(j%5 != 0 || j == 0){cout << "==================== Nouvelle journée ====================" << endl;}
        else{
            cout << "==================== Fin de la semaine ====================" << endl;
            cout << "Tout vos actifs on été vendu, et cette semaine, une somme de " << 2000 * pow(1.1,(j/5) -1) << "€ vous a été prélevé" << endl;
            cout << "==================== Nouvelle semaine ====================" << endl;}}// Affichage pour une nouvelle journée ou une fin de semaine

        vector<EvenementEnAttente> fileAttente = simu.returnEvent();

        if(!fileAttente.empty()){
            cout << "\n--- ACTUALITÉ ---" << endl;
            cout << fileAttente[0].e.recupDescription() << endl;
        }




        unsigned int t = j*9 + (h-9)%17;
        char entre = ' ';
        while(entre != 'p'){// Tant que l'utilisateur n'a pas choisi de "Passer" l'heure
        cout << "Jour : " << j+1 << "    Heure : " << h << endl << endl;

        cout << "Votre solde actuel : " << simu.recupTotalValeur()  << "€" << endl;// Affichage du prix, de la quantité et de la valeur détenue
        cout << "Votre portefeuille actuel : " << endl;
        vector<string> tabAct = simu.returnTabAct();
        vector<float> pru = simu.returnPru();
        for(unsigned int i = 0; i < simu.nbrActif(); i++){
            cout << "   " ;
            if(i != 0){
                cout << "("<< i <<") ";
            }

            cout << "Actif: " << tabAct[i] << " (" << simu.recupTypeActif(tabAct[i]) << ")";
            cout << "   " ;
            cout << "Quantité : " << simu.recupMontantActif(tabAct[i]) << "   (" << simu.recupValeur(tabAct[i]) << "€)";
            cout << "   " ;
            cout << "Valeur : " << simu.recupValActif(tabAct[i]) << "€";// Affichage des actifs et des quantités possédé
            
            if( i != 0 && t != 0){
                if(((simu.recupValActif(tabAct[i]) - simu.recupValActifTemp(tabAct[i], t-1) )/simu.recupValActifTemp(tabAct[i], t-1)) < 0 ){
                cout << "   (" << RED << ((simu.recupValActif(tabAct[i]) - simu.recupValActifTemp(tabAct[i], t-1) )/simu.recupValActifTemp(tabAct[i], t-1))*100  << "%" << RESET << ")" ;}
                else{if(((simu.recupValActif(tabAct[i]) - simu.recupValActifTemp(tabAct[i], t-1) )/simu.recupValActifTemp(tabAct[i], t-1)) > 0 ){
                cout << "   (" << GREEN << ((simu.recupValActif(tabAct[i]) - simu.recupValActifTemp(tabAct[i], t-1) )/simu.recupValActifTemp(tabAct[i], t-1))*100  << "%" << RESET << ")" ;}

                    else{ cout << "   (" << RESET << ((simu.recupValActif(tabAct[i]) - simu.recupValActifTemp(tabAct[i], t-1) )/simu.recupValActifTemp(tabAct[i], t-1))*100  << "%" << RESET << ")" ;}
                }}// Affichage des variation entre l'heure actuel et l'heure passé (Rouge si sa baisse, Vert si sa augmente)

             
        
            
            if(pru[i] != 0){
                if(((simu.recupValActif(tabAct[i]) - pru[i] )/pru[i]) < 0 ){
                cout << "   Performance : " << RED <<((simu.recupValActif(tabAct[i]) - pru[i] )/pru[i])*100 << "%" << RESET;}
                else{if(((simu.recupValActif(tabAct[i]) - pru[i] )/pru[i]) > 0 ){
                cout << "   Performance : " << GREEN <<((simu.recupValActif(tabAct[i]) - pru[i] )/pru[i])*100 << "%" << RESET;}

                    else{ cout << "   Performance : " << ((simu.recupValActif(tabAct[i]) - pru[i] )/pru[i])*100 << "%";}
                }// Affichage des performance du joueur pour chaque actif
            }
            cout << endl;
        }
        cout << endl;
       
        while(entre != 'a' && entre != 'v' && entre != 'p'){
        cout << "Voulez-vous acheter ou vendre un actif ou passer l'heure ? (a/v/p) " << endl;// Affichage pour demander au joueur quel action il souhaite effectuer
        cin >> entre;}

        string nomActif;
        string q = " ";
        float quantite;
        switch (entre) {
            case 'a' : // Si le joueur veut acheté
            
                while(!simu.verifieActif(nomActif) || nomActif =="Euro"){
                cout << "Veuillez entrer le nom de l'actif que vous voulez acheter " << endl;
                cin >> nomActif;

                if(regex_match(nomActif, pattern) && (unsigned int)stof(nomActif) < simu.nbrActif() && (int)stof(nomActif) > 0 ){// On vérifie que l'entrée est bien un nombre

                    nomActif = simu.actifNom((int)stof(nomActif));
                }

                }
                while( !regex_match(q, pattern) && q != "all"){
                    cout <<"Veuillez entrer la quantité de " << nomActif << " que vous voulez acheter (Vous pouvez en acheter au maximum ";
                    
                    if(simu.recupTypeActif(nomActif) == "Action"){
                    cout << (int)(simu.recupMontantActif("Euro")/simu.recupValActif(nomActif)) << " pour " << (int)(simu.recupMontantActif("Euro")/simu.recupValActif(nomActif))*simu.recupValActif(nomActif)<<"€)" << endl;}
                    else{ cout << simu.recupMontantActif("Euro")/simu.recupValActif(nomActif) << " pour " << simu.recupMontantActif("Euro")/simu.recupValActif(nomActif)*simu.recupValActif(nomActif)<<"€)" << endl;};
                    cin >> q;}// Affiche la quantité maximal que le joueur peut acheter de l'actif selectionné

                if( q == "all"){quantite = simu.recupMontantActif("Euro")/simu.recupValActif(nomActif);}// q permet d'acheter la quantité maximale
                else{quantite = stof(q) ;}

                simu.achatActif(nomActif, quantite);// Achète le nombre d'actif voulu
                entre = ' ';
            break;



            case 'v' : // Si le joueur veut vendre
                while(!simu.verifieActif(nomActif) || nomActif =="Euro"){
                cout << "Veuillez entrer le nom de l'actif que vous voulez vendre" << endl;
                cin >> nomActif;
                if(regex_match(nomActif, pattern) && (unsigned int)stof(nomActif) < simu.nbrActif() && (int)stof(nomActif) > 0 ){

                nomActif = simu.actifNom((int)stof(nomActif));
                }

                }
                while( !regex_match(q, pattern) && q != "all"){// Boucle de sécurisation pour la quantité, on vérifie si l'entrée est soit un nombre valide soit "all"
                    
                    cout <<"Veuillez entrer la quantité de " << nomActif << " que vous voulez vendre" << endl;
                    cin >> q;}

                if( q == "all"){quantite = simu.recupMontantActif(nomActif);}// Récupère la totalité du stock détenu par le trader
                else{quantite = stof(q) ;}

                simu.vendreActif(nomActif, quantite);// Exécution de l'ordre de vente dans le moteur de simulation
                
                entre = ' ';

            break;


        }}

        simu.prochaineHeure();
        loop();

    }
}



