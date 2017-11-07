#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

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

void llegir_fins (char c)
{
	char i;
	while ((i = llegir_caracter ()) != EOF)
		if ( i == c )
			return;

	error_final ("llegir fins.");
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
	exit (EXIT_FAILURE);
}

int llegir_inici_final (char i, char f)
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

int llegir_digit_final ( char f )
{
	int o = 0;
	char c;

	while (isdigit((c = llegir_caracter ())))
		o = c - '0' + o*10;

	if (c != f)
	{
		printf ("Després de llegir el dígit, s'esperava: '%c'.\n", f);
		printf ("On ha entrat: '%c'", c);
		error_final ("Dígit amb final concret.");
	}

	return o;
}
