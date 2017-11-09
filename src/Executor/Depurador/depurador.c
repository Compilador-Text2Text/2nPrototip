#include <stdio.h>
#include "../executor.h"

#define LOCALITZACIONS	8
#define TIPUS		4

struct
relacionant
{
	size_t id;
	char *nom;
} *localitzat = NULL, *tipus = NULL;


void
inicialitzar_localitzacions ()
{
	localitzat = malloc (LOCALITZACIONS * sizeof (struct relacionant));

	localitzat[0].id = Codi; localitzat[0].nom="codi";

	localitzat[1].id = Arguments; localitzat[1].nom="v arguments";
	localitzat[2].id = Locals; localitzat[2].nom="v locals";
	localitzat[3].id = Globals; localitzat[3].nom="v globals";

	localitzat[4].id = Funcions; localitzat[4].nom="f funcions";
	localitzat[5].id = Sistema; localitzat[5].nom="f sistema";
	localitzat[6].id = Retorn; localitzat[6].nom="f retorn";

	localitzat[7].id = NoRetorn; localitzat[7].nom="e no hi ha retorn";
}

void
inicialitzar_tipus ()
{
	tipus = malloc (TIPUS * sizeof (struct relacionant));

	tipus[0].id = Void; tipus[0].nom="void";
	tipus[1].id = Char; tipus[1].nom="char";
	tipus[2].id = Int; tipus[2].nom="int";
	tipus[3].id = Pointer; tipus[3].nom="punter";
}

void
mostra_localitzacions ()
{
	int i;

	for (i = 0; i < LOCALITZACIONS; i++)
		printf ("-%2zu '%s'\n", localitzat[i].id, localitzat[i].nom);
}

void
mostra_tipus ()
{
	int i;

	for (i = 0; i < TIPUS; i++)
		printf ("-%2zu '%s'\n", tipus[i].id, tipus[i].nom);
}

void
inicialitzar_depurador ()
{
	inicialitzar_localitzacions ();
	inicialitzar_tipus ();
}

void
finalitzar_depurador ()
{
	free (localitzat);
	free (tipus);
}
