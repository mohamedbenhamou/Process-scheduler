

    #ifndef PROCESSUS_H_INCLUDED
    #define PROCESSUS_H_INCLUDED
    #include <stdbool.h>
     
    typedef int  booleen;
    #define faux 0
    #define vrai 1
     
     
    typedef struct processus{        // les champs propre à un processus
     
      int Id;                        //un simple identifiant
      int Duree;           // temps d'exucution
      int Date_arrive;               // date d'arrivé
      char Nom[400];               // la tache a executé
      struct processus * next;
    }  processus;
     
    typedef struct listprocessus{            //liste des processus
     
      processus *premier;            // le premier element de la liste
        int nbrprocessus;
    } listeprocessus;
     
     
    // fonctions processus
    processus * nouveau_processus(int id, int duree, int date_arrive,char *nom);
    void afficher_pr(processus* processus);//affiche un processus
     
     
    //fonction liste
    listeprocessus * creer_liste();
    void ajouter_processus(int id, int duree, int date_arrive,char *nom,listeprocessus *l);// ajout d'une nouvelle structure processus a la liste
    int estvide(listeprocessus *l);
    int tailleliste(listeprocessus *l);
    void afficher(listeprocessus *l);//affiche une liste;//affiche une liste
    void supprimer_processus(int id, listeprocessus*l);//suppression d'une structure processus dans la liste definie par son id
    void trie_par_date(listeprocessus *l);
     
    void trie_par_Duree(listeprocessus *l);// on trie la liste des processus par leurs temps d'execution
    int get_increment_max_Id(listeprocessus *l);
    void charger_listep(listeprocessus *l,char *fich);
    processus* chercher_processus(int id,listeprocessus *l);
    void executer_processus(int id,listeprocessus *l);
    //fonction ordonnencement
    void FIFO(listeprocessus *l);
    void check_arrival_time(listeprocessus *L1,listeprocessus *L2,int t);
    void SJF(listeprocessus *l,int quantum);
    void round_robin(listeprocessus *l,int quantum);
     
    #endif // PROCESSUS_H_INCLUDED

