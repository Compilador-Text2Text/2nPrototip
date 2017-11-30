#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "../2-Funció-de-sistema/inicialitzador.h"
#include "../3-Lèxic/LecturaObjecte/v01-lèxic.h"
#include "../6-Depurador/depurador.h"
#include "../9-Util/pila.h"
#include "../4-Sintàctic/shunting-yard_algorithm.h"

FILE *g_pf;		// punter de fitxer, variable global.
int g_f;		// global fila.
struct pila g_e_s;	// Pila global de string pels errors.
int bool_lectura;	// Saber quan reiniciar g_e_s.

FILE *
inicialitza_lecura_fitxer_1 (char *nom)
{
	FILE *pf;
	struct stat s;

	if ( stat (nom, &s) )
	{
		printf ("El fitxer: %s\nNo existeix o no tenim permisos d'accés.\n", nom);
		exit (EXIT_FAILURE);
	}
	if (!S_ISREG (s.st_mode))
	{
		printf ("No és un fitxer: %s\nNomés podem interpretar fitxers.\n", nom);
		exit (EXIT_FAILURE);
	}

	// Inicialitzem les 4 variables globals.
	pf = fopen (nom, "r");
	g_f = 1;
	bool_lectura = 0;
	g_e_s = pila_inicialitzar (100, sizeof (char));

	return pf;
}

char
lectura_fitxer_1 (void)
{
	char c = getc (g_pf);

	if ( c == '\n' )
		bool_lectura = 1;
	else if ( bool_lectura )
	{
		bool_lectura = 0;
		g_f++;
		g_e_s.us = 0;
	}
	if ( c == EOF ) return c;

	pila_afegir (&g_e_s, &c);

	return c;
}

char
lectura_fitxer_verbos (void)
{
	char c = getc (g_pf);

	if ( c == '\n' )
		bool_lectura = 1;
	else if ( bool_lectura )
	{
		bool_lectura = 0;
		g_f++;
		g_e_s.us = 0;
	}
	if ( c == EOF ) return c;

printf ("%c", c); // verbos
	pila_afegir (&g_e_s, &c);

	return c;
}

int
inicialitzador_lectura_objecte_1 (char *nom, int argc, char**argv, int verbos)
{
	inicialitza_funcions_sistema ();
	inicialitzar_depurador ();

	g_pf = inicialitza_lecura_fitxer_1 (nom);
	if (verbos)
		llegir_codi_objecte_v01 (lectura_fitxer_verbos, l_v01_normal);
	else
		llegir_codi_objecte_v01 (lectura_fitxer_1, l_v01_normal);
	fclose (g_pf);

	pila_alliberar (&g_e_s);

	shunting_yard_algorithm ();

	return 0;
}
