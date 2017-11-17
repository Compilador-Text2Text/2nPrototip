#include <stdlib.h>

#include "funcions.h"
#include "../1-Executor/executor.h"

void
inicialitza_funcions_sistema (void)
{
	struct funcio_sistema *fs;
	funcions_sistema.mida = End_sistema;
	funcions_sistema.punter = malloc ( End_sistema * sizeof (struct funcio_sistema) );

	fs = funcions_sistema.punter + Igual_general;
	fs->nom		= "Igual general (=)";
	fs->funcio	= igual_general;

	fs = funcions_sistema.punter + Extreure_punter;
	fs->nom		= "Extreure punter (&(var))";
	fs->funcio	= extreu_punter;
}

void
finalitza_funcions_sistema (void)
{
	funcions_sistema.mida = 0;
	free (funcions_sistema.punter);
	funcions_sistema.punter = NULL;
}
