#include <stdio.h>

#include "shunting-yard_algorithm.h"

#include "../9-Util/pila.h"

struct
sya_salts
{
	enum pre_execucio tipus;
	size_t on;
	struct frase condicio;
	struct frase inici;
	struct frase increment;
	size_t primera_paraula_relativa;
};

struct pila pco;	// Pila del codi, sortida.
struct pila pfo;	// Pila de frase, sortida.
struct pila pfa;	// Pila de frase, auxiliar.
struct pila pj;		// Pila dels salts (jumps).

enum cert_fals bolea_obert_arguments	= Fals; // Nombre arguments 0 o major.
enum cert_fals bolea_condicio		= Fals; // while (cond), for (,condi,), if (cond)
enum cert_fals bolea_inici		= Fals; // for (inici,
enum cert_fals bolea_increment		= Fals; // for (,,increment)

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
preparacio_salt_logic (struct sya_salts *s, struct paraula *p)
{
	struct paraula n;

	n.lloc.on = Sistema;
	n.lloc.relatiu = GotoZ;
	n.descriptor.tipus = CapTipus;
	n.descriptor.vegades_punter = 0;
	n.auxiliar.enter = 0;
	shunting_yard_algorithm_paraula (&n);

	n.lloc.on = Preexecucio;
	n.lloc.relatiu = Obert;
	shunting_yard_algorithm_paraula (&n);

	n.lloc.on = Codi;
	n.lloc.relatiu = 0;
	shunting_yard_algorithm_paraula (&n);

	n.lloc.on = Preexecucio;
	n.lloc.relatiu = Coma;
	shunting_yard_algorithm_paraula (&n);

	s->tipus			= p->lloc.relatiu;
	s->on				= pco.us;
	s->condicio.punter		= NULL;
	s->condicio.mida		= 0;
	s->inici.punter			= NULL;
	s->inici.mida			= 0;
	s->increment.punter		= NULL;
	s->increment.mida		= 0;
	s->primera_paraula_relativa	= pfo.us;
	pila_afegir (&pj, s);
}

void
pre_execucio (struct paraula *p)
{
	struct paraula *a, n;
	int i;
	struct estats_sya o;
	struct sya_salts s;


	switch ((enum pre_execucio)p->lloc.relatiu)
	{
	case Obert:
		bolea_obert_arguments = Cert;
		pila_afegir (&pfa, p);
		break;

	case Coma:
		while (pfa.us)
		{
			a = pila_mostra (&pfa);
			if ((a->lloc.on == Preexecucio) && (a->lloc.relatiu == Obert))
			{
				a->auxiliar.enter++;
				return;
			}

			pila_afegir (&pfo, a);
			pila_treure (&pfa);
		}
		printf ("Error, Coma sense parèntesis obert\n");
		exit (EXIT_FAILURE);

	case Tancat:
		while (pfa.us)
		{
			a = pila_treure (&pfa);
			if ((a->lloc.on == Preexecucio) && (a->lloc.relatiu == Obert))
			{
				i = a->auxiliar.enter;
				a = pila_mostra (&pfa);

				si_operant_retorna_estat_sya (a, &o);

				if (o.tipus_funcio == Funcio)
				{
					a->auxiliar.enter = i;
					pila_afegir (&pfo, pila_treure (&pfa));
				} else if (i)
				{
					printf ("Arguments per una no funció!\n");
					exit (EXIT_FAILURE);
				}
				return;
			}

			pila_afegir (&pfo, a);

			if (bolea_condicio)
			{// Només pel while.
				printf ("TODO, pendent a fer!\n");
				bolea_condicio = Fals;
				exit (EXIT_FAILURE);
			}
			if (bolea_increment)
			{// Només el final del for.
				printf ("TODO, pendent a fer!\n");
				bolea_increment = Fals;
				exit (EXIT_FAILURE);
			}
		}
		printf ("Error, Coma sense parèntesis obert\n");
		exit (EXIT_FAILURE);

	case While:
		bolea_condicio = Cert;
		preparacio_salt_logic (&s, p);
		break;

	case End_While:
		s = *(struct sya_salts*) pila_treure (&pj);
		if (s.tipus != While)
		{
			printf ("ERROR, no és un while!\n");
			exit (EXIT_FAILURE);
		}

		n.lloc.on = Sistema;
		n.lloc.relatiu = GotoNZ;
		n.descriptor.tipus = CapTipus;
		n.descriptor.vegades_punter = 0;
		n.auxiliar.enter = 0;

		n.lloc.on = Preexecucio;
		n.lloc.relatiu = Obert;
		shunting_yard_algorithm_paraula (&n);

		n.lloc.on = Codi;
		n.lloc.relatiu = s.on +1; // TODO, comprovar el resultat!
		shunting_yard_algorithm_paraula (&n);

		n.lloc.on = Preexecucio;
		n.lloc.relatiu = Coma;
		shunting_yard_algorithm_paraula (&n);

		for (i = 0; i < s.condicio.mida; i++)
			pila_afegir (&pfo, s.condicio.punter +i);

		n.lloc.on = Preexecucio;
		n.lloc.relatiu = Tancat;
		shunting_yard_algorithm_paraula (&n);
	}
	/*
struct
sya_salts
{
	enum pre_execucio tipus;
	size_t on;
	struct frase *condicio;
	struct frase *inici;
	struct frase *increment;
	size_t primera_paraula_relativa;
};*/
}

void
shunting_yard_algorithm_paraula (struct paraula *p)
{
//printf ("hola món\n"); // Peta per problemes de reservar memòria.
// TODO Vigilar a fer-ho prou lent per evitar aquests problemes!

	// Cas de tenir arguments la funció.
	if (bolea_obert_arguments)
	{
		bolea_obert_arguments = Fals;

		if (p->lloc.on == Preexecucio)
			if (p->lloc.relatiu != Tancat)
				((struct paraula *)pila_mostra (&pfa))->auxiliar.enter = 1;
	}

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
		funcio_o_operant (p);
		// Amb el relatiu, recuperar la informació pel sya
		// enviar la informació amb la paraula (així per Sistema també funcionarà!
		break;
		// Repetir l'anterior!
		// VIGILAR FUNCIO O OPERANT!
		break;

	case Preexecucio:
		pre_execucio (p);
		break;

	default:
		printf ("Error, entrat un valor inesperat\n");
		exit (EXIT_FAILURE);
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
	pco = pila_inicialitzar (codi, sizeof (struct codi));
	pfo = pila_inicialitzar (frase, sizeof (struct frase));
	pfa = pila_inicialitzar (frase, sizeof (struct frase));
	pj  = pila_inicialitzar (jumps, sizeof (struct sya_salts));
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
