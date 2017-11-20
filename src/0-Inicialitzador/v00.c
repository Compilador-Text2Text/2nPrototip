#include <stdio.h>
#include <stdlib.h>

#include "alliberar_memòria.h"
#include "../1-Executor/instruccions.h"
#include "../1-Executor/punter-funció.h"
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
inicialitzador_lectura_objecte (char *nom, int argc, char **argv)
{
	struct element_execucio *e;
	struct pila p;
	struct punter_funcio f;
	int out;

	inicialitza_funcions_sistema ();
	inicialitzar_depurador ();

	// Lectura dle fitxer
	g_pf = inicialitza_lecura_fitxer (nom);
		llegir_codi_objecte (lectura_fitxer);
	fclose (g_pf);

	// Memòria per l'execució.
	e = malloc ( 2 * sizeof (struct element_execucio) );
	e[0].valor.enter = argc;
	e[1].valor.punter = argv;
	p = pila_inicialitzar ( 100, sizeof (struct funcio_dinamica) );
	crear_nova_funcio_dinamica (2, e, 0, &p);

	// Crida perquè executi el codi.
	f.funcio = funcio_executa_paraula;
	funcio_ciclica ( &f, &p );

	out = e->valor.enter;
	free (e);
	pila_alliberar (&p);
	return out;
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
