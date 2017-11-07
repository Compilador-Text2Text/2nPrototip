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

int main ()
{
	char c;

	my_pf = inicialitza_lecura_fitxer ("lexic.c");
	llegir (lectura_fitxer);


	// Tanquem el document.
	fclose (my_pf);
	return 1;
}
