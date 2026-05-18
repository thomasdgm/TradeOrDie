#ifndef _ACTIF_H
#define _ACTIF_H
#include <string>
#include <vector>
using namespace std;

/**
 * @class Actif
 * @brief Représente un actif financier avec un nom, un type et un historique de valeurs.
 */
class Actif {
private : 
    ///< Nom de l'actif
    string Anom;
    ///< Conteneur de l'historique des prix.
    vector<float> AhistoriqueValeur;
    ///< Catégorie de l'actif déterminant sa volatilité (Crypto, Action, Obligation).
    string Atype;

public : 
    /**
     * @brief Constructeur par défaut
     * Initialise un actif vide sans historique.
     */
    Actif();

    /**
     * @brief Constructeur avec paramètres
     * @param nom Nom de l'actif
     * @param prixOrigine Valeur initiale
     * @param type Type de l'actif
     */
    Actif(const string nom, const float prixOrigine, const string type);
    /**
     * @brief Destructeur de la classe Actif
     */
    ~Actif();
    /**
     * @brief Test de régression
     *Vérifie la validité des méthodes de récupération de nom et d'ajout de valeur.
     */
    static void testRegression();
    /**
     * @brief Modifie le nom de l'actif
     * @param string nom nouveau nom
     */
    void modifNom(const string nom);
    /**
     * @brief Récupère le nom de l'actif
     * @return nom de l'actif
     */
    string recupNom()const;
    /**
     * @brief Récupère la valeur actuelle (dernière valeur) de l'actif
     * @return dernière valeur
     */
    float recupValActuel()const;
    /**
     * @brief Ajoute une valeur à l'historique
     * @param valeur nouvelle valeur
     */
    void ajouterVal(const float valeur);
    /**
     * @brief Récupère une valeur de l'historique
     * @param i Index de la valeur
     * @return valeur correspondante
     */
    float recupVal(const int i);
    /**
     * @brief Récupère le type de l'actif
     * @return Float type de l'actif
     */
    string recupType()const;
    /**
     * @brief Modifie le type de l'actif
     * @param type Nouveau type
     */
    void modifType(const string type);

};
#endif
