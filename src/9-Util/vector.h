#ifndef UTIL_VECTOR_H_
#define UTIL_VECTOR_H_

#include <stdlib.h>

struct
vector
{
	size_t us;
	size_t mida;
	size_t byts;
	void * punter;
};

// Treballant amb memòria.
struct vector vector_inicialitzar (size_t capacitat_inicial, size_t byts_per_element);
void vector_alliberar (struct vector *v);

// Instruccions de pila.
void  vector_afegir (struct vector *v, void* dada);
void* vector_treure (struct vector *v);
void* vector_mostra (struct vector *v);

#endif // UTIL_VECTOR_H_
