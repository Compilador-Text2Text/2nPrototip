#include <stdio.h>
#include "../1-Executor/descriptor.h"
#include "../9-Util/pila.h"

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
	localitzat[Retorn_final]	= "f. exit";
	localitzat[Funcions_especials]	= "f. 'while, for, if'";

	localitzat[NoRetorn]	= "e. no hi ha retorn";

	localitzat[EndLocalitzacions] = "Final";
}

void
inicialitzar_tipus (void)
{
	tipus = inicialitzar_vector_strings (EndTipus +1);

	tipus[CapTipus]	= "NT";
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

/************ EXECUCIÓ ***********/
void
mostra_variable (struct variable *v)
{
}

void
mostra_element_execucio (struct element_execucio *e)
{
	struct descriptor d = e->descriptor;

	printf (" <p%ld", d.vegades_punter);
	if (e->punter)
		printf (" \"%s", e->punter->nom);
	if (d.vegades_punter)
	{
		if ((d.vegades_punter == 1) && (d.tipus == Char))
			printf (" \"%s\"", (char *)e->valor.punter);
	}
	else
		switch (d.tipus)
		{
		case CapTipus:	printf (" NT");				break;
		case Void:	printf (" void");			break;
		case Char:	printf (" '%c'", e->valor.caracter);	break;
		case Int:	printf (" %d", e->valor.enter);		break;
		case Float:	printf (" %f", e->valor.flotant);	break;
		case Pointer:	printf (" %p", e->valor.punter);	break;
		case EndTipus:
		default:	printf (" ERROR'end'");			break;
		}
	printf (">");
}

void
mostra_memoria_execucio (struct pila *p)
{
	int i;
	struct memoria_execucio m;
	struct funcio_dinamica	*f;

	f = pila_mostra (p);
	m = f->memoria;

	printf ("%2ld:", m.us);
	for (i = 0; i < m.us; i++)
		mostra_element_execucio (m.punter +i);
	printf ("\n");
}
