#include <stdio.h>
#include <stdlib.h>

char (*llegir_caracter) (void);

void descriu_lectura (char (*funcio) (void))
{
	llegir_caracter = funcio;
}

void error_final (char *s)
{
	printf ("ERROR, final intentant llegir.\n");
	printf ("Error detectat: '%s'\n", s);
	exit (EXIT_FAILURE);
}

void llegir_fins (char c)
{
	char i;
	while ((i = llegir_caracter ()) != EOF)
		if ( i == c )
			return;

	error_final ("llegir fins");
}

char llegir_linia (void)
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
}

void llegir_inici_final (char i, char f)
{
	char c;
	c = llegir_caracter ();
	printf ("Llegit: '%c'\n");
}
