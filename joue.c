#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <joue.h>



void affichePlateauSDL(int** plateau){
    //EN COURS DE DEV
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            printf("%d ", plateau[i][j]);
        }
        printf("\n");
    }
}

void Joue(){
    srand(time(NULL));

    //ouverture d'un fichier pour l'enregistrement de la partie
    //le nom du fichier sera composé de la date et de l'heure du début de la partie
    time_t now;
    time(&now);
    char* nomFichier = ctime(&now);
    printf("Début de la partie: %s\n", nomFichier);
    FILE* fichier = fopen(nomFichier,"w+");


    ///// Affichage /////
    //Si l'initialisation de SDL rencontre un problème, on renvoit le code erreur
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    //Si l'initialisation de TTF rencontre un problème, on renvoit le code erreur
    if(TTF_Init() == -1){
    fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
    exit(EXIT_FAILURE);
    }
    //On choisit la police et la couleur à utiliser pour l'affichage
    TTF_Font* police = NULL;
    police = TTF_OpenFont("angelina.ttf", 65);
    SDL_Color couleurNoire = {0, 0, 0};

    //On créé la surface d'affichage et on définit sa taille
    SDL_Surface* surface = SDL_CreateRGBSurface(SDL_HWSURFACE, 1000, 1000, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000), *texte = NULL;
    SDL_Rect positionSDL;
    positionSDL.x = 0;
    positionSDL.y = 0;

    
    //création du plateau de jeu
    int** plateau = creerPlateau(fichier);

    //boucle de jeu
    int run = 1;
    char input;
    while(run){
        printf("\n");
        affichePlateau(plateau);
        scanf("%s", &input);
        switch(input){
        case 'h':
            joueEnHaut(plateau);
            fprintf(fichier, "%s\n", "h");
            run = 1;
            break;
        case 'b':
            joueEnBas(plateau);
            fprintf(fichier, "%s\n", "b");
            run = 1;
            break;
        case 'g':
            joueAGauche(plateau);
            fprintf(fichier, "%s\n", "g");
            run = 1;
            break;
        case 'd':
            joueADroite(plateau);
            fprintf(fichier, "%s\n", "d");
            run = 1;
            break;
        case 'q':
            run = 0;
            break;
        default:
            printf("veuillez entrer une commande valide.\n");
            run = 1;
            break;
        }
        ajoutCase(plateau, fichier);
        //si la partie est perdue (toutes les cases sont remplies)
        if(verifLoose(plateau)){
            //on affiche un message de fin et on quitte le jeu
            printf("Vous avez perdu!\n");
            run = 0;
        }
        /*
        //on fait l'affichage: 
        texte = TTF_RenderText_Blended(police, "Salut les Zér0s !", couleurNoire);
        SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));
        SDL_BlitSurface(texte, NULL, surface, &positionSDL); //Blit du texte
        SDL_Flip(surface);
        */
        
    }
    //fermeture de TTF
    TTF_CloseFont(police);
    TTF_Quit();

    //fermeture de SDL
    SDL_FreeSurface(surface);
    SDL_Quit();

    //fermeture du fichier de sauvegarde
    fclose(fichier);
}