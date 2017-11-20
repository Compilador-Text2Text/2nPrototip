#include <stdlib.h>
#include <string.h>

#include "instruccions.h"

void
codi_a_element_execucio (struct element_execucio *e, struct paraula p)
{
	e->valor	= p.auxiliar;
	e->punter	= NULL;
}

void
variable_a_element_execucio (struct element_execucio *e, struct variable *v)
{
	e->valor	=  v->valor;
	e->punter	= &v->valor;
}

void
element_execucio_a_variable (struct variable *v, struct element_execucio *e)
{
	v->valor	= e->valor;
}

void
crear_nova_funcio_dinamica
(
 size_t n,			// Nombre d'arguments.
 struct element_execucio *e,	// On ha de fer el retorn.
 size_t r,			// Descriptor de funció relativa.
 struct pila *p			// On guardarem el resultat.
)
{
	struct funcio_dinamica fd = {.cp1 = 0, .cp2 = 0 };
	struct descriptor_funcio df;
	int i;

	// Execució
	fd.descriptor = descriptors_funcio.punter + r;
	df = * fd.descriptor;
	fd.memoria.mida = df.mida_memoria_execucio;
	fd.memoria.punter = malloc ( fd.memoria.mida * sizeof (struct element_execucio) );

	// Retorn
	fd.punter_retorn = e;

	// Arguments
	fd.arguments.mida = n;
	fd.arguments.punter = malloc ( n * sizeof (struct variable) );
	memcpy (fd.arguments.punter, df.arguments.punter, n * sizeof (struct variable) );
	for (i = 0; i < n; i++)
		element_execucio_a_variable (fd.arguments.punter +i, e +i);

	// Variables locals
	fd.local = df.local;
	fd.local.punter = malloc ( fd.local.mida * sizeof (struct variable) );
	memcpy (fd.local.punter, df.local.punter, fd.local.mida * sizeof (struct variable) );

	pila_afegir (p, &fd);
}

int
crida_funcio_sistema
(
 size_t r,			// Funció relativa.
 size_t n,			// Nombre d'arguments.
 struct element_execucio *e,	// On ha de fer el retorn.
 struct funcio_dinamica *f	// Si toca dades com per fer un GOTO.
)
{
	return funcions_sistema.punter[r].funcio (n, e, f);
}
