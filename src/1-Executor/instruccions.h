#ifndef EXECUTOR_DESCRIPTOR_H_
#define EXECUTOR_DESCRIPTOR_H_

#include "descriptor.h"
#include "../9-Util/pila.h"

void
crear_nova_funcio_dinamica
(
 size_t n,			// Nombre d'arguments.
 struct element_execucio *e,	// On ha de fer el retorn.
 size_t r,			// Descriptor de funció relativa.
 struct pila *p			// On guardarem el resultat.
);

#endif // EXECUTOR_DESCRIPTOR_H_
