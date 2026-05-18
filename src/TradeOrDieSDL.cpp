#include "TradeOrDieSDL.h"
#include <iostream>
#include <sstream>
using namespace std;

const char* FONT = "data/dejavu.ttf";


// Formate un nombre pour l'affichage
string formatFloat(float value, long unsigned int maxLen) {
    ostringstream oss;
    oss << value;
    string s = oss.str();
    // Nettoyage des décimales
    if (s.find('.') != string::npos) {
        s.erase(s.find_last_not_of('0') + 1);
        if (s.back() == '.') {
            s.pop_back();
        }
    }
    // Tronquage si une longueur max est définie
    if(maxLen != 0){
    if (s.length() > maxLen) {
        s = s.substr(0, maxLen);

        if (!s.empty() && s.back() == '.') {
            s.pop_back();
        }
    }}

    return s;
}

void replaceAll(std::string& text, const std::string& from, const std::string& to) {
    size_t pos = 0;
    while ((pos = text.find(from, pos)) != std::string::npos) {
        text.replace(pos, from.length(), to);
        pos += to.length();
    }
}


void drawFilledCircle(SDL_Renderer* renderer, int cx, int cy, int radius, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (int w = -radius; w <= radius; w++) {
        for (int h = -radius; h <= radius; h++) {
            if (w*w + h*h <= radius*radius) {
                SDL_RenderDrawPoint(renderer, cx + w, cy + h);
            }
        }
    }
}


void drawRoundedRect(SDL_Renderer* renderer, int x, int y, int w, int h, int radius, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);


    SDL_Rect rect = { x + radius, y, w - 2 * radius, h };
    SDL_RenderFillRect(renderer, &rect);

    rect = { x, y + radius, w, h - 2 * radius };
    SDL_RenderFillRect(renderer, &rect);

    drawFilledCircle(renderer, x + radius, y + radius, radius, color);
    drawFilledCircle(renderer, x + w - radius - 1, y + radius, radius, color);
    drawFilledCircle(renderer, x + radius, y + h - radius - 1, radius, color);
    drawFilledCircle(renderer, x + w - radius - 1, y + h - radius - 1, radius, color);
}


// Initialise SDL, les polices et crée la fenêtre
TradeOrDieSDL::TradeOrDieSDL(){
    if(SDL_Init(SDL_INIT_VIDEO) !=0){
        cout << "Erreur SDL_Init : " << SDL_GetError() << endl;
        return;
    }    

    if(TTF_Init() < 0){
        cout << "Erreur TTF_Init : " << TTF_GetError() << endl;
        return;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        cout << "Erreur IMG_Init: " << IMG_GetError() << endl;
    }  
    else{// Création de la fenêtre et du renderer
        window = SDL_CreateWindow("TradeOrDie", 200, 200, 1350, 900,SDL_WINDOW_SHOWN);
        SDL_SetWindowResizable(window, SDL_FALSE);
        SDL_SetWindowMinimumSize(window, 1350, 900);
        SDL_SetWindowMaximumSize(window, 1350, 900);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(renderer != NULL){
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);}


        debutPartie();

    }
    

}

TradeOrDieSDL::~TradeOrDieSDL(){
    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window != nullptr) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void TradeOrDieSDL::testRegression(){
    TradeOrDieSDL partie;
    partie.debutPartie();

}

// Gère l'écran d'accueil et le choix de charger une partie ou d'en créer une nouvelle
void TradeOrDieSDL::debutPartie(){
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
    TTF_Font* font50 = TTF_OpenFont(FONT, 45);

    if(simu.partiePresente()){// Logique de l'écran du début de partie
        char continuer = ' ';
        
        afficherText(200, 100, font50, 900, "Voulez vous reprendre votre partie de la derniere fois ?", {255, 255, 255});
        Button oui = {{200, 400, 200, 100}};

        afficherBouton(200, 400, 100, 200, "Oui", font50, {255, 255, 255}, {0, 255, 0});

        Button non = {{800, 400, 200, 100}};

        afficherBouton(800, 400, 100, 200, "Non", font50, {255, 255, 255}, {255, 0, 0});
        

        SDL_Event event;
        SDL_RenderPresent(renderer);
        bool running = true;
        while(running && continuer == ' '){
        while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT){
        running = false;
    }

        if (oui.handleEvent(&event)) {
        continuer = 'y';
        running = false;
        }
        if (non.handleEvent(&event)) {
        continuer = 'n';
        running = false;
        }
    }}

    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);
        
    

        if(continuer == 'y'){
            
            simu.reprendrePartie();
            TTF_CloseFont(font50);
            loop();

        }
        if(continuer == 'n'){
        string text = "Bienvenue dans TradeOrDie\nDans ce jeu, vous devrez speculer sur differents actifs pour vous enrichir le plus possible\nChaque jour, vous commencez a 9h, et finissez a 17h. Vous travaillerez tous les jours de la semaine (pas le week-end)\nA la fin de chaque semaine, l'integralite de vos actifs sont vendus, et une somme vous est preleve\nVous pouvez acheter des fractions de crypto, mais vous etes oblige d'acheter des actions entieres\nBonne chance ! (Cliquez pour continuer)";
        simu.nouvellePartie();
        afficherText(50, 100, font50, 1200, text, {255, 255, 255});
        Button suite = {{0, 0, 1350, 800}};

        SDL_Event event;
        SDL_RenderPresent(renderer);

        bool running = true;
        while(running){
        while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT){
        running = false;
    }

        if (suite.handleEvent(&event)) {
        running = false;
        
        TTF_CloseFont(font50);
        loop();

        }
    }}}
}
else{// Initialisation d'une nouvelle partie et affichage des règles
    string text = "Bienvenue dans TradeOrDie\nDans ce jeu, vous devrez speculer sur differents actifs pour vous enrichir le plus possible\nChaque jour, vous commencez a 9h, et finissez a 17h. Vous travaillerez tous les jours de la semaine (pas le week-end)\nA la fin de chaque semaine, l'integralite de vos actifs sont vendus, et une somme vous est preleve\nVous pouvez acheter des fractions de crypto, mais vous etes oblige d'acheter des actions entieres\nBonne chance ! (Cliquez pour continuer)";
    simu.nouvellePartie();
    afficherText(50, 100, font50, 1200, text, {255, 255, 255});
    Button suite = {{0, 0, 1350, 900}};

    SDL_Event event;
    SDL_RenderPresent(renderer);

    bool running = true;
        while(running){
        while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT){
        running = false;
    }

        if (suite.handleEvent(&event)) {
        running = false;
        
        TTF_CloseFont(font50);
        loop();

        }
    }
}
}}

// Boucle principale du jeu
void TradeOrDieSDL::loop(){
    // Initialisation des variables locales
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);
    bool running = true;
    SDL_Event event;
    // La simulation avance toutes les 10 secondes réelles
    int nextTimestamp;
    time_t now;
    time(&now);
    nextTimestamp = now + 10;
    // Variables d'état de l'interface
    unsigned int actifActuel = 0;
    bool needtorefresh = true;
    bool newday = true;
    vector<Button> actifs;
    vector<string> tabAct;
    vector<float> pru;
    vector<EvenementEnAttente> fileAttente;
    int j;
    int h;
    vector<float> currentGraph;
    SDL_Color fontColor = {255, 255, 255};
    string fontPolice = FONT;
    double saisie = 0;
    unsigned int nbrSaisie = 0;
    Button sell;
    Button buy;
    Button all;
    SDL_Keycode key;
    SDL_Scancode sc;
    float perf;
    bool allEnable;
    string text;
    // Chargement des polices de différentes tailles
    TTF_Font* font30 = TTF_OpenFont(FONT, 30);
    TTF_Font* font39 = TTF_OpenFont(FONT, 39);
    TTF_Font* font50 = TTF_OpenFont(FONT, 50);

    while(running){

        time(&now);
        if(now >= nextTimestamp){// Gestion du temps, avance la simulation toutes les 10 secondes
            simu.prochaineHeure();
            nextTimestamp = now + 10;
            needtorefresh = true;
            newday = true;
        }

        

        if (needtorefresh){// Si besoin de rafraîchir, on redessine toute l'interface
        Uint32 frameStart = SDL_GetTicks();

        j = simu.jourActuel();
        h = simu.heureActuel();
        actifs = {};   
        tabAct = simu.returnTabAct();
        pru = simu.returnPru();
        unsigned int t = j*9 + (h-9)%17;

        needtorefresh = false;

        if(h == 9 && j != 0 && j%5 == 0 && newday){
            SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
            SDL_RenderClear(renderer);
            afficherText(200, 100, font50, 900, "Fin de la semaine\nTout vos actifs on ete vendue, et une somme de " + formatFloat(2000 * pow(1.1,(j/5) -1), 0) + " vous a ete preleve", {255, 255, 255});
            SDL_RenderPresent(renderer);
            time(&now);
            nextTimestamp = now + 3;
            while(now < nextTimestamp){
                time(&now);
            }
            
            nextTimestamp = now + 10;
            newday = false;
        }


        
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);
        // Dessin de l'interface
        afficherLigne(350, 0, 350, 800, 2, fontColor); 
        afficherText(360, 0, font50, 200, "Jour : " + to_string(j + 1), fontColor);
        afficherText(560, 0, font50, 300, "Heure : " + to_string(h), fontColor);
        afficherText(950, 0, font50, 450, "Solde : " + formatFloat(simu.recupTotalValeur(), 0) + "e", fontColor);
        // Affichage de la liste latérale des actifs avec leurs variations de prix
        int y = 0;
        float pourcent;
        string textAct;
        int debutbouton;
        for(unsigned int i = 0; i < simu.nbrActif(); i++){// Boucle sur les actifs pour créer la liste à gauche
            debutbouton = y;
            // Calcul de la variation en pourcentage pour la couleur
            
            textAct = tabAct[i] + " (" + simu.recupTypeActif(tabAct[i]) + ")";
            afficherText(0, y, font39, 350, textAct, fontColor);
            SDL_Surface* TextSurface = TTF_RenderText_Blended_Wrapped(font39, textAct.c_str(), fontColor, 350);
            y += TextSurface->h;
            SDL_FreeSurface(TextSurface);
            textAct = formatFloat(simu.recupValActif(tabAct[i]), 6) + "e";
            afficherText(0, y, font39, 160, textAct, fontColor);

            TextSurface = TTF_RenderText_Blended_Wrapped(font39, textAct.c_str(), fontColor, 160);
            

            if(i == 0){
                afficherText(80, y, font39, 270, "(" + formatFloat(simu.recupMontantActif(tabAct[i]), 0) + "e)", fontColor);
            }


            if(i!= 0 && t!= 0){
            pourcent = ((simu.recupValActif(tabAct[i]) - simu.recupValActifTemp(tabAct[i], t-1) )/simu.recupValActifTemp(tabAct[i], t-1))*100;
            if(pourcent < 0 ){
                fontColor = {255, 0, 0};
                afficherText(170, y + 5, font30, 200, formatFloat(pourcent, 6) + "%", fontColor);
            }
            else{

                fontColor = {0, 255, 0};
                afficherText(170, y + 5, font30, 200, "+" + formatFloat(pourcent, 6) + "%", fontColor);}

            fontColor = {255, 255, 255};
        }

            y += TextSurface->h;
            SDL_FreeSurface(TextSurface);

            actifs.push_back({{0, debutbouton, 350, y-debutbouton}});

            afficherLigne(0, y, 350, y, 2, fontColor);
            
    
        }
        // Si un actif est sélectionné, on affiche son graphique et les options d'achat/vente
        if(actifActuel != 0){
            currentGraph = {};
            for(unsigned int i = t - (h - 9); i <= t; i++){
                currentGraph.push_back(simu.recupValActifTemp(tabAct[actifActuel], i));
                
            }


            afficherText(550, 100, font39, 500, tabAct[actifActuel] + "(" + formatFloat(simu.recupValActif(tabAct[actifActuel]), 6) + "e)", fontColor);
            afficherGraph(450, 150, 500, 9, currentGraph);
            ostringstream oss;
            oss << saisie;
            if(allEnable){afficherText(1000, 280, font39, 300, "Tout", fontColor);}
            else{
            if((oss.str().size() == nbrSaisie && saisie > 0 ) || nbrSaisie == 0 ){
            afficherText(1000, 280, font39, 300, formatFloat(saisie, nbrSaisie), fontColor);}
            else{
            afficherText(1000, 280, font39, 300, formatFloat(saisie, nbrSaisie-1) + ".", fontColor);
            }}

            sell = {{1000, 150, 200, 100}};

            
            afficherBouton(1000, 150, 100, 200, "acheter", font50, {255, 255, 255}, {0, 255, 0});

            buy = {{1000, 350, 200, 100}};


            afficherBouton(1000, 350, 100, 200, "vendre", font50, {255, 255, 255}, {255, 0, 0});

            all = {{1200, 250, 100 , 100}};

            afficherBouton(1200, 250, 100, 100, "tout", font30, {0, 0, 0}, {255, 255, 255});

            afficherText(375, 700, font39, 400, "Quantite : " + formatFloat(simu.recupMontantActif(tabAct[actifActuel]), 0) + "   (" + formatFloat(simu.recupValeur(tabAct[actifActuel]), 0) + "e)", fontColor);
            if(pru[actifActuel] != 0){
                afficherText(800, 700, font39, 300, "Performance : ", fontColor);
                perf = ((simu.recupValActif(tabAct[actifActuel]) - pru[actifActuel] )/pru[actifActuel])*100;

                if(perf > 0 ){fontColor = {0, 255, 0};}
                else{if(perf < 0){fontColor = {255, 0, 0}; }}

                afficherText(1080, 700, font39, 270, formatFloat(perf, 0) + "%", fontColor);
                fontColor = {255, 255, 255};}
        

        }
        else{
            string text = "Bienvenue dans TradeOrDie\nDans ce jeu, vous devrez speculer sur differents actifs pour vous enrichir le plus possible\nChaque jour, vous commencez a 9h, et finissez a 17h. Vous travaillerez tous les jours de la semaine (pas le week-end)\nA la fin de chaque semaine, l'integralite de vos actifs sont vendus, et une somme vous est preleve\nVous pouvez acheter des fractions de crypto, mais vous etes oblige d'acheter des actions entieres\nBonne chance !";
            afficherText(360, 100, font39, 990, text, {255, 255, 255});
            allEnable = false;
            saisie = 0;
            nbrSaisie = 0;
            sell = {{0, 0, 0, 0}};
            buy = {{0, 0, 0, 0}};
        }



        afficherLigne(350,800,1350,800, 2, fontColor);
        fileAttente = simu.returnEvent();
        afficherText(0, 755, font39, 330, "Actualite : ", fontColor);

        if(fileAttente.empty()){
            text = "    Aucune actualite recente " ;}
        else{
            text = "    " + fileAttente[0].e.recupDescription();
            replaceAll(text, "é", "e");
            replaceAll(text, "è", "e");
            replaceAll(text, "à", "a");
            replaceAll(text, "€", " euros");
            replaceAll(text, "ô", "o");
        }

        afficherText(0, 800, font39, 1350, text, fontColor);
        
        SDL_RenderPresent(renderer);

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        cout << "Frame time: " << frameTime << " ms\n";

    }


        // Gestion des événements
        while(SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                running = false;
            }
            // Clic sur Achat / Vente / Bouton "Tout"
            if(sell.handleEvent(&event) && actifActuel != 0){
                if(allEnable){saisie = simu.recupMontantActif("Euro")/simu.recupValActif(tabAct[actifActuel]);}
                if(simu.achatActif(tabAct[actifActuel], saisie)){
                    needtorefresh = true;
                    saisie = 0;
                    nbrSaisie = 0;
                    allEnable = false;
                }

            }
            if(buy.handleEvent(&event) && actifActuel != 0){
                if(allEnable){saisie = simu.recupMontantActif(tabAct[actifActuel]);}
                if(simu.vendreActif(tabAct[actifActuel], saisie)){
                    needtorefresh = true;
                    saisie = 0;
                    nbrSaisie = 0;
                    allEnable = false;
                }

            }

            if(all.handleEvent(&event) && actifActuel != 0){
                    allEnable = true;
                    needtorefresh = true;
                    saisie = 0;
                    nbrSaisie = 0;
                

            }

            for(unsigned int i = 0; i < actifs.size(); i++){
                if( actifs[i].handleEvent(&event)){
                    if(i != actifActuel){
                        saisie = 0;
                        nbrSaisie = 0;
                    }
                    actifActuel = i;
                    allEnable = false;
                    needtorefresh = true;
                }}

                if (event.type == SDL_KEYDOWN  && event.key.repeat == 0) {
                key = event.key.keysym.sym;
                sc = event.key.keysym.scancode;

                if((key >= SDLK_0 && key <= SDLK_9) || (sc >= SDL_SCANCODE_KP_0 && sc <= SDL_SCANCODE_KP_9)){
                    int num;
                if (key >= SDLK_0 && key <= SDLK_9) {
                    num = key - '0';
                }
                else{
                    num = sc - SDL_SCANCODE_KP_0 - '0';
                }
                ostringstream oss;
                oss << saisie;
                if(nbrSaisie < 6){
                if((oss.str().size() == nbrSaisie && saisie > 0 ) || nbrSaisie == 0 ){
                    saisie = stof((formatFloat(saisie, nbrSaisie)) + to_string(num));}
                else{
                    saisie = stof((formatFloat(saisie, nbrSaisie)) + "." + to_string(num));}
                oss << saisie;
                nbrSaisie ++;
                
                needtorefresh = true;}
    
            }
            
            ostringstream oss;
            oss << saisie;
            if(nbrSaisie < 6){
            if((key == 59 || key == 1073741923) && (oss.str().size() == nbrSaisie || nbrSaisie == 0) && (int)saisie == saisie){
                   nbrSaisie ++;
                   needtorefresh = true;
                }}

            if(key == 8 && allEnable){allEnable = false;
            needtorefresh = true;
            }

            if(key == 8 && nbrSaisie > 0){
                ostringstream oss;
                oss << saisie;
                if(allEnable){allEnable = false;}
                else{
                if((oss.str().size() == nbrSaisie && saisie > 0 ) || nbrSaisie == 0 ){
                    string tmp = (formatFloat(saisie, nbrSaisie));
                    tmp.pop_back();
                    oss << saisie;
                    nbrSaisie --;
                    if(nbrSaisie == 0){saisie = 0;}
                    else{saisie = stof( tmp );}
                }
                else{
                nbrSaisie --;
                }}

                needtorefresh = true;
            }
            }   
        }// Vérification de la condition de défaite
        if(simu.partiePerdu()){
            running = false;
            finPartie();}

    }
        TTF_CloseFont(font30);
        TTF_CloseFont(font39);
        TTF_CloseFont(font50);
}

void TradeOrDieSDL::finPartie(){
    TTF_Font* font50 = TTF_OpenFont(FONT, 50);// Chargement de la police pour le message de fin

    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);// Nettoyage de l'écran avec la couleur de fond
    SDL_RenderClear(renderer);

    string text =  "Vous avez perdu au bout de " + to_string(simu.jourActuel()) + " jours (cliquez si vous voulez relancer une partie)";// Préparation du message personnalisé affichant le score
    afficherText(200, 100, font50, 900, text, {255, 255, 255});

    Button suite = {{0, 0, 1350, 800}};

    SDL_RenderPresent(renderer);

    simu.supprimerPartie();// Suppression du fichier de sauvegarde car la partie est terminée
    SDL_Event event;
    bool running = true;
    while(running){// Boucle d'attente : on laisse la fenêtre ouverte
        while(SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                TTF_CloseFont(font50);
                running = false;
            }
            if (suite.handleEvent(&event)) {
                TTF_CloseFont(font50);
                running = false;
                simu = Simulation();
                debutPartie();

        }

        }}
    
}

// Fonction de dessin de texte avec gestion de la mémoire
void TradeOrDieSDL::afficherText(int x, int y, TTF_Font* font, const int size, const string txt, const SDL_Color TextColor){

    SDL_Surface* TextSurface = TTF_RenderText_Blended_Wrapped(font, txt.c_str(), TextColor, size);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, TextSurface);
    // Positionnement et rendu
    SDL_Rect DstRect;
    DstRect.x = x;
    DstRect.y = y;
    DstRect.w = TextSurface->w;
    DstRect.h = TextSurface->h;

    SDL_RenderCopy(renderer, texture, NULL, &DstRect);

    SDL_DestroyTexture(texture);// Nettoyage immédiat des ressources
    SDL_FreeSurface(TextSurface);


}

// Affichage d'une image
void TradeOrDieSDL::afficherImage(const int x, const int y, const int size, const char* path){

    SDL_Surface* image = IMG_Load(path);// Chargement du fichier image

    if (!image) {
    cout << "Erreur IMG_Load: " << IMG_GetError() << endl;
    return;
}// Vérifie si le fichier est introuvable ou corrompu

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);

    SDL_Rect DstRect;// Calcul des dimensions de destination
    DstRect.x = x;
    DstRect.y = y;
    float ratio = 1.0f*size/(image->w);// Calcul du ratio pour garder les proportions d'origine
    DstRect.w = (image->w)*ratio;// Largeur finale égale à size
    DstRect.h = (image->h)*ratio;// Hauteur ajustée proportionnellement

    SDL_RenderCopy(renderer, texture, NULL, &DstRect);

    SDL_DestroyTexture(texture);// Nettoyage immédiat des ressources
    SDL_FreeSurface(image);
}

// Dessine le graphique boursier d'un actif
void TradeOrDieSDL::afficherGraph(const int x, const int y, const int size, const int maxVal, const vector<float> vals){
    SDL_Color color = {255, 255, 255};
    // Dessine le cadre du graphique
    afficherLigne(x, y, x+size, y, 5, color);
    afficherLigne(x+size, y, x+size, y+size, 5, color);
    afficherLigne(x+size, y+size, x, y+size, 5, color);
    afficherLigne(x, y+size, x, y, 5, color);
    // Calcule la moyenne et l'échelle pour que la courbe tienne dans le cadre
    int midy = (2*y+size)/2;

    afficherLigne(x , midy, x+size, midy, 1, color);// Dessine la ligne d'horizon (la moyenne) au centre du graphique

    float avg = 0.0f;
    for (unsigned int i = 0; i < vals.size(); i++) {
        avg += vals[i];
    }
    avg = avg / vals.size();// Calcul de la valeur moyenne de l'historique

    float max = 0.0f;
    for (unsigned int i = 0; i < vals.size(); i++) {
    float diff = fabs(avg - vals[i]);
    if(diff > max){
        max = diff;}// Recherche de l'écart maximal par rapport à la moyenne
    }
    
    
    if (max == 0) max = 1;// Sécurité pour éviter une division par zéro si le prix est constant
    int saut = size/(maxVal -1);// Calcul de l'espacement horizontal entre deux points du graphique

    int maxpix = (size/2) *3/4;// Définit la hauteur maximale que peut prendre la courbe (75% de la demi-fenêtre)

    for(unsigned int i = 0; i<vals.size()-1; i++ ){// Boucle de tracé des segments de la courbe

        afficherLigne(x + i*saut, midy + maxpix*(avg - vals[i])/max, x + (i+1)*saut, midy + maxpix*(avg - vals[i+1])/max, 5, color );
    }
}

// Affiche une ligne
void TradeOrDieSDL::afficherLigne(const int x1, const int y1, const int x2, const int y2, const int epaisseur, const SDL_Color Color){

    SDL_SetRenderDrawColor(renderer, Color.r, Color.g, Color.b, 255);// Définit la couleur de dessin du renderer
    float dx = x2 - x1;// Calcul du vecteur direction
    float dy = y2 - y1;
    float length = sqrtf(dx*dx + dy*dy);// Calcul de la distance entre les deux points

    float ux = -dy / length;
    float uy = dx / length;

    for (int i = -epaisseur/2; i <= epaisseur/2; i++) {// Boucle pour dessiner plusieurs lignes côte à côte selon l'épaisseur voulue
        int offsetX = (int)(i * ux);
        int offsetY = (int)(i * uy);
        SDL_RenderDrawLine(renderer, x1 + offsetX, y1 + offsetY, x2 + offsetX, y2 + offsetY);
    }
}



void TradeOrDieSDL::afficherBouton(const int x, const int y, const int h, const int w, const string txt,  TTF_Font* font, const SDL_Color TextColor, const SDL_Color BackgroundColor ){

     SDL_Renderer* renderer = this->renderer; // supposé existant

    
    int radius = h / 2;

    
    drawRoundedRect(renderer, x, y, w, h, radius, BackgroundColor);

    
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, txt.c_str(), TextColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    int textW = textSurface->w;
    int textH = textSurface->h;

    SDL_FreeSurface(textSurface);

    SDL_Rect dstRect;
    dstRect.x = x + (w - textW) / 2;
    dstRect.y = y + (h - textH) / 2;
    dstRect.w = textW;
    dstRect.h = textH;

    SDL_RenderCopy(renderer, textTexture, nullptr, &dstRect);
    SDL_DestroyTexture(textTexture);
    



}



