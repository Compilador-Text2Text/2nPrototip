#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "0-Inicialitzador/v00.h"
#include "0-Inicialitzador/v01.h"

void
missatge_error (void)
{
	printf ("ERROR: operació no especificada (usi -h per tenir ajuda)\n");
}

int main (int argc, char *argv[])
{
	int out, i;
	char *nom = NULL;
	int nombre_arguments = 0;
	char **arguments = NULL;
	enum tipus_execucio
	{
		Simple,
		Cap
	} exec = Cap;


	for (i = 1; i < argc; i++)
	{
		// Descriu quin fitxer llegirà.
		if ( !strcmp ("-f", argv[i]) )
		{
			exec = Simple;
			nom = argv[++i];
		}

		// Mostrarà com estan definits els elements. "enums"
		else if ( !strcmp ("-hf", argv[i]) )
		{
			inicialitzador_informacio ();
			return 0;
		}

		// Per afegir els arguments.
		else if ( !strcmp ("-a", argv[i]) )
		{
			nombre_arguments = atoi (argv[++i]);
			arguments = malloc ( nombre_arguments * sizeof (char*) );

			for (out = 0; out < nombre_arguments; out++)
				if (++i >= argc)
				{
					printf ("ERROR:\n");
					printf ("No hi ha el nombre d'arguments que diu.\n");
					return 1;
				}
				else
					arguments[out] = argv[i];
		}
		else
		{
			printf ("Desconegut: '%s'\n", argv[i]);
			missatge_error ();
			return 1;
		}
	}

	switch (exec)
	{
	case Simple:
		out = inicialitzador_lectura_objecte (nom, nombre_arguments, arguments);
		finalitza_allibera_memoria ();
		if (arguments)
			free (arguments);
		return out;

	case Cap:
		missatge_error ();
		if (arguments)
			free (arguments);
	default:
		return 1;
	}
}
