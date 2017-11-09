#include <stdio.h>
#include "depurador.h"

int
main ()
{
	inicialitzar_depurador ();
		printf ("Demanem que mostri localitzacions:\n");
		mostra_localitzacions ();

		printf ("\nDemanem que mostri els tipus:\n");
		mostra_tipus ();
	finalitzar_depurador ();
	return 0;
}
