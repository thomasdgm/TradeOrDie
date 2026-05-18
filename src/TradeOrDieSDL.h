#ifndef _TRADEORDIESDL_H
#define _TRADEORDIESDL_H
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "simulation.h"
#include <numeric>
using namespace std;

/**
 * @class TradeOrDieSDL
 * @brief Gère l'interface graphique du jeu en utilisant la bibliothèque SDL2.
 * * Cette classe est responsable de l'affichage de la fenêtre, du rendu des graphiques boursiers,
 * de la gestion des textures (images) et de l'écriture de texte via SDL_ttf.
 */
class TradeOrDieSDL {
    private : 
        ///< Pointeur vers la fenêtre principale de l'application.
        SDL_Window * window;
        ///< Pointeur vers le moteur de rendu (renderer) lié à la fenêtre.
        SDL_Renderer * renderer;
        ////< Instance de la simulation contenant les données logiques.
        Simulation simu;
    
    public :
        /** @brief Constructeur par défaut. */
        TradeOrDieSDL();

        /** @brief Destructeur */
        ~TradeOrDieSDL();

        /** @brief vérifie le bon fonctionnement des fonctions de classes */
        static void testRegression();
        /**
        * @brief Affiche du texte à l'écran.
        * @param x Coordonnée horizontale.
        * @param y Coordonnée verticale.
        * @param font Pointeur vers la police chargée.
        * @param size Taille du texte.
        * @param txt Chaîne de caractères à afficher.
        * @param TextColor Couleur du texte (SDL_Color).
        */
        void afficherText(int x, int y, TTF_Font* font, const int size, const string txt, const SDL_Color TextColor);

        /**
         * @brief Affiche une image (texture) à l'écran.
         * @param x Coordonnée x du coin supérieur gauche.
         * @param y Coordonnée y du coin supérieur gauche.
         * @param size Multiplicateur de taille ou dimension.
         * @param path Chemin vers le fichier image (PNG, JPG, etc.).
         */
        void afficherImage(const int x, const int y, const int size, const char* path);

        /**
         * @brief Dessine un graphique boursier à partir d'un historique de valeurs.
         * @param x Position horizontale de la base du graphique.
         * @param y Position verticale de la base du graphique.
         * @param size Largeur du graphique à l'écran.
         * @param maxVal Valeur maximale pour l'échelle verticale.
         * @param vals Vecteur contenant l'historique des prix.
         */
        void afficherGraph(const int x, const int y, const int size, const int maxVal, const vector<float> vals);

        /**
         * @brief Dessine une ligne segmentée avec une épaisseur donnée.
         * @param x1 Point de départ X.
         * @param y1 Point de départ Y.
         * @param x2 Point d'arrivée X.
         * @param y2 Point d'arrivée Y.
         * @param epaisseur Épaisseur de la ligne en pixels.
         * @param Color Couleur de la ligne (SDL_Color).
         */
        void afficherLigne(const int x1, const int y1, const int x2, const int y2, const int epaisseur, const SDL_Color Color);
        /**
         * @brief Dessine un bouton.
         * @param x Coordonnée x du coin supérieur gauche.
         * @param y Coordonnée y du coin supérieur gauche.
         * @param h Taille du bouton ( horizontale ).
        * @param w Taille du bouton ( verticale ).
         * @param txt Text a mettre dans le bouton.
         * @param font Pointeur vers la police chargée.
         * @param TextColor Couleur du texte (SDL_Color).
         * @param BackgroundColor Couleur ddu fond (SDL_Color).
         */
        void afficherBouton(const int x, const int y, const int h, const int w, const string txt,  TTF_Font* font, const SDL_Color TextColor, const SDL_Color BackgroundColor );
        /** @brief Initialise la fenêtre graphique et lance la partie. */
        void debutPartie();
        /** @brief Boucle de rendu graphique et gestion des événements (clic, clavier). */
        void loop();
        /** @brief Nettoie les ressources SDL et ferme la fenêtre. */
        void finPartie();

};

/**
 * @struct Button
 * @brief Structure utilitaire pour créer des zones cliquables (boutons) dans l'interface.
 */
struct Button {
    /** @brief Rectangle définissant la position et la taille du bouton.*/
    SDL_Rect rect;
    /** @brief État du bouton (cliquable ou non). */
    bool active = true;

    /**
     * @brief Dessine le bouton sur le renderer.
     * @param renderer Le moteur de rendu SDL.
     */
    void render(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 0, 120, 255, 255);
        SDL_RenderFillRect(renderer, &rect);
    }

    /**
     * @brief Détecte si le bouton a été cliqué.
     * @param event Pointeur vers l'événement SDL capturé.
     * @return true Si le clic gauche a eu lieu à l'intérieur du rectangle.
     */
    bool handleEvent(SDL_Event* event) {
        if (event->type == SDL_MOUSEBUTTONDOWN && active) {
            int x = event->button.x;
            int y = event->button.y;

            if (x >= rect.x && x <= rect.x + rect.w &&
                y >= rect.y && y <= rect.y + rect.h) {
                return true;
            }
        }
        return false;
    }
};


#endif
