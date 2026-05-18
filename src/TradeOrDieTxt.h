#ifndef _TRADEORDIETXT_H
#define _TRADEORDIETXT_H
#include "simulation.h"
#include <string>
using namespace std;
/**
 * @class TradeOrDieTxt
 * @brief Gère l'interface texte du jeu de trading.
 *
 * La classe TradeOrDieTxt permet de piloter une partie en mode texte
 * en utilisant une instance de Simulation. Elle gère le déroulement
 * du jeu (début, boucle principale, fin), ainsi que les interactions
 * avec le joueur et la gestion des actifs disponibles.
 */
class TradeOrDieTxt{
private:
    ///< Création du jeu 
    Simulation simu;
public:
    /**
     * @brief Constructeur par défaut
     */
    TradeOrDieTxt();
    /**
     * @brief Destructeur
     */
    ~TradeOrDieTxt();
    /** @brief Vérifie le bon fonctionnement des fonctions de la classe */
    static void testRegression();
    /**
     * @brief Initialise le début de la partie
     * Met en place les variables de jeu, initialise la simulation
     * et prépare les actifs disponibles.
     */
    void debutPartie();
    /**
     * @brief Gère la fin de la partie
     *
     * Affiche les résultats finaux et termine la simulation.
     */
    void finPartie();
    /**
     * @brief Boucle principale du jeu
     *
     * Exécute les différentes étapes du jeu (mise à jour, interactions utilisateur,
     * évolution des actifs) jusqu'à la fin de la partie.
     */    
    void loop();



};
#endif
