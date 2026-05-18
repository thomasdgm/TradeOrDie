#ifndef _TRADER_H
#define _TRADER_H
#include "actif.h"
#include <map>
#include <string>
using namespace std;

/**
 * @class Trader
 * @brief Représente un trader possédant un portefeuille d'actifs.
 *
 * La classe gère un portefeuille de type map<Actif, float>, où la clé est
 * un Actif et la valeur est la quantité possédée. Elle fournit des méthodes
 * pour acheter et vendre des actifs, récupérer la valeur totale du portefeuille,
 * et effectuer un test de régression simple.
 */
class Trader{

private: 
    ///< Portefeuille du trader.
    map<string, float> portefeuille;

public: 
    /**
     * @brief Constructeur par défaut
     */
    Trader();
    /**
     * @brief Destructeur
     */
    ~Trader();
    /**
     * @brief Test de régression pour vérifier le fonctionnement de la classe
     */
    static void testRegression();
    /**
     * @brief Ajoute une quantité à un actif du portefeuille
     * @param actif Nom de l'actif
     * @param val Quantité à ajouter
     * * @note Si l'actif n'est pas encore présent dans la map, il est créé
     * automatiquement avec la valeur fournie.
     */
    void ajoutMontant(const string actif, const float val);
    /**
     * @brief Récupère la quantité possédée pour un actif donné.
     * @param actif Nom de l'actif
     * @return float La quantité possédée (0.0 si l'actif n'a jamais été initialisé).
     */
    float recupMontant(const string actif)const;
};

#endif
