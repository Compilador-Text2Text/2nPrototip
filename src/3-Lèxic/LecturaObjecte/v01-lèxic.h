#ifndef V01_LEXIC_H_
#define V01_LEXIC_H_

enum
lexic_v01
{
	l_v01_normal,
	l_v01_verbos
};

void llegir_codi_objecte_v01 (char (*funcio) (void), enum lexic_v01);

#endif // V01_LEXIC_H_
