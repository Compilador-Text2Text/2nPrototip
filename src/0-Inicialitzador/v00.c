#include <stdio.h>
#include <stdlib.h>

#include "alliberar_memòria.h"
#include "../2-Funció-de-sistema/inicialitzador.h"
#include "../3-Lèxic/LecturaObjecte/v00-lèxic.h"
#include "../6-Depurador/depurador.h"

FILE *g_pf; // punter de fitxer, variable global.

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
	return getc (g_pf);
}

int
inicialitzador_lectura_objecte (char *nom)
{
	inicialitza_funcions_sistema ();
	inicialitzar_depurador ();

	g_pf = inicialitza_lecura_fitxer (nom);
		llegir_codi_objecte (lectura_fitxer);
	fclose (g_pf);

	return 0;
}

void
inicialitzador_informacio (void)
{
	inicialitza_funcions_sistema ();
	inicialitzar_depurador ();

	printf ("Mostra les localitzacions que hi ha.\n");
	mostra_localitzacions ();
	printf ("\nMostra els tipus que hi ha.\n");
	mostra_tipus ();
	printf ("\nMostra les funcions a sistema que hi ha.\n");
	mostra_sistema ();

	finalitza_funcions_sistema ();
	finalitzar_depurador ();
}

void
finalitza_allibera_memoria (void)
{
	finalitza_funcions_sistema ();
	finalitzar_depurador ();

	alliberar_descriptors_funcions ();
}
