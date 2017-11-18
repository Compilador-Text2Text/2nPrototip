#include <stdio.h>
#include <string.h>

#include "0-Inicialitzador/v00.h"

int main (int argc, char *argv[])
{
	int out, i;
	char *nom;

	for (i = 1; i < argc; i++)
	{
		if ( !strcmp ("-f", argv[i]) )
			nom = argv[++i];
		else
		{
			printf ("ERROR:\n");
			printf ("L'entrada no és vàlida 'comandes'.\n");
			printf ("Per més ajuda premi 'h'.\n");
			return 1;
		}
	}

	out = inicialitzador_lectura_objecte (nom);
	finalitza_allibera_memoria ();
	return out;
}
