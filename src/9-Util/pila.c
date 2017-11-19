#include <string.h>
#include <stdio.h>
#include "pila.h"

struct pila pila_inicialitzar (size_t mida, size_t byts)
{
	// Inicialitza l'estructura amb els valors corresponents.
	struct pila v={
			.us		= 0,
			.mida		= mida,
			.byts		= byts,
			.punter		= malloc (mida*byts)
			};

	// Evita que el programa continuï en cas d'error.
	if (!v.punter && (v.mida != 0))
	{
		printf ("%s\nCapacitat: %zu, Nombre de byts: %zu\n%s\n",
		"Error al inicialitzar el pila.", mida, byts,
		"Error generat pel malloc!");
		exit (EXIT_FAILURE);
	}
	return v;
}

void pila_alliberar (struct pila *v)
{
	// Alliberem evitant errors.
	if (v->mida)
		free (v->punter);

	// Actualitzem els valors.
	v->us		= 0;
	v->mida		= 0;
	v->punter	= NULL;
}

void incrementar_mida_del_pila_en_necessitat (struct pila *v)
{
	// No cal fer res.
	if (v->us < v->mida) return;

	// Valor extret de open source de ArrayList de Java.
	v->mida = (v->mida * 3)/2 +1;

	// Assegura mida mínima.
	if (v->mida <= v->us)
		v->mida = v->us +1;

	v->punter = realloc (v->punter, v->mida * v->byts);

	// Parem en cas d'error.
	if (!v->punter)
	{
		printf ("%s\nCapacitat: %zu, Nombre de byts: %zu\n%s\n",
		"Error al redefinir la mida del pila.", v->mida,
		v->byts, "Error generat pel realloc!");
		exit (EXIT_FAILURE);
	}
}

void assegurar_memoria_minima (struct pila *v)
{
	if (v->us == 0)
	{
		printf ("%s\n%s%zu\n%s\n",
		"Error al treure un element.",
		"Element restants: ", v->us,
		"Error generat al treure on no queda res."
		);

		exit (EXIT_FAILURE);
	}
}

void pila_afegir (struct pila *v, void* punter)
{
	// Cas en que no hi hagi més mida.
	incrementar_mida_del_pila_en_necessitat (v);

	// Emmagatzemem la informació.
	memcpy (v->punter + v->us++*v->byts, punter, v->byts);
}

void* pila_treure (struct pila *v)
{
	// Comprovem que tingui mínim un element.
	assegurar_memoria_minima (v);

	// Retornem l'últim valor i actualitzem v->us.
	return v->punter + (--v->us)*(v->byts);
}

void* pila_mostra (struct pila *v)
{
	// Comprovem que tingui mínim un element.
	assegurar_memoria_minima (v);

	// Retornem l'últim valor.
	return v->punter + (v->us -1)*(v->byts);
}
