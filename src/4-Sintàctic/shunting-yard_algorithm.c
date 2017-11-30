#include <stdio.h>

#include "shunting-yard_algorithm.h"

#include "../9-Util/pila.h"

struct pila pco;	// Pila del codi, sortida.
struct pila pfo;	// Pila de frase, sortida.
struct pila pfa;	// Pila de frase, auxiliar.
struct pila pj;		// Pila dels salts (jumps).

void
shunting_yard_algorithm_paraula (struct paraula *p)
{
printf ("hola món\n");
	switch (p->lloc.on)
	{
	case Codi:
	case Arguments:
	case Locals:
	case Globals:
		pila_afegir (&pfo, p);
		break;
	}
}

void
shunting_yard_algorithm_frase (struct frase *f)
{
	int i;

	for (i = 0; i < f->mida; i++)
		shunting_yard_algorithm_paraula ( f->punter +i );
}

void
shunting_yard_algorithm_codi (struct codi *c)
{
	int i;

	for (i = 0; i < c->mida; i++)
		shunting_yard_algorithm_frase ( c->punter +i );
}

void
shunting_yard_algorithm (void)
{
	int i;
	pco = pila_inicialitzar (100, sizeof (struct codi *));
	pfo = pila_inicialitzar (100, sizeof (struct frase *));
	pfa = pila_inicialitzar (100, sizeof (struct frase *));
	pj  = pila_inicialitzar (100, sizeof (struct frase *));

	for (i = 0; i < descriptors_funcio.mida; i++)
		shunting_yard_algorithm_codi ( &(descriptors_funcio.punter[i].codi) );

	pila_alliberar (&pco);
	pila_alliberar (&pfo);
	pila_alliberar (&pfa);
	pila_alliberar (&pj);
}
