#include "maquina_estats_v01.h"
#include "v01-lèxic.h"

#include "../../1-Executor/descriptor.h"
#include "../../9-Util/pila.h"

struct pila g_v_s; // Per poder llegir els noms.

union valor
definir_valor (struct descriptor d, char *m_error, int lloc, char* concret)
{
	union valor v;
	char c;

	// Cal reservar memòria.
	if (d.vegades_punter)
	{
		if ((d.tipus == Char) && (d.vegades_punter == 1))
			v.punter = llegir_text (&g_v_s, m_error, lloc, "Llegim un string: \"([^\"]*)\"");
		else
			error_procedencia (m_error, lloc, "No hi ha inicialitzar memòria pel tipus demanat.");
	}

	// Si no és un punter.
	switch (d.tipus)
	{
	case CapTipus:
		error_procedencia (m_error, lloc, "No hi ha inicialització per cap tipus.");

	case Void:
		error_procedencia (m_error, lloc, "No hi ha inicialització pel void.");

	case Char:
		v.caracter = llegir_caracter_facil (m_error, lloc, "Esperem un caràcter: '(.)'");
		break;

	case Int:
		v.enter = llegir_digit_pos_neg (m_error, lloc, "Llegim amb un enter.");
		break;

	case Float:
		v.flotant = llegir_digit_float (&c, m_error, lloc, "Llegim amb l'scanf.");
		break;

	case Pointer:
		break;
	default:
		error_procedencia (m_error, lloc, "Tipus no existeix.");
	}

	return v;
}

// ' '\d*(tipus)' '\d*(vegades punter)
char
llegir_tipus_vegades_punter (char c, struct descriptor *d, char *m_error, int lloc, char *concret)
{
	comprovacio_caracter_amb_2 (' ', c, m_error, lloc, concret);
	d->tipus = llegir_digit_final_limitat_1 ( ' ', EndTipus, m_error, lloc, concret );
	d->vegades_punter = llegir_digit ( &c, m_error, lloc, concret);

	return c;
}

// -[av][^:\n]:\d*
// "nom \d*(tipus) \d*(vegades punter)\n
// "nom \d*(tipus) \d*(vegades punter)[^\n](valor)
void
definir_variables_i_declarar (char b, struct variables *vs, char *m_error, int lloc)
{
	int mida;
	char c;
	struct variable *v;

	llegir_inici_final_1 ('-', b, ':', m_error, lloc, "On \"-[va][^:\\n]:\" és el missatge esperat.");

	vs->mida = mida = llegir_digit_final_1 ( '\n', m_error, lloc, "On tot seguit ':' esperem: \"d+\\n\"" );
	vs->punter = mida ? malloc ( mida * sizeof (struct variable) ) : NULL;

	for (v = vs->punter; v < vs->punter +mida; v++)
	{
		v->usat = Fals; // Això ho ha de definir
		c = llegir_text_sense_espais_ni_intro (&g_v_s, &v->nom, m_error, lloc, "Volem el nom \"[^(comentari)]*");
		c = llegir_tipus_vegades_punter (c, &v->descriptor, m_error, lloc, "Entrada: \\d*(tipus) \\d*(v. punter).");

		v->inicialitzat = Cert;
		if ( c == '\n' )
			v->inicialitzat = Fals;
		else
			v->valor = definir_valor (v->descriptor, m_error, lloc, "Definint el valor d'una variable.");
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
