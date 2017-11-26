#ifndef MAQUINA_ESTATS_V01_H_
#define MAQUINA_ESTATS_V01_H_

#include "../../9-Util/pila.h"

void descriu_lectura_1 (char (*) (void));

void error_procedencia (char*general, int lloc, char*concret);
/*
void comprovacio_caracter_1 (char esperat, char *missatge_error_general, int quina_funcio, char*missatge_concret);
char llegir_linia_1 (char *missatge_error_general, char *missatge_concret);
*/
void comprovacio_caracter_amb_2 (char esperat, char entrat, char *general, int lloc, char*concret);

void llegir_inici_final_1 (char p, char s, char f, char *missatge_error_general, int quina_funcio, char*missatge_concret); 

int llegir_digit (char *d, char *general, int lloc, char *concret);
int llegir_digit_final_1 (char c, char *missatge_error, int funcio, char *missatge_concret);
int llegir_digit_final_limitat_1 ( char f, int maxim, char*general, int lloc, char*concret );
int llegir_digit_final_limitat_comentari ( char f, int maxim, char *general, int lloc, char *concret );

int llegir_digit_pos_neg (char *general, int lloc, char *concret);
float llegir_digit_float (char *c, char *general, int lloc, char *concret);

char llegir_text_sense_espais_ni_intro (struct pila *p, char **s, char*general, int lloc, char*concret);
char* llegir_text (struct pila *p, char*general, int lloc, char*concret);

char llegir_caracter_facil (char *general, int lloc, char *concret);
#endif // MAQUINA_ESTATS_V01_H_
