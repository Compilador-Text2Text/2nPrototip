#include <stdio.h>
#include <string.h>

#include "0-Inicialitzador/v00.h"


int main (int argc, char *argv[])
{
	int out, i;
	char *nom;
	enum tipus_execucio
	{
		Simple,
		Mostra_ajuda,
		Cap
	} exec = Simple;


	for (i = 1; i < argc; i++)
	{
		if ( !strcmp ("-f", argv[i]) )
			nom = argv[++i];
		else if ( !strcmp ("-hf", argv[i]) )
			exec = Mostra_ajuda;
		else
		{
			printf ("ERROR:\n");
			printf ("L'entrada no és vàlida 'comandes'.\n");
			printf ("Per més ajuda premi 'h'.\n");
			return 1;
		}
	}

	switch (exec)
	{
	case Simple:
		out = inicialitzador_lectura_objecte (nom);
		finalitza_allibera_memoria ();
		return out;

	case Mostra_ajuda:
		inicialitzador_informacio ();
		return 0;

	case Cap:
	default:
		return 1;
	}
}
