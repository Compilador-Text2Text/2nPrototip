#include <ctype.h>
#include <stdio.h>

#include "depurador.h"

// No funciona per CTRL-D
void
treure_caracters_fins_enter (void)
{
	while (getchar () != '\n');
}

int
lectura_digit (void)
{
	char c;
	int r = 0;

	while (isdigit ((c = getchar ())))
		r = c - '0' + 10 * r;

	return r;
}

void help_h (char c)
{
	switch (c)
	{
	case 'i':
		printf ("Amb la `i' pot fer:\n");
		printf ("\n'i t'	Veurà els tipus.");
		printf ("\n'i o'	Veurà els llocs.");
		printf ("\n");
		break;
	}
}

void
premut_h (void)
{
	printf ("Llista de comandes:\n");
	printf ("\nq	Per sortir.");
	printf ("\nCTRL-D	Per sortir.");
	printf ("\n\ni	Tenir informació.");
	printf ("\n");
	treure_caracters_fins_enter ();
}

void informatiu (void)
{
	char c;

	if ((c = getchar ()) == '\n')
	{
		help_h ('i');
		return;
	}

	switch ((c = getchar ()))
	{
	case 't': // tipus
		mostra_tipus ();
		break;
	case 'o': // localitzacions
		mostra_localitzacions ();
		break;
	default:
		printf ("Instrucció desconeguda: `i %c'\n", c);
		help_h ('i');
	}
		treure_caracters_fins_enter ();
}

void
menu_visualitzacio (void)
{
	char c;

	inicialitzar_depurador ();
	printf ("No facis <instrucció>CTRL-D ;)\n");
	printf ("Fes <instrucció><enter>\n");
	printf ("Per informació fes: `h'\n");
	printf ("Per acabar, esperi el mode input [»], llavors fes CTRL-D\n");
	printf ("» ");

	while ((((c = getchar ()) != EOF) && (c != 'q')))
	{
	switch (c)
	{
	case 'h':
		premut_h ();
		break;
	case 'i':
		informatiu ();
		break;
	case '\n': break;
	default:
		printf ("Instrucció erronia: `%c'.\n", c);
		printf ("Premi `h' per tenir ajuda.\n");
		treure_caracters_fins_enter ();
	}
	printf ("» ");
	}

	printf ("\n");
	finalitzar_depurador ();
}
