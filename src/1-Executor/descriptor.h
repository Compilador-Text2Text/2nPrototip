#ifndef DESCRIPTOR_PER_L_EXECUTOR_H_
#define DESCRIPTOR_PER_L_EXECUTOR_H_

#include <stdlib.h>

/**
 *
 * 0	No depen de ningú.
 * 0.0		Valor		{char, int, void*}
 * 0.1		Localitzacions	{Codi, Variables, Funció}
 * 0.2		Tipus		{Char, Int, Void}
 * 0.3		Sistema		Noms de funcions del sistema.
 * 0.4		numerador SYA	{Valor, Funció, Operador, …}
 * 0.5		Cert fals	Per saber si és verdader.
 *
 * 1	Amb dependències amb *0*.
 * 1.0		Localitzat	Saber on està.
 * 1.1		Variable	Guardar la seva informació.
 *	1.1.0	Variables	Llista de variables.
 * 1.2		ele. execució	On guardem els valors.
 *	1.2.0	mem. execució	Llista d'elements d'execució.
 *
 * 2	Amb dependències amb *1*.
 * 2.0		Paraula		Dades per poder executar.
 *	2.0.0	Frase		Llista de paraules.
 *	2.0.0.0	Codi		Llista de frases.
 *
 * 3	Amb dependències amb *2*.
 * 3.0		Descriptor de funció.
 *
 * 4	Amb dependències amb *3*.
 * 4.0		Funció dinàmica.
 *
 * 5	Amb dependències amb *4*.
 * 5.0		Funció de sistema.
 *
 **/

	/*0*	No depen de ningú.	*/
/*0.0* Serveix per a poder operar amb valors.			*/
// Usat: (1.1)variable, (1.2) ele. execució, (2.0)paraula.
union
valor
{
	char caracter;
	int enter;
	float flotant;
	void *punter;
};

/*0.1* Serveix per poder executar correctament la (2.0)paraula.	*/
// Usat: (1.0)localitzat.
// Localització_on_*
enum
localitzacions
{
	Codi,		// Les dades estan a la paraula.

	Arguments,	// Les dades estan a les variables d'arguments.
	Locals,		// Les dades estan a les variables locals.
	Globals,	// Les dades estan a les variables globals.

	Funcions,	// Creació d'una funció pròpia.
	Sistema,	// Funció pròpia del compilador.
	Retorn,		// Retorn del resultat d'una funció pròpia.
	Retorn_final,	// Retorn like exit.
	Funcions_especials,	// while, for, if.

	NoRetorn,	// Error, no queden frases.

	Preexecucio,

	EndLocalitzacions
};

/*0.2* Serveix per a poder saber amb que estem treballant.	*/
// Descriptor_tipus_*
enum
tipus
{
	CapTipus,

	Void,
	Char,
	Int,
	Float,
	Pointer,

	EndTipus
};

/*0.3* Serveix per a poder definir les funcions amb dígits.	*/
// Sistema_relatiu_*
enum
sistema
{
	Igual_general,
	Extreure_punter,

	Goto,	// Salt.
	GotoZ,	// Salt si és zero.
	GotoNZ,	// Salt si no és zero.

	End_sistema
};

// SYA_tipus_*
enum
funcions_sya
{
	Funcio,
	Asociativa_dreta,
	Asociativa_esquerra
};

// Pensat fer Preexecució_relatiu_*
// Perquè és de la preexecució, però és el apartat relatiu.
enum
pre_execucio
{
	Obert,				// (, {
	Tancat,				// ), }

	Coma,				// ,

// Funcions especials.
	While,
	End_While,
	For,
	End_For,
	If,
	Else_if,
	Else,
	End_if,

	End_preexecucio,
};

/*0.5* Serveix per a saber si ha passat o no.			*/
enum
cert_fals
{
	Fals		= 0,
	Cert		= 1
};
	/*1*	Dependència amb *0*.	*/
/*1.0* Saber exactament on està la informació.			*/
// Usat: (2.0)paraula.
struct
localitzat
{
	enum localitzacions on;
	size_t relatiu;
};

struct
estats_sya
{
	enum funcions_sya tipus_funcio;
	size_t precedencia; // Com més gran abans ho farà.
};

struct
descriptor
{
	enum tipus tipus;
	size_t vegades_punter;
};

/*1.1* Tota la informació necessària per a les variables.	*/
struct
variable
{
	char *nom;
	union valor valor;
	struct descriptor descriptor;
	enum cert_fals inicialitzat;
	enum cert_fals usat;
};

/*1.1.0* Llista de variables.					*/
// Usat: (3.0)descriptor de funció, (4.0)funció dinàmica.
struct
variables
{
	size_t mida;
	struct variable* punter;
};

/*1.2* Dades que seran usades per les funcions.			*/
// Usat: (4.0)funció dinàmica i (5.0)funció sistema.
struct
element_execucio
{
	union valor valor;
	struct descriptor descriptor;
	struct variable *punter;		// Per exemple a = 3, trobar a.
};

/*1.2.0* Per a poder passar més d'un argument a les funcions.	*/
// Usat: (4.0)funció dinàmica.
struct
memoria_execucio
{
	size_t mida;
	size_t us;
	struct element_execucio *punter;
};

struct
descriptor_argument
{
	size_t mida;
	struct descriptor *punter;
};
	/*2*	Dependència amb *1*.	*/
/*2.0* Tota la informació necessària per a ser executat.	*/
struct
paraula
{
	struct localitzat lloc;	// Saber que fer al executar la paraula.
	union valor auxiliar;	// Comodí, per guardar diferents valors.
	struct descriptor descriptor;
};

/*2.0.0* Llista de paraules.					*/
struct
frase
{
	size_t mida;
	struct paraula *punter;
};

/*2.0.0.0* Llista de frases.					*/
// Usat: (3.0)descriptor de funció.
struct
codi
{
	size_t mida;
	struct frase *punter;
};

	/*3*	Dependència amb *2*.	*/
/*3.0* Tota la informació que necessita una funció.		*/
// Usat: (4.0)funció dinàmica.
struct
descriptor_funcio
{
	char *nom;
	struct variables arguments;
	struct variables local;
	size_t mida_memoria_execucio;
	struct codi codi;
	struct descriptor descriptor;
};

	/*4*	Dependència amb *3*.	*/
/*4.0* Tota la informació d'una funció en execució.		*/
// Usat: (5.0)funció de sistema.
struct
funcio_dinamica
{
	struct element_execucio *punter_retorn;
	struct variables arguments;
	struct variables local;
	struct memoria_execucio memoria;
	// Contadors de punters. 1 canvia poc, 2 canvia molt.
	size_t cp1, cp2;
	struct descriptor_funcio *descriptor;
};

	/*5*	Dependència amb *4*.	*/
/*5.0* Tota la informació d'una funció de sistema.		*/
struct
funcio_sistema
{
	char *nom;
	int (*funcio) (size_t, struct element_execucio *, struct funcio_dinamica *);
	struct descriptor descriptor;
	// struct variables arguments; TODO, pendent!
};

/* Executar el codi */
extern struct variables variables_globals;
extern struct llista_descriptors
{
	size_t mida;
	struct descriptor_funcio *punter;
} descriptors_funcio;
extern struct llista_sistema
{
	size_t mida;
	struct funcio_sistema *punter;
} funcions_sistema, funcions_especials_sistema;

#endif // DESCRIPTOR_PER_L_EXECUTOR_H_
