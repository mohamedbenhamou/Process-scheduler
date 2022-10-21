

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "processus.h"
     
     
     
     
    processus * nouveau_processus(int id, int duree, int date_arrive,char *nom){  //creation d'un nouvelle structure processus
     
      processus * nouveau = (processus *) malloc(sizeof(processus));
      if(nouveau == NULL){
         printf("un probleme est survenue lors de la creation d'une structure processus!\n");
         exit(0);
      }
     
      nouveau->Id = id;
      nouveau->Duree = duree;
      nouveau->Date_arrive = date_arrive;
      strcpy(nouveau->Nom, nom);
      nouveau->next=NULL;
     
     
      return nouveau;
    }
     
    void afficher_pr(processus* tmp){
      printf("%d %d %d %s \n",tmp->Id,tmp->Date_arrive,tmp->Duree,tmp->Nom);
    }
     
    listeprocessus * creer_liste(){       //creation d'une liste
      listeprocessus * l;
      l = (listeprocessus *)malloc(sizeof(listeprocessus));
      l->premier=NULL;
      l->nbrprocessus=0;
      if(l == NULL){
          printf("un probleme est survenue lors de la creation de la liste\n !");
          exit(0);
      }
    return l;
    }
     
    void ajouter_processus(int id, int duree, int date_arrive,char *nom, listeprocessus *l){
        processus *tmp;
     
      if( l->nbrprocessus==0 ){
     
        l->premier = nouveau_processus(id,duree,date_arrive,nom);
        l->nbrprocessus++;
      }
      else{
        tmp = l->premier;
        while(tmp->next != NULL){
          tmp = tmp->next;
        }
        tmp->next = nouveau_processus(id,duree,date_arrive,nom);
        l->nbrprocessus++;
      }
    }
     
    int tailleliste(listeprocessus *l){
        int a = 0;
        processus *tmp = l->premier;
        while(tmp != NULL){
               a++;
               tmp = tmp->next;
        }
       return a;
    }
     
    void afficher(listeprocessus *l){//affiche une liste
       processus *tmp = l->premier;
       if(tmp == NULL) printf("la liste est vide");
       while(tmp != NULL){
        afficher_pr(tmp);
            tmp = tmp->next;
        }
    }
     
    void supprimer_processus(int id, listeprocessus *l){//suppression d'une structure processus dans la liste definie par son id
     
       processus *tmp;
       int d ;
       if(l->nbrprocessus!=0){
        d = (l->premier->Id == id);
        if(d){
                l->premier = l->premier->next;
                l->nbrprocessus--;
        }
        else{
                tmp = l->premier;
                while(!d && tmp!=NULL){
                if(tmp->next->Id == id) d = 1;
                else tmp = tmp->next;
                }
                if(d){
                    tmp->next = tmp->next->next;
                    l->nbrprocessus--;
     
                }
        }
       }
     
    }
     
    void trie_par_date(listeprocessus *l){
      processus *p1 = l->premier;
      processus *p2, *min;
      int  t;
      char tmp[400];
     
      while(p1 != NULL){
     
        p2 = p1;
        min = p2;
        while(p2 != NULL){
          if(min->Date_arrive > p2->Date_arrive){
            min = p2;
          }
          p2 = p2->next;
        }
     
        t = p1->Id;
        p1->Id = min->Id;
        min->Id = t;
        t = p1->Duree;
        p1->Duree = min->Duree;
        min->Duree = t;
        t = p1->Date_arrive;
        p1->Date_arrive = min->Date_arrive;
        min->Date_arrive = t;
        strcpy(tmp, p1->Nom);
        strcpy(p1->Nom, min->Nom);
        strcpy(min->Nom,tmp);
     
        p1 = p1->next;
     
      }
    }
     
    void trie_par_Duree(listeprocessus *l){
     
      processus *p1 = l->premier;
      processus *p2, *min;
      int  t;
      char tmp[400];
     
      while(p1 != NULL){
     
        p2 = p1;
        min = p2;
        while(p2 != NULL){
          if(min->Duree> p2->Duree){
            min = p2;
          }
          p2 = p2->next;
        }
     
        t = p1->Id;
        p1->Id = min->Id;
        min->Id = t;
        t = p1->Duree;
        p1->Duree = min->Duree;
        min->Duree = t;
        t = p1->Date_arrive;
        p1->Date_arrive = min->Date_arrive;
        min->Date_arrive = t;
        strcpy(tmp, p1->Nom);
        strcpy(p1->Nom, min->Nom);
        strcpy(min->Nom,tmp);
     
        p1 = p1->next;
     
      }
    }
     
    int get_increment_max_Id(listeprocessus *l){
    int max = 0;
        processus *p = l->premier;
        while(p != NULL){
            if(p->Id > max) max = p->Id;
            p = p->next;
        }
       return max+1;
    }
    void charger_listep(listeprocessus *l,char *fich){
        FILE *F;
        int a,b;
        char t[400];
        int i;
     
        F = fopen(fich,"r");
        if(F == NULL){
        printf("un probléme lors de l'ouverture du fichier\n");
            exit(0);
        }
     
        while(!feof(F)){
        fscanf(F,"%d %d %s",&a,&b,t);
            ajouter_processus(get_increment_max_Id(l),b,a,t,l);
     
        }
       i = get_increment_max_Id(l);
       supprimer_processus(i-1,l);
       fclose(F);
     
    }
    processus* chercher_processus(int id,listeprocessus *l){
        int d = 0;
         processus *tmp = l->premier;
         while(tmp != NULL && d==0){
            if(tmp->Id == id) d = 1;
            else tmp = tmp->next;
         }
         return tmp;
    }
     
    void executer_processus(int id,listeprocessus *l){
        processus * tmp;
        tmp=chercher_processus(id,l);
        if(tmp!=NULL)
        {
     
            if(tmp->Duree>0){
                printf("%s  ",tmp->Nom);
                tmp->Duree--;
     
            }
        }
    }
     
     
    void FIFO(listeprocessus *l){
    processus *tmp;
    trie_par_date(l);
    int t=0;
    while(l->nbrprocessus!=0){
        tmp=l->premier;
        if(tmp->Date_arrive<=t){
            while(tmp->Duree>0){
                if(tmp->Duree>1){
                    executer_processus(tmp->Id,l);
                    t++;
                }
                else{
                    executer_processus(tmp->Id,l);
                    t++;
                    supprimer_processus(tmp->Id,l);
                }
            }
        tmp=tmp->next;
        }
        else{
            printf("-");
            t++;
        }
    }
    }
     
    void check_arrival_time(listeprocessus *L1 ,listeprocessus *L2,int t){
        processus *tmp;
        tmp=L1->premier;
        while(tmp!=NULL){
            if(tmp->Date_arrive<=t){
                ajouter_processus(tmp->Id,tmp->Duree,tmp->Date_arrive,tmp->Nom,L2);
                supprimer_processus(tmp->Id,L1);
            }
            tmp=tmp->next;
     
        }
    }
     
     

    void SJF(listeprocessus *l,int quantum){
        listeprocessus *tml;
        tml=creer_liste();
        processus *tmp , *tmpl;
        trie_par_date(l);
        int t=0,i;
        while(t>=0){
            if(l->nbrprocessus==0 && tml->nbrprocessus==0)
                break;
            tmp=l->premier;
            check_arrival_time(l,tml,t);
            if(tml->nbrprocessus!=0){
                while(tml->nbrprocessus!=0){
                    trie_par_Duree(tml);
                    tmpl=tml->premier;
     
                    if(tmpl->Duree!=0){
                        for(i=0;i<quantum;i++){
                                executer_processus(tmpl->Id,tml);
                                t++;
                                check_arrival_time(l,tml,t);
                                if(tmpl->Duree==0) break;
     
                        }
     
                     supprimer_processus(tmpl->Id,tml);
                     if(tmpl->Duree!=0) ajouter_processus(tmpl->Id,tmpl->Duree,tmpl->Date_arrive,tmpl->Nom,tml);
                    }
                    else{
                        supprimer_processus(tmpl->Id,tml);
                        check_arrival_time(l,tml,t);
                    }
            }
            }
            else{
                printf("-");
                t++;
            }
        }
    }
    void round_robin(listeprocessus *l,int quantum){
     
        listeprocessus *tml,*tml_attente;
        processus *tmp,*tmpl;
        int t=0 ,k,q,i;
     
        tml=creer_liste();
        tml_attente=creer_liste();
        trie_par_date(l);
        while(t>=0){
            check_arrival_time(l,tml,t);
     
            if(tml->nbrprocessus!=0){
                while(tml->nbrprocessus!=0){
                        tmp=tml->premier;
                    for(i=0;i<quantum;i++){
     
                        executer_processus(tmp->Id,tml);
                        t++;
     
                        check_arrival_time(l,tml,t);
                        if(tmp->Duree==0) break;
     
     
                    }
                    supprimer_processus(tmp->Id,tml);
                    if(tmp->Duree!=0) ajouter_processus(tmp->Id,tmp->Duree,tmp->Date_arrive,tmp->Nom,tml_attente);
     
     
     
                }
            }
            else{
                k=tml_attente->nbrprocessus;
                q=0;
                while(tml_attente->nbrprocessus!=0){
                    tmpl=tml_attente->premier;
                    for(i=0;i<quantum;i++){
     
                            executer_processus(tmpl->Id,tml_attente);
                            t++;
                            check_arrival_time(l,tml,t);
                            if(tmpl->Duree==0) break;
                    }
     
     
                    q++;
                    supprimer_processus(tmpl->Id,tml_attente);
     
                    if(tmpl->Duree!=0) ajouter_processus(tmpl->Id,tmpl->Duree,tmpl->Date_arrive,tmpl->Nom,tml_attente);
                    if(k==q) break;
     
     
                }
            }
            if(tml->nbrprocessus==0 && tml_attente->nbrprocessus == 0 && l->nbrprocessus==0) break;
     
        }
     
    }

