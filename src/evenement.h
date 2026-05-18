#ifndef _EVENEMENT_H
#define _EVENEMENT_H
#include <string>
#include <iostream>
using namespace std;

/**
 * @class Evenement
 * @brief Représente un événement aléatoire impactant les cours du marché.
 * * Un événement peut affecter soit un actif spécifique (ex: une news sur Orange),
 * soit un groupe entier d'actifs (ex: un crash général des cryptomonnaies).
 */
class Evenement{
    private :
        ///< Titre/Nom de l'événement  
        string Enom;
        ///< Texte explicatif affiché au joueur.
        string Edescription;
        ///< Coefficient multiplicateur appliqué au prix 
        float Eimpact;
        ///< Flag indiquant si l'impact touche un groupe d'actifs (true) ou un seul (false).
        bool Egroupe_actif;
        ///< Nom de l'actif ou du groupe visé
        string Enom_actif;

    public:
        /** @brief Constructeur par défaut. */
        Evenement();

        /**
         * @brief Constructeur paramétré pour créer une news économique.
         * @param nom Titre de la news.
         * @param description Détails de l'événement.
         * @param impact Valeur du choc boursier.
         * @param groupe_actif Définit la portée de l'événement.
         * @param nom_actif Cible précise de l'événement.
         */
        Evenement(const string nom, const string description, const float impact, const bool groupe_actif, const string nom_actif );
        /** @brief Destructeur. */
        ~Evenement();
        /** @brief test les fonctions de la classe */
        void testRegression();
        /** @brief Accesseur pour le nom de l'événement.
         *@return string */
        string recupNom()const;
        /** @brief Accesseur pour la description de l'événement. @return string */
        string recupDescription()const;
        /** @brief Récupère la puissance de l'impact financier. @return float */
        float recupImpact()const;
        /** @brief Vérifie si l'événement est global ou ciblé. @return bool */
        bool recupGroupeActif()const;
        /** @brief Récupère le nom de la cible visée par l'impact. @return string */
        string recupNomGroupeActif()const;
};

/**
 * @struct EvenementEnAttente
 * @brief Structure de stockage pour la file d'attente des événements.
 * * Permet de gérer un décalage temporel entre l'apparition d'une news
 * et son impact réel sur les prix (simulation de l'inertie du marché).
 */
struct EvenementEnAttente{
    Evenement e;
    int heureActivation;
};




#endif
