#include <stdio.h>

#include "shunting-yard_algorithm.h"

#include "../9-Util/pila.h"

struct pila pco;	// Pila del codi, sortida.
struct pila pfo;	// Pila de frase, sortida.
struct pila pfa;	// Pila de frase, auxiliar.
struct pila pj;		// Pila dels salts (jumps).

int
si_operant_retorna_estat_sya (struct paraula *p, struct estats_sya *s)
{
	// TODO fer que d'una paraula, retorni el estats_sya
	// també representa que ha de retornar 0 si correcte, i 1 si falç.

	s->tipus_funcio = Funcio;
	s->precedencia = 20;

	return 0;
}

void
funcio_o_operant (struct paraula *p)
{
	struct estats_sya o1, o2;
	struct paraula *s;
	int c;

	si_operant_retorna_estat_sya (p, &o1);

	switch (o1.tipus_funcio)
	{
	case Funcio:
		pila_afegir (&pfa, p);
		return;

	case Asociativa_dreta:		// >
		c = 0;
		break;
	case Asociativa_esquerra:	// ≥
		c = 1;
		break;
	}

	while ( pfa.us )
	{
		s = (struct paraula *) pila_mostra (&pfa);

		if (si_operant_retorna_estat_sya (s, &o2))
			break;

		if ((o1.precedencia +c) > o2.precedencia)
			break;

		pila_afegir (&pfo, pila_treure (&pfa));
	}

	pila_afegir (&pfa, p);

}

void
shunting_yard_algorithm_paraula (struct paraula *p)
{
//printf ("hola món\n"); Peta per problemes de reservar memòria.
// TODO Vigilar a fer-ho prou lent per evitar aquests problemes!
	switch (p->lloc.on)
	{
	case Codi:
	case Arguments:
	case Locals:
	case Globals:
		pila_afegir (&pfo, p);
		break;

	case Funcions:
	case Sistema:
		// Amb el relatiu, recuperar la informació pel sya
		// enviar la informació amb la paraula (així per Sistema també funcionarà!
		break;
		// Repetir l'anterior!
		// VIGILAR FUNCIO O OPERANT!
		break;

	case Preexecucio:

		printf ("Error, entrat un valor inesperat\n");
		exit (1);
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
shunting_yard_algorithm_inicialitzar (size_t codi, size_t frase, size_t jumps)
{
	pco = pila_inicialitzar (codi, sizeof (struct codi *));
	pfo = pila_inicialitzar (frase, sizeof (struct frase *));
	pfa = pila_inicialitzar (frase, sizeof (struct frase *));
	pj  = pila_inicialitzar (jumps, sizeof (struct frase *));
}

void
shunting_yard_algorithm_finalitzar (void)
{
	pila_alliberar (&pco);
	pila_alliberar (&pfo);
	pila_alliberar (&pfa);
	pila_alliberar (&pj);
}

void
shunting_yard_algorithm (void)
{
	int i;

	shunting_yard_algorithm_inicialitzar (100, 100, 100);

	for (i = 0; i < descriptors_funcio.mida; i++)
		shunting_yard_algorithm_codi ( &(descriptors_funcio.punter[i].codi) );

	shunting_yard_algorithm_finalitzar ();
}
