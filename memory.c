#include <math.h>
#include <string.h>
#include <stdio.h>
#include "memory.h"

void afficherListe(liste *l)
{
	element *actuel = *l;

	while(actuel != NULL)
	{
		printf("%d\n", actuel->valeur);
		actuel = actuel->suivant;
	}	
	return;
}

element* elementLibre() {
	/*Allocation de mémoire*/
	element* e = (element*) malloc(sizeof(element));	

	/*DEBUG DE MEMOIRE MALLOC/FREE*/
	#ifdef DEBUG_MEM
		mcheck(&no_op);
	#endif
	

	/*Initialisation*/
	(*e).valeur = NULL;
	(*e).suivant = NULL;
	return e;
}

void insererElement(int *x, int Adresse, liste *l)
{
    int i;
    element *select, *suiv, *libre;

	select = NULL;
	suiv = *l;
	
	/*Détermination de la position de l'insertion*/
	while ( (suiv != NULL) && ((*suiv).adresse != Adresse) ){
		select = suiv;
		suiv = (*select).suivant;
        
	}
	
	/*Insertion*/
    if(suiv == NULL)
    {
        libre = elementLibre();
	    if (select == NULL) {
	    	(*l) = libre;
	    }else{
	    	(*select).suivant = libre;
	    }
        (*libre).adresse = Adresse;
        for(i=0;i<7;i++)
        {
            (*libre).valeur[i] = x[i];
        }
	    (*libre).suivant = suiv;
    }
	else
    {
        for(i=0;i<7;i++)
        {
            (*suiv).valeur[i] = x[i];
        }
    }
}
