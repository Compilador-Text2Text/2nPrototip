#ifndef EXECUTOR_FUNCIO_H_
#define EXECUTOR_FUNCIO_H_

#include "descriptor.h"
#include "../9-Util/pila.h"

struct punter_funcio
{
	int (*funcio) (struct punter_funcio*, struct pila *);
};

// Primari qui executarà punter de funció.
void funcio_ciclica ( struct punter_funcio *, struct pila *);

// Execució simple
int  funcio_executa_paraula ( struct punter_funcio *, struct pila *);

#endif // EXECUTOR_FUNCIO_H_
