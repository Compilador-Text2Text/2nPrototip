#include <string.h>
#include <stdio.h>
#include "vector.h"

struct vector vector_inicialitzar (size_t mida, size_t byts)
{
	// Inicialitza l'estructura amb els valors corresponents.
	struct vector v={
			.us		= 0,
			.mida		= mida,
			.byts		= byts,
			.punter		= malloc (mida*byts)
			};

	// Evita que el programa continuï en cas d'error.
	if (!v.punter && (v.mida != 0))
	{
		printf ("%s\nCapacitat: %zu, Nombre de byts: %zu\n%s\n",
		"Error al inicialitzar el vector.", mida, byts,
		"Error generat pel malloc!");
		exit (EXIT_FAILURE);
	}
	return v;
}

void vector_alliberar (struct vector *v)
{
	// Alliberem evitant errors.
	if (v->mida)
		free (v->punter);

	// Actualitzem els valors.
	v->us		= 0;
	v->mida		= 0;
	v->punter	= NULL;
}

void incrementar_mida_del_vector_en_necessitat (struct vector *v)
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
		"Error al redefinir la mida del vector.", v->mida,
		v->byts, "Error generat pel realloc!");
		exit (EXIT_FAILURE);
	}
}

void assegurar_memoria_minima (struct vector *v)
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

void vector_afegir (struct vector *v, void* punter)
{
	// Cas en que no hi hagi més mida.
	incrementar_mida_del_vector_en_necessitat (v);

	// Emmagatzemem la informació.
	memcpy (v->punter + v->us++*v->byts, punter, v->byts);
}

void* vector_treure (struct vector *v)
{
	// Comprovem que tingui mínim un element.
	assegurar_memoria_minima (v);

	// Retornem l'últim valor i actualitzem v->us.
	return v->punter + (--v->us)*(v->byts);
}

void* vector_mostra (struct vector *v)
{
	// Comprovem que tingui mínim un element.
	assegurar_memoria_minima (v);

	// Retornem l'últim valor.
	return v->punter + (v->us -1)*(v->byts);
}
