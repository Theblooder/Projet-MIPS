#ifndef __MEMORY__H_
#define __MEMORY__H_


/* Prototypes */
typedef struct element element;

struct element {
    int adresse;
	int valeur[8];/* valeur de l’élément */
	element *suivant;/* adresse du successeur */
};
typedef element* liste;

void afficherListe(liste *l);
void insererElement(int x,int Adresse, liste *l);



#endif