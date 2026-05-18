#ifndef _SIMULATION_H
#define _SIMULATION_H
#include "trader.h"
#include "gestionnaireEvenement.h"
#include <string>


/**
 * @class Simulation
 * @brief Gère une simulation de trading avec un joueur et des variations d'actifs.
 *
 * La classe Simulation contient un trader (joueur) et fournit des méthodes
 * pour appliquer des variations aux actifs et effectuer un test de régression.
 */
class Simulation{
    private :
        GestionnaireEvenement bdd;
        std::vector<EvenementEnAttente> fileAttente;
        int compteur = 0;
    public :
        ///> Objet Trader représentant le joueur et son capital. */
        Trader joueur;
        ///> Vecteur, liste de tous les objets Actif présents dans le jeu. */
        vector<Actif> allActif;
        ///> Vecteur des noms d'actifs */
        vector<string> tabAct;
        ///> Vecteur des Prix de Revient Unitaire (PRU) pour chaque actif possédé. */
        vector<float> pru;
        ///> Heure actuelle de la simulation (entre 9h et 17h). */
        int h;
        ///> Jour actuel de la simulation. */
        int j;
    

        /**
        * @brief Constructeur par défaut
        */
        Simulation();
        /**
        * @brief Destructeur
        */
        ~Simulation();
        /**
        * @brief Test de régression pour vérifier le fonctionnement de la classe
        */
        static
        void testRegression();
        
        /**
        * @brief Récupère le prix actuel d'un actif.
        * @param nomActif Nom de l'actif à trouver.
        * @return float Cours actuel du marché de l'actif en paramètre.
        */
        float recupValActif(const string nomActif)const;

        /**
        * @brief Récupère une valeur historique d'un actif.
        * @param nomActif Nom de l'actif.
        * @param t Indice temporel dans l'historique.
        * @return float Valeur à l'instant t.
        */
        float recupValActifTemp(const string nomActif, const int t)const;
            
        /**
        * @brief Modifie manuellement la valeur d'un actif.
        * @param nomActif Nom de l'actif à modifier.
        * @param val Nouvelle valeur à insérer dans l'historique.
        */
        void modifValActif(const string nomActif,  const float val);

        /**
        * @brief Calcule et applique les variations boursières.
        * @details Utilise des modèles mathématiques (Brownien Géométrique) pour 
        * simuler la volatilité selon le type d'actif.
        */
        void variationActifs();

        /**
        * @brief Calcule la valeur totale de la fortune du joueur.
        * @return float Somme du cash et de la valeur actuelle de tous les titres possédés.
        */
        float recupTotalValeur()const;
            
        /**
        * @brief Récupère la valeur totale détenue pour un titre spécifique.
        * @param nomActif Nom de l'actif.
        * @return float (Quantité possédée * Prix actuel).
        */
        float recupValeur(const  string nomActif)const;
            
        /**
        * @brief Effectue une opération de vente.
        * @param actif Nom de l'actif à vendre.
        * @param quantite Nombre d'unités à céder.
        */
        bool vendreActif(const string actif, const float quantite);
            
        /**
        * @brief Effectue une opération d'achat.
        * @param actif Nom de l'actif à acquérir.
        * @param quantite Nombre d'unités à acheter.
        */
        bool achatActif(const string actif, const float quantite);
            
        /**
        * @brief Ajoute un objet Actif complet à la simulation.
        * @param actif L'objet Actif déjà initialisé.
        */
        void ajoutActif(const Actif actif);
            
        /**
        * @brief Retourne la quantité de titres détenus pour un actif.
        * @param nomActif Nom de l'actif.
        * @return float Quantité en portefeuille.
        */
        float recupMontantActif(const string nomActif)const;
            
        /**
        * @brief Trouve l'indice d'un actif dans les vecteurs allActif.
        * @param nomActif Nom de l'actif.
        * @return int Indice (0 à n-1) ou -1 si l'actif n'existe pas.
        */
        int recupIndice(const string nomActif)const;
            
        /**
        * @brief Applique un prélèvement financier (impôts ou taxes).
        * @param nomActif Nom de la devise
        * @param taxe Montant fixe à retirer.
        */
        void prelevementImpots(const string nomActif, float const taxe);
            
        /**
        * @brief Récupère la catégorie d'un actif.
        * @param nomActif Nom de l'actif.
        * @return string "Crypto", "Action" ou "Obligation".
        */
        string recupTypeActif(const string nomActif)const;
            
        /**
        * @brief Crée et ajoute un actif à la partie avec ses paramètres de base.
        * @param nom Nom du nouvel actif.
        * @param val Prix de départ.
        * @param type Type d'actif.
        */
        void ajoutActifPartie(const string nom, const float val, const string type);
            
        /**
        * @brief Vérifie l'existence d'un actif sur le marché.
        * @param nomActif Nom à chercher.
        * @return true si présent, false sinon.
        */
        bool verifieActif(const string nomActif)const;
            
        /** @return unsigned int Le nombre total d'actifs enregistrés. */
        unsigned int nbrActif() const;

        /** @brief Retourne le nom de l'actif à un indice donné.
         * @param i Indice.
         */
        string actifNom(const int i);

        /** @brief Retourne le vecteur de tous les noms d'actifs. */
        vector<string> returnTabAct();

        /** @brief Retourne le vecteur de tous les PRU du joueur. */
        vector<float> returnPru();

        /** @brief Retourne le vecteur "file d'attente" des evenements. */
        vector<EvenementEnAttente> returnEvent();

        /** @brief Lance le début de la partie avec la boucle de jeu */
        void debutPartie();

        /**
        * @brief Charge une partie existante depuis le fichier de sauvegarde.
        */
        void reprendrePartie();

        /**
        * @brief Initialise les données pour une nouvelle session de jeu.
        */
        void nouvellePartie();

        /**
        * @brief Vérifie si un fichier de sauvegarde est disponible.
        * @return true si une sauvegarde existe.
        */
        bool partiePresente() const;

        /**
        * @brief Supprime le fichier de sauvegarde actuel.
        */
        void supprimerPartie() const;

        /**
        * @brief Avance la simulation d'un pas de temps (1 heure).
        * @details Gère les cycles 9h-17h, le passage des jours et les taxes hebdomadaires.
        */
        void prochaineHeure();

        /** @brief charge tout les évènement présent dans un fichier dans un vector */
        void chargerBddEvenements();

        /** @return int Le numéro du jour actuel. */
        int jourActuel()const;

        /** @return int L'heure actuelle */
        int heureActuel()const;

        /** 
        * @brief Vérifie si le joueur a perdu. 
        * @return true si la partie est finie. 
        */
        bool partiePerdu()const;
};

#endif

