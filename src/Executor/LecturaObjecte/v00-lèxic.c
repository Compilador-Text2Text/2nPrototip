#include <stdio.h>
#include <stdlib.h>

#include "maquina_estats.h"

void error (char *s)
{
	printf ("Error detectat.\n%s\n", s);
	exit (EXIT_FAILURE);
}

void comprovacio_caracter (char c, char f)
{
	if (c != f)
	{
		printf ("S'esperava un '%c' i ha entrat: '%c'\n", f, c);
		error ("No ha trobat el caràcter.");
	}
}

void llegir (char (*funcio) (void))
{
	int d;

	descriu_lectura (funcio);

	/****** Variables Globals ******/
	comprovacio_caracter (llegir_linia (), '-');
	llegir_inici_final ('v', ':');
	d = llegir_digit_final ( '\n' );
	// TODO reservar memòria de les variables globals.
	// TODO falta indicar com modificar les variables.
	printf ("Llegit valor: %d per les variables globals.\n", d);

	/****** Funcions ******/
	comprovacio_caracter (llegir_linia (), '-');
	llegir_inici_final ('f', ':');
	d = llegir_digit_final ( '\n' );
	// TODO memoria per les funcions
	printf ("Llegit valor: %d el nombre de funcions.\n", d);

	comprovacio_caracter (llegir_linia (), '<');
	while ( llegir_inici_final ('F', ':' ) )
	{
		d = llegir_digit_final ( '\n' );
		// TODO fer que editi el valor indicat.
		printf ("Llegit valor: %d funció a modificar.\n", d);

		comprovacio_caracter (llegir_linia (), '-');
		llegir_inici_final ( 'a', ':' );
		d = llegir_digit_final ( '\n' );
		printf ("Llegit valor: %d nombre d'arguments.\n", d);
		// TODO Falta poder modificar els valors.

		comprovacio_caracter (llegir_linia (), '-');
		llegir_inici_final ( 'v', ':' );
		d = llegir_digit_final ( '\n' );
		printf ("Llegit valor: %d nombre de variables.\n", d);
		// TODO Locals

		comprovacio_caracter (llegir_linia (), '-');
		llegir_inici_final ( 'c', ':' );
		d = llegir_digit_final ( '\n' );
		printf ("Llegit valor: %d nombre de frases.\n", d);
		// TODO Codi

		comprovacio_caracter (llegir_linia (), '-');
		while ( llegir_inici_final ( 'f', ':' ) )
		{
			d = llegir_digit_final ( '\n' );
			printf ("Llegit valor: %d nombre de paraules.\n", d);
			// TODO reservar paraules

		}
	}
}
