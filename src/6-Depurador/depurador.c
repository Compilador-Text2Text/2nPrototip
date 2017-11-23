#include <stdio.h>
#include "../1-Executor/descriptor.h"

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
inicialitzar_localitzacions (void)
{
	localitzat = inicialitzar_vector_strings (EndLocalitzacions +1);

	localitzat[Codi]	= "codi";

	localitzat[Arguments]	= "v. arguments";
	localitzat[Locals]	= "v. locals";
	localitzat[Globals]	= "v. globals";

	localitzat[Funcions]	= "f. funcions";
	localitzat[Sistema]	= "f. sistema";
	localitzat[Retorn]	= "f. retorn";

	localitzat[NoRetorn]	= "e. no hi ha retorn";

	localitzat[EndLocalitzacions] = "Final";
}

void
inicialitzar_tipus (void)
{
	tipus = inicialitzar_vector_strings (EndTipus +1);

	tipus[Void]	= "void";
	tipus[Char]	= "char";
	tipus[Int]	= "int";
	tipus[Float]	= "float";
	tipus[Pointer]	= "punter";

	tipus[EndTipus]	= "Final";
}

void
mostra_localitzacions (void)
{
	int i;

	for (i = 0; i < EndLocalitzacions +1; i++)
		if (localitzat[i])
			printf ("-%2d '%s'\n", i, localitzat[i]);
}

void
mostra_tipus (void)
{
	int i;

	for (i = 0; i < EndTipus +1; i++)
		if (tipus[i])
			printf ("-%2d '%s'\n", i, tipus[i]);
}

void
mostra_sistema (void)
{
	int i;

	for (i = 0; i < funcions_sistema.mida; i++)
		printf ("- %3d '%s'\n", i, funcions_sistema.punter[i].nom);
}

void
inicialitzar_depurador (void)
{
	inicialitzar_localitzacions ();
	inicialitzar_tipus ();
}

void
finalitzar_depurador (void)
{
	free (localitzat);
	free (tipus);
}
