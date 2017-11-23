#ifndef MAQUINA_ESTATS_H_
#define MAQUINA_ESTATS_H_

#include "../../9-Util/pila.h"

void descriu_lectura (char (*) (void));

void error (char *s);
void comprovacio_caracter (char c, char f);

char llegir_linia (void);
int llegir_inici_final (char i, char f);
int llegir_digit_final ( char f );
int llegir_digit_final_comenzat (char c, char f);

char llegir_text_sense_espais_ni_enters (struct pila *v, char **ps);

// V01 amb missatges d'errors.
void comprovacio_caracter_1 (char esperat, char *missatge_error_general, int quina_funcio, char*missatge_concret);
void llegir_inici_final_1 (char inici, char final, char *missatge_error_general, int quina_funcio, char*missatge_concret);

#endif // MAQUINA_ESTATS_H_
