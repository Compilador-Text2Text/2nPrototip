#include <stdlib.h>
#include <string.h>

void *
reservar_memoria_i_copiarla ( void * punter, int mida )
{
	void *o;

	o = malloc ( mida );
	strncpy (o, punter, mida );

	return o;
}
