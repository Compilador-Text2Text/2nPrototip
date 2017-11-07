#include <stdio.h>
#include <stdlib.h>
#include "v00-lèxic.h"

FILE *my_pf;

FILE *
inicialitza_lecura_fitxer (char *nom)
{
	FILE *pf = fopen (nom, "r");

	if (!pf)
	{
		printf ("El fitxer: %s\nNo existex o no tenim permisos d'accés.\n", nom);
		exit (EXIT_FAILURE);
	}

	return pf;
}

char lectura_fitxer ()
{
	return getc (my_pf);
}

int main (int argc, char *argv[])
{
	if (argc != 2)
	{
		printf ("Necessitem 1 argument.\n");
		printf ("- Fitxer on farem la lectura.\n");
	}
	my_pf = inicialitza_lecura_fitxer (argv[1]);
	llegir (lectura_fitxer);


	// Tanquem el document.
	fclose (my_pf);
	return 1;
}
