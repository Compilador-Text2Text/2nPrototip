#include <ctype.h>
#include <math.h>
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
		// Ja que pot ésser c = '\n'.
		else if ( i == '\n' )
			break;

	if ( i == EOF )
		error_final_1 (general, quina_funcio, concret);
	printf ("ERROR:\nEsperem un '%c', però no ha arribat.\n", c);
	error_procedencia (general, quina_funcio, concret);
}

// (Comentaris) ≡ (#[^\n]*\n|[ \n\t])*
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

int
llegir_digit_comenzat_1 (int o, char *e, char *general, int lloc, char *concret)
{
	char c;

	while (isdigit((c = llegir_caracter_1 ()))) o = c - '0' + o*10;

	*e = c;

	return o;
}

int
llegir_digit_final_comenzat_1 (int o, char f, char *general, int lloc, char *concret)
{
	char c;
	o = llegir_digit_comenzat_1 (o, &c, general, lloc, concret);
	comprovacio_caracter_amb_2 (f, c, general, lloc, concret);

	return o;
}

int
llegir_digit (char *e, char *general, int lloc, char *concret)
{
	return llegir_digit_comenzat_1 (0, e, general, lloc, concret);
}


int
llegir_digit_comentaris (char *e, char *general, int lloc, char *concret)
{
	int o = 0;
	char c;

	if (isdigit((c = llegir_linia_1 (general, concret, lloc))))
		return llegir_digit_comenzat_1 (c-'0', e, general, lloc, concret);

	*e = c;

	return o;
}


// \d*'f'
int
llegir_digit_final_1 (char f, char *general, int lloc, char *concret)
{
	return llegir_digit_final_comenzat_1 (0, f, general, lloc, concret);
}

int
llegir_digit_final_comentari (char f, char *general, int lloc, char *concret)
{
	char c;
	int o;

	o = llegir_digit_comentaris (&c, general, lloc, concret);
	comprovacio_caracter_amb_2 (f, c, general, lloc, concret);

	return o;
}

void
vigilar_limit (int entrada, int maxim, char *general, int lloc, char *concret)
{
	if ( entrada < maxim ) return;

	printf ("Màxim i entrat: %d >(hauria) %d\n", maxim, entrada);
	printf ("Per ajuda usi -hf\n");
	error_procedencia (general, lloc, concret);
}

int
llegir_digit_final_limitat_1 ( char f, int maxim, char*general, int lloc, char*concret )
{
	int d = llegir_digit_final_1 (f, general, lloc, concret);
	vigilar_limit ( d, maxim, general, lloc, concret);
	return d;
}

int
llegir_digit_final_limitat_comentari ( char f, int maxim, char *general, int lloc, char *concret )
{
	int o;

	o = llegir_digit_final_comentari ( f, general, lloc, concret );
	vigilar_limit ( o, maxim, general, lloc, concret);

	return o;
}

int
llegir_digit_pos_neg (char *p, char *general, int lloc, char *concret)
{
	int o, negatiu = 0;
	char c = llegir_caracter_1 ();

	if ( c == '-' )
	{
		negatiu = 1;
		c = llegir_caracter_1 ();
	}

	if ( isdigit (c) )
		o = llegir_digit_comenzat_1 (c-'0', p, general, lloc, concret);
	else
		error_procedencia (general, lloc, concret);

	if (negatiu) o = -o;

	return o;
}

float
llegir_digit_float (char *c, char *general, int lloc, char *concret)
{
	float r, s = 0;
	int i;

	r = llegir_digit_pos_neg (c, general, lloc, concret);
	if ( *c == '.' )
	{
		// M'he dit que era més fàcil dividint que fent logaritmes.
		i = g_e_s.us +1;
		s = llegir_digit (c, general, lloc, concret);
		s /= pow (10., g_e_s.us -i);
		r += s;
	}

	return r;
}

// (comentari)"[^\n ]*
// Guarda el resultat en s, pensat pels noms, ja que no volem espais ni enters.
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

// "(\"|[^"])*" approx, perquè "\\" No funciona.
char *
llegir_text (struct pila *p, char*general, int lloc, char*concret)
{
	char c, e = '\0';
	int estat = 0;

	comprovacio_caracter_1 ('"', general, lloc, concret);
	p->us = 0; // Inicialitzem la pila.

	while ((c = llegir_caracter_1 ()) != EOF)
		if ( estat )
		{
			estat = 0;
			pila_afegir (p, &c);
		} else if ( c == '"' )
		{
			pila_afegir (p, &e);
			return strdup (p->punter);
		} else if ( c == '\\' )
			estat = 1;
		else
			pila_afegir (p, &c);

	error_final_1 (general, lloc, concret);
	return p->punter; // Evitar warnigs del compilador. Mai pot arribar aquí.
}

// '.'
char
llegir_caracter_facil (char *general, int lloc, char *concret)
{
	char c;

	comprovacio_caracter_1 ('\'', general, lloc, concret);
	c = llegir_caracter_1 ();
	comprovacio_caracter_1 ('\'', general, lloc, concret);

	return c;
}
