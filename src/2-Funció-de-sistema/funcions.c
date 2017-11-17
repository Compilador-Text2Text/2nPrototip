#include "funcions.h"

/**
 *(size_t n, struct element_execucio *e, struct funcio_dinamica *f)
 * n on és el nombre d'arguments.
 * e on és l'element d'execució.
 * f on és la funció dinàmica.
 **/

// Mou les dades cap al punter. (=)
int
igual_general
(size_t n, struct element_execucio *e, struct funcio_dinamica *f)
{
	*((union valor*) e->punter) = e[1].valor;
	return 1;
}

// Posar el punter com a valor. (&var)
int
extreu_punter
(size_t n, struct element_execucio *e, struct funcio_dinamica *f)
{
	e->valor.punter = e->punter;
	return 1;
}
