#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../../1-Executor/descriptor.h"
#include "maquina_estats.h"

struct pila g_v_s; // Pila global de string.

// Funcions a modificar si vols tenir en compte:
// - tipus
// - Valors nous

struct descriptor llegir_tipus_valor (union valor* v);
char inicialitzar_paraules (struct frase *pf);

// TODO Hauria de llegir quantes vegades punter és.
struct descriptor
llegir_tipus_valor (union valor* v)
{
	int d;
	struct descriptor r = {.tipus = CapTipus, .vegades_punter = 0};

	switch ((d = llegir_digit_final ( ' ' )))
	{
	case Char:
		comprovacio_caracter (llegir_linia (), '\'');
		v->caracter = llegir_linia ();
		comprovacio_caracter (llegir_linia (), '\'');
		r.tipus = Char;
		break;

	case Int:
		v->enter = llegir_digit_final ( '\n' );
		r.tipus = Int;
		break;

	case Pointer:
		r.tipus = Pointer;
		break;

	default:
		// TODO, missatge d'error mal fet.
		printf ("Esperavem que fos un: Char o un Int.\n");
		printf ("Int: %d\nChar: %d\nEntrat: %d\n", Int, Char, d);
		error ("Valor inesperat.");
	}
	return r;
}

void
definir_variables (struct variables *vs)
{
	int mida, i;
	char c;
	struct variable *v;

	vs->mida = mida = llegir_digit_final ( '\n' );
	vs->punter = mida ? malloc ( mida * sizeof (struct variable) ) : NULL;

	// Inicialitzar els valors.
	for (i = 0; i < mida; i++)
	{
		v = vs->punter + i;
		c = llegir_text_sense_espais_ni_enters (&g_v_s, &v->nom);

		if ( c == '\n' ) continue;
		v->descriptor = llegir_tipus_valor (&v->valor);
	}
}

char
inicialitzar_paraules (struct frase *pf)
{
	int d, i;
	char c;
	struct paraula *pp;

	i = 0;
	while ( isdigit ((c = llegir_linia ())) && (i < pf->mida) )
	{
		pp = pf->punter + i++;

		// Que fer.
		d = llegir_digit_final_comenzat (c, ' ');
		pp->lloc.on = d;
		switch (d)
		{
		case Codi: // Tipus valor
			pp->lloc.relatiu = 0;
			pp->descriptor = llegir_tipus_valor (&pp->auxiliar);
			break;

		case Arguments:
		case Locals:
		case Globals:
			pp->lloc.relatiu = llegir_digit_final ( '\n' );
			break;

		case Funcions:
		case Sistema:
			pp->lloc.relatiu = llegir_digit_final ( ' ' );
			pp->auxiliar.enter = llegir_digit_final ( '\n' );
			break;

		case Retorn:
			pp->auxiliar.enter = llegir_digit_final ( '\n' );
			break;

		default:
			printf ("Valor màxim esperat: %u, valor entrat: %d", EndLocalitzacions, d);
			error ("Instrucció inesperada. Usi '-hf' per tenir ajuda.");
			break;
		}
	}

	if ( isdigit (c) || (i != pf->mida))
	{
		printf ("Reservat: %zu\nOcupat: %d\n", pf->mida, i);
		error ("No escrites totes les paraules o volen escriure on no queda memòria.");
	}

	return c;
}
char
inicialitzar_frases (struct descriptor_funcio *pdf)
{
	int d, i;
	char c;
	struct frase *pf;

	c = llegir_linia ();
	i = 0;
	while ( (c == '-') && (i < pdf->codi.mida) )
	{
		llegir_inici_final ( 'f', ':' );
		d = llegir_digit_final ( '\n' );
		pf = pdf->codi.punter + i++;
		pf->mida = d;
		pf->punter = malloc ( d * sizeof (struct paraula) );
		printf ("Llegit valor: %d nombre de paraules.\n", d);

		c = inicialitzar_paraules (pf);
	}

	if ( (c == '-') || (i != pdf->codi.mida) )
	{
		printf ("Reservat: %zu\nOcupat: %d\n", pdf->codi.mida, i);
		error ("No escrites totes les frases o volen escriure on no queda memòria.");
	}

	return c;
}

void
llegir_codi_objecte (char (*funcio) (void))
{
	int d;
	char c;
	struct descriptor_funcio *pdf; // Inicialitzar les funcions.

	descriu_lectura (funcio);
	g_v_s = pila_inicialitzar (100, sizeof (char));

	/****** Variables Globals ******/
	comprovacio_caracter (llegir_linia (), '-');
	llegir_inici_final ('v', ':');
	definir_variables (&variables_globals);

	/****** Funcions ******/
	comprovacio_caracter (llegir_linia (), '-');
	llegir_inici_final ('f', ':');
	d = llegir_digit_final ( '\n' );
	descriptors_funcio.mida = d;
	descriptors_funcio.punter = malloc ( d * sizeof (struct descriptor_funcio) );

	// Inicialitzar les funcions.
	c = llegir_linia ();
	while ( c == '<' )
	{
		llegir_inici_final ('F', ':' );
		// TODO Hauria de llegir el tipus de la funció.
		pdf = descriptors_funcio.punter + llegir_digit_final ( '\n' );

		// Nom i mida de la memoria d'execució
		c = llegir_text_sense_espais_ni_enters (&g_v_s, &pdf->nom);
		comprovacio_caracter (c , ' ');
		pdf->mida_memoria_execucio = llegir_digit_final ('\n');

		/****** Arguments ******/
		comprovacio_caracter (llegir_linia (), '-');
		llegir_inici_final ( 'a', ':' );
		definir_variables ( &pdf->arguments );

		/****** Locals ******/
		comprovacio_caracter (llegir_linia (), '-');
		llegir_inici_final ( 'v', ':' );
		definir_variables ( &pdf->local );

		/****** Codi ******/
		comprovacio_caracter (llegir_linia (), '-');
		llegir_inici_final ( 'c', ':' );
		d = llegir_digit_final ( '\n' );
		pdf->codi.mida = d;
		pdf->codi.punter = malloc ( d * sizeof (struct frase) );
		printf ("Llegit valor: %d nombre de frases.\n", d);

		c = inicialitzar_frases (pdf);
	}
	pila_alliberar (&g_v_s);
}
