#include "maquina_estats_v01.h"
#include "v01-lèxic.h"

#include "../../1-Executor/descriptor.h"
#include "../../9-Util/pila.h"

struct pila g_v_s; // Per poder llegir els noms.

void
definir_variables_i_declarar (char b, struct variables *vs, char *m_error, int lloc)
{
	int mida, i;
	char c;
	struct variable *v;

	llegir_inici_final_1 ('-', b, ':', m_error, lloc, "On \"-[va][^:\\n]:\" és el missatge esperat.");

	vs->mida = mida = llegir_digit_final_1 ( '\n', m_error, lloc, "On tot seguit ':' esperem: \"d+\\n\"" );
	vs->punter = mida ? malloc ( mida * sizeof (struct variable) ) : NULL;

	for (i = 0; i < mida; i++)
	{
		v = vs->punter +i;
		c = llegir_text_sense_espais_ni_intro (&g_v_s, &v->nom, m_error, lloc, "Volem el nom \"[^(comentari)]*");
	}
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
	descriu_lectura_1 (funcio);
	g_v_s = pila_inicialitzar (100, sizeof (char));

	definir_variables_i_declarar ('v', &variables_globals, "Declarant les variables globals", -1);

	/*
	alliberar_funcions ();
	*/
	pila_alliberar (&g_v_s);
}
