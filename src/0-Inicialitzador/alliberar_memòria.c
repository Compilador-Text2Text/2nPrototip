#include <stdio.h>
#include "../1-Executor/descriptor.h"

void
alliberar_variables (struct variables *vs)
{
	int i;

	for (i = 0; i < vs->mida; i++)
		free (vs->punter[i].nom);

	free (vs->punter);
	vs->mida = 0;
}

void
alliberar_frases ( struct frase *f )
{
printf ("\nA\n");
	free (f->punter);
printf ("B\n");
	f->mida = 0;
}

void
alliberar_codi ( struct codi *codi )
{
	int i;

	for (i = 0; i < codi->mida; i++)
		alliberar_frases ( codi->punter +i );

	free ( codi->punter );
	codi->mida = 0;
}

void
alliberar_funcions (void)
{
	int i;
	struct descriptor_funcio *pdf;

	for (i = 0; i < descriptors_funcio.mida; i++)
	{
		pdf = descriptors_funcio.punter + i;
		free (pdf->nom);
		alliberar_variables ( &pdf->arguments );
		alliberar_variables ( &pdf->local );
		alliberar_codi ( &pdf->codi );
	}

	free (descriptors_funcio.punter);
	descriptors_funcio.mida = 0;
}

// Nom no molt adequat, perquè també afecta a les variables globals.
void
alliberar_descriptors_funcions (void)
{
	alliberar_variables (&variables_globals);
	alliberar_funcions ();
}
