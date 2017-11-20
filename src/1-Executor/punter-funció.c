#include "punter-funció.h"
#include "executor.h"

void
funcio_ciclica
(
 struct punter_funcio *f,
 struct pila *p
)
{
	while ( f->funcio ( f, p ) );
}

// Hauria de ser un altre .c...
int
funcio_executa_paraula ( struct punter_funcio *f, struct pila *p)
{
	return execucio_paraula (p);
return 0;
}
