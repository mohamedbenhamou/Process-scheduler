

    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #include <unistd.h>
    #include "processus.h"
     
    int menu () {
      printf("\n/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
      printf ("\n\n\n\n Partie 1 : Ordonnanceur de processus.\n\n");
      printf ("\n\n Ce programme lit automatiquement les processus a partir d'un fichier nomme 'data.txt' qui doit etre passe en parametre suivis de la politique d'ordonnancement souhaiter.\n\n");
     
      printf ("0  - Fin du programme.\n");
      printf ("1  - Politique d ordonnancement FCFS.\n");
      printf ("2  - Politique d ordonnancement SJF Preemptif.\n");
      printf ("3  - Politique d ordonnancement Round-Robin Preemptif. \n");
     printf ("Votre choix ? ");
      int cod; scanf ("%d", &cod); getchar();
      printf ("\n");
      return cod;
    }
     
    int main(int argc, char *argv[] )
    {
        if(argc!=2)
        {
            printf("Veuillez entrez le nom du fichier qui contient les processus a executer. Merci ^__^");
            return 0;
        }
        printf("Program name is: %s\n", argv[0]);
        printf("The file name is: %s\n", argv[1]);
     
        listeprocessus *l;
        l=creer_liste();
        int quantum;
        booleen fini = faux;
        while(!fini){
            switch (menu()){
            case 0 :
                fini=vrai;
                printf("Au revoir \n ");
                break;
            case 1 :
                printf ("1  - Politique d ordonnancement FCFS.\n\n");
                charger_listep(l,argv[1]);
                FIFO(l);
                printf ("\n");
                break;
     
            case 2 :
                printf ("2  - Politique d ordonnancement SJF Preemptif.\n\n");
                printf ("*****************donner la valeur du quantum desirer********************\n");
                scanf("%d",&quantum);
                charger_listep(l,argv[1]);
                SJF(l,quantum);
                printf ("\n");
                break;
     
            case 3:
                 printf ("3  - Politique d ordonnancement Round-Robin.\n\n");
                 printf ("*****************donner la valeur du quantum desirer********************\n");
                 scanf("%d",&quantum);
                 charger_listep(l,argv[1]);
                 round_robin(l,quantum);
                 printf ("\n");
                 break;
     
     
            default:
                printf("Aucun Politique d ordonnancement n'a ete mentionner  donc la politique FCFS sera choisi.\n\n");
                charger_listep(l,argv[1]);
                FIFO(l);
                printf ("\n");
                break;
     
     
            }
        }
        return 0;
    }

