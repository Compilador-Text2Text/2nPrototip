#include <stdio.h>
#include <stdlib.h>

#include "../2-Funció-de-sistema/inicialitzador.h"
#include "../3-Lèxic/LecturaObjecte/v01-lèxic.h"
#include "../6-Depurador/depurador.h"
#include "../9-Util/pila.h"

FILE *g_pf;		// punter de fitxer, variable global.
int g_f;		// global fila.
struct pila g_e_s;	// Pila global de string pels errors.

FILE *
inicialitza_lecura_fitxer_1 (char *nom)
{
	FILE *pf = fopen (nom, "r");

	if (!pf)
	{
		printf ("El fitxer: %s\nNo existex o no tenim permisos d'accés.\n", nom);
		exit (EXIT_FAILURE);
	}
	g_f = 1;
	g_e_s = pila_inicialitzar (100, sizeof (char));

	return pf;
}

char
lectura_fitxer_1 ()
{
	char c;

	pila_afegir (&g_e_s, &c);

	if ((c = getc (g_pf)) == '\n')
	{
		g_f++;
		g_e_s.us = 0;
	}

	return c;
}

int inicialitzador_lectura_objecte_1 (char *nom, int argc, char**argv)
{
	inicialitza_funcions_sistema ();
	inicialitzar_depurador ();

	return 0;
}
