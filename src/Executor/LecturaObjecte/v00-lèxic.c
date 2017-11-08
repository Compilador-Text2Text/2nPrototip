#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../executor.h"
#include "maquina_estats.h"

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

char
definir_variables (struct variables *vs)
{
	int d;
	char c;
	struct variable *v;

	vs->mida = llegir_digit_final ( '\n' );
	vs->punter = malloc ( vs->mida * sizeof (struct variable) );

	// Inicialitzar els valors.
	while ( isdigit ( (c = llegir_linia ()) ) )
	{
		v = vs->punter + llegir_digit_final_comenzat (c, ' ');

		switch ( (d = llegir_digit_final ( ' ' )) )
		{
		case Char:
			v->valor.caracter = llegir_linia ();
			comprovacio_caracter (llegir_linia (), '-');
			break;

		case Int:
			v->valor.enter = llegir_digit_final ( '\n' );
			break;

		default:
			printf ("Esperavem que fos un: Char o un Int.\n");
			printf ("Int: %d\nChar: %d\nEntrat: %d\n", Int, Char, d);
			error ("Valor inesperat.");
		break;
		}
	}

	return c;
}

char
inicialitzar_paraules (struct frase *pf)
{
	int d, i;
	char c;
	struct paraula *pp;

	c = llegir_linia ();
	i = 0;
	while ( isdigit (c) )
	{
		pp = pf->punter + i++;
		c = llegir_linia ();
	}

	if (i != pf->mida)
	{
		printf ("Reservat: %zu\nOcupat: %d\n", pf->mida, i);
		error ("No escrites totes les paraules.");
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
	while ( c == '-' )
	{
		llegir_inici_final ( 'f', ':' );
		d = llegir_digit_final ( '\n' );
		pf = pdf->codi.punter + i++;
		pf->mida = d;
		pf->punter = malloc ( d * sizeof (struct paraula) );
		printf ("Llegit valor: %d nombre de paraules.\n", d);

		c = inicialitzar_paraules (pf);
	}

	if (i != pdf->codi.mida)
	{
		printf ("Reservat: %zu\nOcupat: %d\n", pdf->codi.mida, i);
		error ("No escrites totes les frases.");
	}

	return c;
}

void
llegir (char (*funcio) (void))
{
	int d;
	char c;
	struct descriptor_funcio *pdf; // Inicialitzar les funcions.

	descriu_lectura (funcio);

	/****** Variables Globals ******/
	comprovacio_caracter (llegir_linia (), '-');
	llegir_inici_final ('v', ':');
	c = definir_variables (&variables_globals);

	/****** Funcions ******/
	comprovacio_caracter (c, '-');
	llegir_inici_final ('f', ':');
	d = llegir_digit_final ( '\n' );
	descriptors_funcio.mida = d;
	descriptors_funcio.punter = malloc ( d * sizeof (struct descriptor_funcio) );

	// Inicialitzar les funcions.
	c = llegir_linia ();
	while ( c == '<' )
	{
		llegir_inici_final ('F', ':' );
		pdf = descriptors_funcio.punter + llegir_digit_final ( '\n' );

		/****** Arguments ******/
		comprovacio_caracter (llegir_linia (), '-');
		llegir_inici_final ( 'a', ':' );
		c = definir_variables ( &pdf->arguments );

		/****** Locals ******/
		comprovacio_caracter (c, '-');
		llegir_inici_final ( 'v', ':' );
		c = definir_variables ( &pdf->local );

		/****** Codi ******/
		comprovacio_caracter (c, '-');
		llegir_inici_final ( 'c', ':' );
		d = llegir_digit_final ( '\n' );
		pdf->codi.mida = d;
		pdf->codi.punter = malloc ( d * sizeof (struct frase) );
		printf ("Llegit valor: %d nombre de frases.\n", d);

		c = inicialitzar_frases (pdf);
	}
}
