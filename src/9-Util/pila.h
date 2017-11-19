#ifndef UTIL_VECTOR_H_
#define UTIL_VECTOR_H_

#include <stdlib.h>

struct
pila
{
	size_t us;
	size_t mida;
	size_t byts;
	void * punter;
};

// Treballant amb memòria.
struct pila pila_inicialitzar (size_t capacitat_inicial, size_t byts_per_element);
void pila_alliberar (struct pila *v);

// Instruccions de pila.
void  pila_afegir (struct pila *v, void* dada);
void* pila_treure (struct pila *v);
void* pila_mostra (struct pila *v);

#endif // UTIL_VECTOR_H_
