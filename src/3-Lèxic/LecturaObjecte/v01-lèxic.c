#include "v01-lèxic.h"
#include "maquina_estats.h"
#include "../../1-Executor/descriptor.h"

struct pila g_v_s; // Per poder llegir els noms.

void
definir_variables_i_declarar (char b, struct variables *vs, char *m_error, int lloc)
{
	comprovacio_caracter_1 ('-', m_error, lloc,
			"Per demanar declarar les variables, cal començar amb '-'");
	llegir_inici_final_1 (b, ':', m_error, lloc,
"Ha començat bé: '-'.\
Continua amb: '%c' i ha entrat: '%c'.\
On acaba amb: ':' i ha entrat: '%c'.\
Tot seguit de ':' va el dígit per reservar memòria per les variables.\
");
}
/*
	int i;

	for (i = 0; i < vs->mida; i++)
		free (vs->punter[i].nom);

	free (vs->punter);
	vs->mida = 0;
	*/

void
llegir_codi_objecte_v01 (char (*funcio) (void), enum lexic_v01 estat)
{
	descriu_lectura (funcio);
	g_v_s = pila_inicialitzar (100, sizeof (char));

	definir_variables_i_declarar ('v', &variables_globals, "Declarant les variables globals", -1);

	/*
	alliberar_funcions ();
	*/
	pila_alliberar (&g_v_s);
}
