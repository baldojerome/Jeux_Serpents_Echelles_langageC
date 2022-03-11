#include <time.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct CaseJeu{
    int numCase;
    struct CaseJeu* suivant;
    struct CaseJeu* serpentEchelle;

}CaseJeu;

CaseJeu* creer_case(int valeur)
{
    CaseJeu* c = (CaseJeu*)malloc(sizeof(CaseJeu)); //attribution espace avec malloc 
    if(c != NULL) //test (si reussite malloc alors on poursuis à l'interieur)
    {
        c->numCase = valeur;
        c->suivant = NULL;
        c->serpentEchelle = NULL;
    }

    return c;
}

/*fonction inserer une case de manière classique*/
CaseJeu * InsererTete(CaseJeu* list, int valeur)
{
    CaseJeu* nouveau = creer_case(valeur);
    nouveau->suivant = list;
    //on ne met pas serpent-echelle car il est toujour NULL. Deja null dans creer_case
    return nouveau;
}
//fonction insertion triee de la case 
CaseJeu* Inserertri(CaseJeu* tete, int valeur)
{
    CaseJeu* debut = tete;
    CaseJeu* prec = NULL;

    if(debut == NULL || valeur <= debut->numCase) //si list n'est pas commence ou si list n'a qu'une seule valeur 
    {
        debut  = InsererTete(tete,valeur);
        return debut;
    }
    while(debut != NULL && valeur > debut->numCase) 
    {
        prec = debut;               //boucle qui va naviguer jusquà  
        debut = debut->suivant;     //ou sarreter qaund trouver valeur superieur
    }//on s'arrete entre valeur superieur et precedente 
    prec->suivant = InsererTete(debut,valeur); //on recupere pointeur suivant de precedent pour connecter la nouvelle case

    return tete;
}

//donne le numéro de la derniere case
int dernierCase(CaseJeu* tete)
{
    CaseJeu* list = tete;
    int compteurCase = 0;
    while(list != NULL) //on parcourt jusqu'à la fin et incremente compteur pour avoir numero de case 
    {
        list = list->suivant;
        compteurCase++;
    }

    return compteurCase; 
}

// fonction qui recherche les doublons et renvoie 0 si pas doublons 
int rechercheVal(CaseJeu* tete, int valeur)
{
    CaseJeu* debut = tete;
    

    while(debut != NULL && valeur != debut->numCase)
    {
        debut = debut->suivant;
    }
    if (debut == NULL) //si debut null alors on est la fin sans trouver identique 
    {
        return 0;
    }
    return 1;
}

//fonction permettant de retourner l'adresse d'une case cible en rentrant en paramètre la grille et la valeur recherche
CaseJeu* retournCase (CaseJeu* tete, int valeur)
{
    CaseJeu* list = tete;
    CaseJeu* temporaire;
    // parcours la liste tant que pas fin et si on rencontre pas la meme valeur
    while(list != NULL && valeur != list->numCase)  //s'arrete quand on tombe sur la valeur recherche 
    {
        list = list->suivant;
    }
    if (list != NULL) // on verifie que la list a bien été crée 
    {
        temporaire = list; //adresse de la case /valeur stocke dans temporaire
    }
    return temporaire;
}

//fonction qui lit la grille 
CaseJeu* lire_fichier_grille(char * nom_fichier) {
	CaseJeu * grille = NULL;
    int num;
    int serpentEchelle;
    FILE* f = fopen(nom_fichier,"r"); // read pour récuperer directement les variables
    if(f == NULL)
    {
        exit(1); // si ouverture ne marche pas
    }
    while(!feof(f)) //condition d'arrêt = fin de fichier
    {
        fscanf(f, "%d  %d \n", &num, &serpentEchelle); //fscanf recupere la 1ere et la 2e valeur et le mets dans num et serpentEchelle
//on crée successivement case num et case serpetnEchelle en verifiant pour les 2 si doublons.
        if(rechercheVal(grille,num) == 0) //on fait appel a rechercheVal pour savoir si case n'existe pas déjà
        {
            grille = Inserertri(grille, num);

        }
        CaseJeu* p = retournCase(grille, num); // on conserve l'adresse de la case crée pour num 

        if(serpentEchelle != 0) // si different de 0 alors il faut potentiellement créer une deuxieme case avec int serpentEchelle
        {
            if(rechercheVal(grille,serpentEchelle) == 0) //on fait appel a rechercheVal pour savoir si case n'existe pas déjà
            {
                grille = Inserertri(grille, serpentEchelle); //dans ce cas on crée  la case  aux coordonnes echelleSerpent
            }
            
            CaseJeu* q = retournCase(grille, serpentEchelle); //on conserve l'adresse de la case cree avec serpentEchelle
            p->serpentEchelle = q; // on crée le pointeur serpentEchelle avec @ p et q
        }
    }
    fclose(f);

    return grille;
}
/*
//fonction pour afficher les valeurs. fonction test 
void affiche(CaseJeu* tete)
{
    CaseJeu* list = tete;
    while (list != NULL)
    {
        if (list->serpentEchelle == NULL)
        {
            printf("%d 0 \n", list->numCase);
        }
        else
        {
            printf("%d %d \n", list->numCase, (list->serpentEchelle)->numCase);
        }
        list = list->suivant;
    }
}
*/

// fonction randomize initialise le generateur aleatoire
void randomize(void) 
{
    srand((unsigned) time(NULL));
}

//fonction lancer_un_de ** Retourne un entier choisi aléatoirement entre 1 et 6
int lancer_un_de(void) 
{
    return (rand() % 6) + 1;
}

void jouer_jeu(CaseJeu * grille)
{
	CaseJeu* P = grille;
    int desTotal = 0;
    int premierDes =0;
    int secondDes = 0;
    int numeroCaseCorrect = 0;
    int numStock = 0;
    int arret = 0;
    int rejoue;
    int derCase = dernierCase(P); //on appelle la fonction pour trouver la derniere case 
    while (P->numCase < derCase)
    {
        premierDes = lancer_un_de();
        secondDes = lancer_un_de();     
        desTotal = premierDes + secondDes;
        printf("Vous lancez les des : %d + %d\n",premierDes, secondDes);
        
        if((P->numCase)+desTotal > derCase) // cas quand dépassement de la dernière case
        {  
            numeroCaseCorrect = (2*derCase) - ((P->numCase)+desTotal); //derCase - (((P->numCase)+desTotal)-dernierCase)
            P = retournCase(grille, numeroCaseCorrect); // on appelle retournCase pour localiser la case de recul 
            printf("Lance de des trop eleve : vous reculez en case %d.\n", P->numCase);
        }
        else
        {
            for(int d = 0; d < desTotal; d++) //avancee classique  
            {
                P = P->suivant;
            }
            printf("Vous etes en case %d.\n", P->numCase);
            
        }
        //cas où un pointeur sur serpent ou echelle existe
        if(P->serpentEchelle != NULL)
        {
            numStock = P->numCase; //on stocke @case avant deplacement 
            P = P->serpentEchelle; //on deplace tete de leture 
            if(numStock < P->numCase) //si val initiale + petite que destination alors = echelle 
            {
                printf("Une echelle : vous avancez en case %d.\n", P->numCase);
            }
            else //= serpent 
            {
                printf("Un serpent : vous reculez en case %d.\n", P->numCase);
            }
            
        }
        if (P->numCase != derCase) //tant numero de case pas = arrivee , on demande a chaque fin de boucle 
        {
            printf("Vous voulez-vous rejouer?\n");
            printf("Continuez (pour arreter, saisir 0)  ");
            scanf("%d", &arret);
            printf("\n\n");
            if (arret == 0) //condition pour sortir en cours de partie
            {
                return; 
            }
        }
    }
    printf("FELICITATION. VOUS AVEZ GAGNE!!!\n");
    printf("\n\nREJOUER UNE PARTIE? (Saisissez 0)  ");
    scanf("%d", &rejoue);
    printf("\n\n");
    if(rejoue == 0) //recursivite pour rejouer une partie apres avoir gagne
    {
        printf("NOUVELLE PARTIE \n\n");
        jouer_jeu(grille);
    }

}
//fontion pour supprimer la grille après le jeu 
void supprimer_grille(CaseJeu * grille) 
{
    CaseJeu* list = grille;
//on se concentre uniquement sur pointeur suivant car on supprime la grille en ordre croissant
    while(list != NULL)
    {
        grille = list; //on sauvegarde case actuel // on passe au suivant // et  on supprime la precedente case
        list = list->suivant;
        free(grille);
    }
}

int main()
{
    CaseJeu * grille;
    randomize();
    grille = lire_fichier_grille("serpents-echelles.txt");
    jouer_jeu(grille);
    return 0;
}



