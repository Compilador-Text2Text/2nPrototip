#include <stdio.h>
#include <stdlib.h>

#include "../../9-Util/pila.h"

char (*llegir_caracter_1) (void);
extern int g_f;		// global fila.
extern struct pila g_e_s;	// Pila global de string pels errors.

void
descriu_lectura_1 (char (*f) (void))
{
	llegir_caracter_1 = f;
}

void
error_final_1 (char *s, char *l)
{
	if ((g_f == 1) && (g_e_s.us == 1))
	{
		printf ("El fitxer està buit o és una carpeta.");
	}
	printf ("ERROR, intentant llegir.\n");
	printf ("Error detectat: \n%s\n", s);
	exit (EXIT_FAILURE);
}

void
llegir_fins_1 (char c)
{
	char i;
	while ((i = llegir_caracter_1 ()) != EOF)
		if ( i == c )
			return;

	error_final_1 ("llegir fins.", NULL);
}

char
llegir_linia_1 (char *missatge_error_general, char *missatge_concret)
{
	char c;

	while ((c = llegir_caracter_1 ()) != EOF)
	{
		switch (c)
		{
			case '#': // Comentaris.
				llegir_fins_1 ('\n');
				break;
			case ' ':
			case '\t':
			case '\n':
				break;
			default:
				return c;
		}
	}

	error_final_1 (missatge_error_general, missatge_concret);
	exit (EXIT_FAILURE);
}


void
comprovacio_caracter_1 (char esperat, char *missatge_error_general, int quina_funcio, char*missatge_concret)
{
	char c;

	if ((c = llegir_linia_1 (missatge_error_general, missatge_concret)) == esperat) return;
	printf ("De on venim:\n%s\n", missatge_error_general);
}
void
llegir_inici_final_1 (char inici, char final, char *missatge_error_general, int quina_funcio, char*missatge_concret)
{
}
