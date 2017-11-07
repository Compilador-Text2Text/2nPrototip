#include "maquina_estats.h"
#include <stdio.h>

void llegir (char (*funcio) (void))
{
	char c;
	descriu_lectura (funcio);

	c = llegir_linia ();
	printf ("Caracter llegit: '%c'\n", c);
	llegir_inici_final ('i', 'o');
}
