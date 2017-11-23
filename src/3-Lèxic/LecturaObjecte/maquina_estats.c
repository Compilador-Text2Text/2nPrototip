#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "maquina_estats.h"

char (*llegir_caracter) (void);

void descriu_lectura (char (*funcio) (void))
{
	llegir_caracter = funcio;
}

void error_final (char *s)
{
	printf ("ERROR, intentant llegir.\n");
	printf ("Error detectat: \n%s\n", s);
	exit (EXIT_FAILURE);
}

void
error (char *s)
{
	printf ("Error detectat.\n%s\n", s);
	exit (EXIT_FAILURE);
}

void
comprovacio_caracter (char c, char f)
{
	if (c != f)
	{
		printf ("S'esperava un '%c' i ha entrat: '%c'\n", f, c);
		error ("No ha trobat el caràcter.");
	}
}

void llegir_fins (char c)
{
	char i;
	while ((i = llegir_caracter ()) != EOF)
		if ( i == c )
			return;

	error_final ("llegir fins.");
}

char
llegir_linia (void)
{
	char c;

	while ((c = llegir_caracter ()) != EOF)
	{
		switch (c)
		{
			case '#': // Comentaris.
				llegir_fins ('\n');
				break;
			case ' ':
			case '\t':
			case '\n':
				break;
			default:
				return c;
		}
	}

	error_final ("llegir línia");
	exit (EXIT_FAILURE);
}

char
llegir_text_sense_espais_ni_enters (struct pila *v, char **ps)
{
	char c, e = '\0';

	if ((c = llegir_linia ()) != '"')
	{
		printf ("Esperava un '\"' i ha llegit: '%c'\n", c);
		exit (EXIT_FAILURE);
	}

	v->us = 0; // Inicialitzem el vector.
	while (((c = llegir_caracter ()) != ' ') && (c != '\n'))
		if ( c == EOF )
			error_final ("Voliem llegir una paraula, però s'ha acabat el fitxer.");
		else
			pila_afegir (v, &c);

	// Afegim el final, per a poder copiar correctament el codi.
	pila_afegir (v, &e);

	*ps = strdup (v->punter);

	return c;
}

int
llegir_inici_final (char i, char f)
{
	char c;
	if ((c = llegir_caracter ()) != i)
	{
		printf ("S'eperava una '%c' i ha entrat '%c'.\n", i, c);
		error_final ("inici final.");
	}

	while ((c = llegir_caracter ()) != f)
		if (c == EOF)
		{
			printf ("Al buscar: '%c', no ha sigut trobat.\n", f);
			error_final ("No trobat el caracter final.");
		}
	return 1;
}

int
llegir_digit_final ( char f )
{
	int o = 0;
	char c;

	while (isdigit((c = llegir_caracter ())))
		o = c - '0' + o*10;

	if (c != f)
	{
		printf ("Després de llegir el dígit, s'esperava: '%c'.\n", f);
		printf ("On ha entrat: '%c'\n", c);
		error_final ("Dígit amb final concret.");
	}

	return o;
}

int
llegir_digit_final_comenzat (char c, char f)
{
	int o = c - '0';

	while (isdigit((c = llegir_caracter ())))
		o = c - '0' + o*10;

	if (c != f)
	{
		printf ("Després de llegir el dígit, s'esperava: '%c'.\n", f);
		printf ("On ha entrat: '%c'\n", c);
		error_final ("Dígit amb final concret.");
	}

	return o;
}

// Versió 01
void comprovacio_caracter_1 (char esperat, char *missatge_error_general, int quina_funcio, char*missatge_concret)
{
	char c;

	if ((c = llegir_linia ()) == esperat) return;
	printf ("De on venim:\n%s\n", missatge_error_general);
}
void llegir_inici_final_1 (char inici, char final, char *missatge_error_general, int quina_funcio, char*missatge_concret)
{
}
