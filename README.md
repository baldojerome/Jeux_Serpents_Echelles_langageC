# Jeux_Serpents_Echelles_langageC

PREREQUIS

• ide fonctionnant pour le langage C ou shell

• bien compiler et exécuter avec le fichier serpents-echelles.txt

OBJECTIF 

• ce projet programme le jeu bien connu des enfants : serpents et échelles. 

• Ce jeu est une variante du jeu de l’oie. 

• La version programmée est pour un seul joueur, l’objectif étant de réussir en un minimum de coups.

REGLES DU JEU

• Le joueur lance deux dés à 6 faces ;

• Il avance d’un nombre de cases correspondant au total des deux dés :

    • Si la case d’arrivée est une échelle, le joueur avance jusqu’à la case correspondant à l’autre extrémité de l’échelle ;
    
    • Si la case d’arrivée est la tête d’un serpent, le joueur recule jusqu’à la case correspondant à la queue du serpent ;
    
    • Si le total des dés ajoutés au numéro de la case dépasse 100, le joueur recule d’un nombre de case égal à la différence 
      (ex. le joueur est à la case 97, le joueur obtient 4 et 5, le joueur avance de 3 pour atteindre la case 100 puis recule de 6 pour atteindre la case 94).
      
• Le jeu se termine quand la case 100 est atteinte avec un nombre exact de cases à traverser.




