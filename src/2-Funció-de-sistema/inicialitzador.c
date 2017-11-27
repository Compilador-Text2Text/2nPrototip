#include <stdlib.h>
#include <string.h>

#include "funcions.h"
#include "../1-Executor/descriptor.h"
#include "../9-Util/memoria.h"

void
definir_funcio_sistema (int lloc, char *nom,
		int (*funcio) (size_t, struct element_execucio *, struct funcio_dinamica *),
		struct variables arguments,
		struct descriptor descriptor)
{
	struct funcio_sistema *f;
	f = funcions_sistema.punter + lloc;
	f->nom = nom;
	f->funcio = funcio;
	f->descriptor = descriptor;

	//f->arguments = arguments; TODO
	//f->arguments.punter = reservar_memoria_i_copiarla ( arguments.punter, arguments.mida * sizeof (struct variable) );
}

void
inicialitza_funcions_sistema (void)
{
	struct descriptor descriptor = {.tipus = Void, .vegades_punter = 0};
	struct variables vs = {.mida = 2};

	funcions_sistema.mida = End_sistema;
	funcions_sistema.punter = malloc ( End_sistema * sizeof (struct funcio_sistema) );

	vs.punter = malloc (vs.mida * sizeof (struct variable));
	vs.punter[0].descriptor = descriptor;
	vs.punter[1].descriptor = descriptor;

	// Declarant funcions.
	definir_funcio_sistema (Igual_general, "=", igual_general, vs, descriptor);

	descriptor.vegades_punter = 1;
	definir_funcio_sistema (Extreure_punter, "&", extreu_punter, vs, descriptor);

	free (vs.punter);
}

void
finalitza_funcio_sistema ( struct llista_sistema *f )
{
	int i;

	for (i = 0; i < f->mida; i++)
		;
		//free (f->punter[i].arguments.punter); TODO

	funcions_sistema.mida = 0;
	free (funcions_sistema.punter);
	funcions_sistema.punter = NULL;
}

void
finalitza_funcions_sistema (void)
{
	finalitza_funcio_sistema ( &funcions_sistema );
}
