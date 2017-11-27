#include "maquina_estats_v01.h"
#include "v01-lèxic.h"

#include "../../1-Executor/descriptor.h"
#include "../../9-Util/pila.h"

struct pila g_v_s; // Per poder llegir els noms.
// TODO fer que pugui ser verbós!

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
		error_procedencia (m_error, lloc, "No sabem inicialitzar un punter.");

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

void
definir_variable (struct variable *v, char* m_error, int lloc)
{
	char c;

	v->usat = Fals; // Això ho ha de definir
	c = llegir_text_sense_espais_ni_intro (&g_v_s, &v->nom, m_error, lloc, "Volem el nom \"[^(comentari)]*");
	c = llegir_tipus_vegades_punter (c, &v->descriptor, m_error, lloc, "Entrada: \\d*(tipus) \\d*(v. punter).");

	v->inicialitzat = Cert;
	if ( c == '\n' )
		v->inicialitzat = Fals;
	else
		v->valor = definir_valor (v->descriptor, m_error, lloc, "Definint el valor d'una variable.");
}

// -[av][^:\n]:\d*
// "nom \d*(tipus) \d*(vegades punter)\n
// "nom \d*(tipus) \d*(vegades punter)[^\n](valor)
void
definir_variables_i_declarar (char b, struct variables *vs, char *m_error, int lloc)
{
	int mida;
	struct variable *v;

	llegir_inici_final_1 ('-', b, ':', m_error, lloc, "On \"-[va][^:\\n]:\" és el missatge esperat.");

	vs->mida = mida = llegir_digit_final_1 ( '\n', m_error, lloc, "On tot seguit ':' esperem: \"d+\\n\"" );
	vs->punter = mida ? malloc ( mida * sizeof (struct variable) ) : NULL;

	for (v = vs->punter; v < vs->punter +mida; v++)
		definir_variable (v, m_error, lloc);
}

void
variable_a_paraula (struct paraula *p, struct variables vs, char *m_error, int lloc, char *concret)
{
	int maxim;

	maxim = vs.mida;
	p->lloc.relatiu = llegir_digit_final_limitat_1 ( '\n', maxim, m_error, lloc, concret);

	p->descriptor = vs.punter[p->lloc.relatiu].descriptor;
	p->auxiliar.enter = 0;
}

void
funcio_a_paraula (struct paraula *p, char *m_error, int lloc, char *concret)
{
	p->lloc.relatiu = llegir_digit_final_1 ( '\n', m_error, lloc, concret );

	// No podem dir res, ja que encara no estan totes les funcions declarades!
	// TODO SYA tocarà definir aquests valors!
	p->descriptor.tipus = CapTipus;
	p->descriptor.vegades_punter = 0;
	p->auxiliar.enter = 0;
}

void
sistema_a_paraula ( struct paraula *p, struct llista_sistema l, char *m_error, int lloc, char *concret )
{
	p->lloc.relatiu = llegir_digit_final_limitat_1 ( '\n', l.mida, m_error, lloc, concret );
	p->descriptor = l.punter[p->lloc.relatiu].descriptor;
	p->auxiliar.enter = 0; // TODO l.punter[p->lloc.relatiu].arguments.mida;
}

void
retorn_a_paraula ( struct paraula *p, char *m_error, int lloc, char *concret)
{
	p->auxiliar.enter = llegir_digit_final_1 ( '\n', m_error, lloc, concret );

	p->lloc.relatiu = 0;
	p->descriptor.tipus = Int;
	p->descriptor.vegades_punter = 0;
}

void
definir_paraula (struct paraula *p, char *m_error, int lloc)
{
	struct variables vs;

	p->lloc.on = llegir_digit_final_limitat_comentari ( ' ', EndLocalitzacions, m_error, lloc, "Localitzacions, per més ajuda usi \"-hf\"." );

	switch (p->lloc.on)
	{
	case Codi:
		p->lloc.relatiu = 0;
		llegir_tipus_vegades_punter (' ', &p->descriptor, m_error, lloc, "Dir quin tipus és del codi.");
		p->auxiliar = definir_valor (p->descriptor, m_error, lloc, "Definint valor al codi.");
		break;

	case Arguments:
		vs = descriptors_funcio.punter[lloc].arguments;
		variable_a_paraula (p, vs, m_error, lloc, "Lloc relatiu de l'argument.");
		break;
	case Locals:
		vs = descriptors_funcio.punter[lloc].local;
		variable_a_paraula (p, vs, m_error, lloc, "Lloc relatiu de les variables.");
		break;
	case Globals:
		vs = variables_globals;
		variable_a_paraula (p, vs, m_error, lloc, "Llegint de les variables globals.");
		break;

	case Funcions:
		funcio_a_paraula (p, m_error, lloc, "Llegint relatiu de funcions d'usuari.");
		break;
	case Sistema:
		sistema_a_paraula (p,funcions_sistema, m_error, lloc, "Llegint relatiu de funcions de sistema.");
		break;
	case Retorn:
	case Retorn_final:
		retorn_a_paraula (p, m_error, lloc, "Llegint que retorna.");
		break;
	case Funcions_especials:
		sistema_a_paraula (p, funcions_especials_sistema, m_error, lloc, "Llegint funció especial.");
		break;
	default:
		error_procedencia (m_error, lloc, "Valor inesperat per localització. Més informació premi '-hf'.");
	}
}
/*
	struct localitzat lloc;	// Saber que fer al executar la paraula.
	union valor auxiliar;	// Comodí, per guardar diferents valors.
	struct descriptor descriptor;
	*/

void
definir_frase (struct frase *f, char *m_error, int lloc)
{
	int mida;
	struct paraula *p;

	llegir_inici_final_1 ('-', 'f', ':', m_error, lloc, "On \"-f[^:\\n]:\" és el missatge esperat.");

	f->mida = mida = llegir_digit_final_1 ( '\n', m_error, lloc, "On tot seguit ':' esperem: \"\\d+\\n\"" );
	f->punter = mida ? malloc ( mida * sizeof (struct frase) ) : NULL;

	for (p = f->punter; p < f->punter +mida; p++)
		definir_paraula (p, m_error, lloc);
}

void
definir_codi ( struct codi *c, char *m_error, int lloc)
{
	int mida;
	struct frase *f;

	llegir_inici_final_1 ('-', 'c', ':', m_error, lloc, "On \"-c[^:\\n]:\" és el missatge esperat.");

	c->mida = mida = llegir_digit_final_1 ( '\n', m_error, lloc, "On tot seguit ':' esperem: \"\\d+\\n\"" );
	c->punter = mida ? malloc ( mida * sizeof (struct frase) ) : NULL;

	for (f = c->punter; f < c->punter +mida; f++)
		definir_frase (f, m_error, lloc);
}

void
definir_funcio (struct descriptor_funcio *d, int lloc, char *m_error)
{
	char c;

	llegir_inici_final_1 ('<', 'F', ':', m_error, lloc, "On \"<F[^:\\n]:\" és el missatge esperat.");

	c = llegir_text_sense_espais_ni_intro (&g_v_s, &d->nom, m_error, lloc, "Volem el nom de la funció: \"[^ \n]*");
	c = llegir_tipus_vegades_punter (c, &d->descriptor, m_error, lloc, "Entrada: \\d*(tipus) \\d*(vegades punter).");
	d->mida_memoria_execucio = llegir_digit_final_1 ('\n', m_error, lloc, "Esperem \\d+ per reservar memòria d'execució.");

	definir_variables_i_declarar ('a', &d->arguments, "Declarant els arguments. -a:", lloc);
	definir_variables_i_declarar ('v', &d->local, "Declarant les variables locals. -v:", lloc);
	definir_codi (&d->codi, "Definint el codi de la funció.", lloc);
}

void
definir_funcions (char *m_error)
{
	int mida, lloc = -1;

	llegir_inici_final_1 ('-', 'f', ':', m_error, lloc, "On \"-f[^:\\n]:\" és el missatge esperat.");
	descriptors_funcio.mida = mida = llegir_digit_final_1 ( '\n', m_error, lloc, "On tot seguit ':' esperem \"\\d+\\n\"" );
	descriptors_funcio.punter = malloc ( mida * sizeof (struct descriptor_funcio) );

	for (lloc = 0; lloc < mida; lloc++)
		definir_funcio (descriptors_funcio.punter +lloc, lloc, "Definint la funció");
}

void
llegir_codi_objecte_v01 (char (*funcio) (void), enum lexic_v01 estat)
{
	descriu_lectura_1 (funcio);
	g_v_s = pila_inicialitzar (100, sizeof (char));

		definir_variables_i_declarar ('v', &variables_globals, "Declarant les variables globals. -v:", -1);
		definir_funcions ("Definint funcions");

	pila_alliberar (&g_v_s);
}
