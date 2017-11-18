#include <stdio.h>
#include <stdlib.h>
#include "v00-lèxic.h"
#include "../../1-Executor/executor.h"
#include "../../6-Depurador/menú.h"

struct variables variables_globals;
struct llista_descriptors descriptors_funcio;
struct llista_sistema funcions_sistema;

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

char
lectura_fitxer ()
{
	return getc (my_pf);
}

int
main (int argc, char *argv[])
{
	if (argc != 2)
	{
		printf ("Necessitem 1 argument.\n");
		printf ("- Fitxer on farem la lectura.\n");
	}
	my_pf = inicialitza_lecura_fitxer (argv[1]);
	llegir_codi_objecte (lectura_fitxer);

	menu_visualitzacio ();

	// Tanquem el document.
	fclose (my_pf);
	return 1;
}
