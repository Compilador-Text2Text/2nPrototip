#include <stdio.h>
#include "../executor.h"

char **localitzat = NULL, **tipus = NULL;

char ** inicialitzar_vector_strings (int i)
{
	char **o;

	o = malloc (i * sizeof (char *));

	while (--i)
		o[i] = NULL;

	return o;
}

void
inicialitzar_localitzacions ()
{
	localitzat = inicialitzar_vector_strings (EndLocalitzacions);

	localitzat[Codi]	= "codi";

	localitzat[Arguments]	= "v. arguments";
	localitzat[Locals]	= "v. locals";
	localitzat[Globals]	= "v. globals";

	localitzat[Funcions]	= "f. funcions";
	localitzat[Sistema]	= "f. sistema";
	localitzat[Retorn]	= "f. retorn";

	localitzat[NoRetorn]	= "e. no hi ha retorn";
}

void
inicialitzar_tipus ()
{
	tipus = inicialitzar_vector_strings (EndTipus);

	tipus[Void]	= "void";
	tipus[Char]	= "char";
	tipus[Int]	= "int";
	tipus[Pointer]	= "punter";
}

void
mostra_localitzacions ()
{
	int i;

	for (i = 0; i < EndLocalitzacions; i++)
		if (localitzat[i])
			printf ("-%2d '%s'\n", i, localitzat[i]);
}

void
mostra_tipus ()
{
	int i;

	for (i = 0; i < EndTipus; i++)
		if (tipus[i])
			printf ("-%2d '%s'\n", i, tipus[i]);
}

void
inicialitzar_depurador ()
{
	inicialitzar_localitzacions ();
	inicialitzar_tipus ();
}

void
finalitzar_depurador ()
{
	free (localitzat);
	free (tipus);
}
