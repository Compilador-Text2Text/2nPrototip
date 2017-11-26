#include <stdlib.h>
#include <string.h>

#include "instruccions.h"
#include "../6-Depurador/depurador.h"

void
codi_a_element_execucio (struct element_execucio *e, struct paraula p)
{
	e->descriptor	= p.descriptor;
	e->valor	= p.auxiliar;
	e->punter	= NULL;
}

void
variable_a_element_execucio (struct element_execucio *e, struct variable *v)
{
	e->descriptor	= v->descriptor;
	e->valor	= v->valor;
	e->punter	= v;
}

// Crear una nova funció, arguments.
void
element_execucio_a_variable (struct variable *v, struct element_execucio *e)
{
	v->descriptor	= e->descriptor;
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
	fd.arguments.punter = n ? malloc ( n * sizeof (struct variable) ) : NULL;
	memcpy (fd.arguments.punter, df.arguments.punter, n * sizeof (struct variable) );
	for (i = 0; i < n; i++)
		element_execucio_a_variable (fd.arguments.punter +i, e +i);

	// Variables locals
	fd.local = df.local;
	fd.local.punter = fd.local.mida ? malloc ( fd.local.mida * sizeof (struct variable) ) : NULL;
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

// Retorna la paraula que toca i fa l'increment per la següent crida.
struct paraula
toquen_i_increment ( struct funcio_dinamica *f )
{
	struct paraula paraula;

	// Per defecte necessitem un retorn.
	if (f->descriptor->codi.mida == f->cp1)
	{
		paraula.lloc.on = NoRetorn;
		return paraula;
	}

	paraula = f->descriptor->codi.punter[f->cp1].punter[f->cp2];

	// Alliberem la memòria d'execució.
	if ( !f->cp2 )
		f->memoria.us = 0;

	// Incrementem
	if ( ++f->cp2 == f->descriptor->codi.punter[f->cp1].mida )
	{
		f->cp2 = 0;
		f->cp1++;
	}

	return paraula;
}

// No cal comprovar, ja que representa que ho ha fet l'anàlisi semàntica.
struct element_execucio *
obtencio_element_execucio (struct funcio_dinamica *f)
{
	return f->memoria.punter + f->memoria.us++;
}

int
execucio_paraula (struct pila *p)
{
	int aux, aux2;
	struct funcio_dinamica	*f;
	struct paraula		paraula;
	struct element_execucio	*e;

mostra_memoria_execucio (p);

	f = pila_mostra (p);
	paraula = toquen_i_increment (f);
	e = obtencio_element_execucio (f);

	switch (paraula.lloc.on)
	{
	case Codi:
		codi_a_element_execucio (e, paraula);
		return 1;

	// Variables.
	case Arguments:
		variable_a_element_execucio (e, f->arguments.punter + paraula.lloc.relatiu);
		return 1;
	case Locals:
		variable_a_element_execucio (e, f->local.punter + paraula.lloc.relatiu);
		return 1;
	case Globals:
		variable_a_element_execucio (e, variables_globals.punter + paraula.lloc.relatiu);
		return 1;

	// Funcions.
	case Funcions:
		aux = paraula.auxiliar.enter;
		f->memoria.us -= aux;
		e -= aux;
		crear_nova_funcio_dinamica (aux, e, paraula.lloc.relatiu, p);
		return 1;
	case Sistema:
		aux = paraula.auxiliar.enter;
		f->memoria.us -= aux;
		e -= aux;
		return crida_funcio_sistema (paraula.lloc.relatiu, aux, e, f);
	case Retorn:
		aux = paraula.auxiliar.enter;
		e -= aux;
		if (aux) *f->punter_retorn = *e;
		if (f->arguments.mida)	free (f->arguments.punter);
		if (f->local.mida)	free (f->local.punter);
		free (f->memoria.punter);
		return --p->us;
	case Retorn_final:
		aux = paraula.auxiliar.enter;
		e -= aux;
		if (aux) aux2 = e->valor.enter;

		if (f->arguments.mida)	free (f->arguments.punter);
		if (f->local.mida)	free (f->local.punter);
		free (f->memoria.punter);

		while (p->us--)
		{
			f = pila_mostra (p);

			if (f->arguments.mida)	free (f->arguments.punter);
			if (f->local.mida)	free (f->local.punter);
			free (f->memoria.punter);
		}

		if (aux) f->punter_retorn->valor.enter = aux2;
		return 0;
	case NoRetorn:
	case Funcions_especials:
	case EndLocalitzacions:
	default:
		break;
	}
	return 0;
}
