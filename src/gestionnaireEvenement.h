#ifndef _GESTIONNAIREEVENEMENT_H
#define _GESTIONNAIREEVENEMENT_H
#include "evenement.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

/**
 * @class GestionnaireEvenement
 * @brief Classe gérant la base de données des événements de la simulation.
 * * Cette classe permet de stocker, rechercher et manipuler l'ensemble des
 * événements (Evenement) chargés depuis les fichiers de configuration.
 * Elle sert de "bibliothèque" dans laquelle la Simulation vient puiser.
 */
class GestionnaireEvenement {
    private :
        ///< Vecteur stockant l'intégralité des événements disponibles. 
        vector<Evenement> listeEvenement;

    public :
        /** @brief Constructeur par défaut du gestionnaire. */
        GestionnaireEvenement();
        /**
         * @brief Destructeur.
         */
        ~GestionnaireEvenement();
        /** @brief Fonction de test */
        static void testRegression();
        /**
         * @brief Ajoute un nouvel événement au catalogue.
         * @param evenement L'objet Evenement à stocker.
         */
        void ajoutEvenement(Evenement const evenement);
        /**
         * @brief Supprime un événement spécifique de la liste.
         * @param evenement L'événement à retirer.
         */
        void supprimerEvenement(Evenement const evenement);
        /**
         * @brief Recherche un événement par son nom et retourne son index.
         * @param Enom Le nom de l'événement recherché.
         * @return int L'indice dans le vecteur, ou -1 si non trouvé.
         */
        int recupIndice(const string Enom)const;
        /**
         * @brief Récupère un événement à partir de son indice.
         * @param indice Position de l'événement dans le vecteur.
         * @return Evenement L'objet correspondant.
         */
        Evenement recupEvenement(const unsigned int indice)const;
        /**
         * @brief Retourne le nombre total d'événements enregistrés.
         * @return int Taille de la liste.
         */
        int longueur()const;
};

#endif
