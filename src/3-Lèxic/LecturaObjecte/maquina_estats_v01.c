#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
error_procedencia (char*general, int lloc, char*concret)
{
	char c = '\0';
	printf ("Error detectat a la funció: %d\n%s\n%s\n", lloc, general, concret);
	printf ("Error a la línia:%d:%ld: \n", g_f, g_e_s.us);
	pila_afegir ( &g_e_s, &c );
	printf ("Llegit:\n\"%s\"\n", (char*)g_e_s.punter);
	exit (EXIT_FAILURE);
}

void
error_final_1 (char *general, int lloc, char *concret)
{
	if ((g_f == 1) && (g_e_s.us == 1))
	{
		printf ("El fitxer està buit o és una carpeta.");
	}
	printf ("ERROR, necessitat de llegir quan ha acabat el document.\n");
	error_procedencia (general, lloc, concret);
}

// [^\n'c']*'c'
void
llegir_fins_1 (char c, char* general, int quina_funcio, char *concret)
{
	char i;
	while ((i = llegir_caracter_1 ()) != EOF)
		if ( i == c )
			return;
		else if ( i == '\n' )
			break;

	if ( i == EOF )
		error_final_1 (general, quina_funcio, concret);
	printf ("ERROR:\nEsperem un '%c', però no ha arribat.\n", c);
	error_procedencia (general, quina_funcio, concret);
}

// (Comentaris)
char
llegir_linia_1 (char *general, char *concret, int lloc)
{
	char c;

	while ((c = llegir_caracter_1 ()) != EOF)
	{
		switch (c)
		{
			case '#': // Comentaris.
				llegir_fins_1 ('\n', general, lloc, concret);
			case ' ':
			case '\t':
			case '\n':
				break;
			default:
				return c;
		}
	}

	error_final_1 (general, lloc, concret);
	return c; // No arribarà mai, és pel compilador.
}

// 'esperat'
void
comprovacio_caracter_amb_2 (char esperat, char entrat, char *general, int lloc, char*concret)
{
	if (esperat == entrat) return;
	printf ("ERROR:\nEsperat: '%c', entrat: '%c'.\n", esperat, entrat);
	error_procedencia (general, lloc, concret);
}

// (comentaris)'esperat'
void
comprovacio_caracter_1 (char esperat, char *general, int lloc, char*concret)
{
	char c = llegir_linia_1 (general, concret, lloc);
	comprovacio_caracter_amb_2 (esperat, c, general, lloc, concret);
}

// (comentari)'p'(comentari)'s'[^\n'f']'f'
void
llegir_inici_final_1 (char p, char s, char f, char *general, int lloc, char*concret)
{
	comprovacio_caracter_1 (p, general, lloc, concret);
	comprovacio_caracter_1 (s, general, lloc, concret);
	llegir_fins_1 (f, general, lloc, concret);
}

// \d*\n
int
llegir_digit_final_1 (char f, char *general, int lloc, char *concret)
{
	int o = 0;
	char c;

	while (isdigit((c = llegir_caracter_1 ()))) o = c - '0' + o*10;
	comprovacio_caracter_amb_2 (f, c, general, lloc, concret);

	return o;
}

// (comentari)"[^\n ]*
// Guarda el resultat en s.
char
llegir_text_sense_espais_ni_intro (struct pila *p, char **s, char*general, int lloc, char*concret)
{
	char c, e = '\0';

	comprovacio_caracter_1 ('"', general, lloc, concret);

	p->us = 0; // Inicialitzem la pila.
	while (((c = llegir_caracter_1 ()) != ' ') && (c != '\n'))
		if ( c == EOF )
			error_final_1 (general, lloc, concret);
		else
			pila_afegir (p, &c);

	pila_afegir (p, &e);

	*s = strdup (p->punter);

	return c;
}
