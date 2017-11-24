#ifndef MAQUINA_ESTATS_V01_H_
#define MAQUINA_ESTATS_V01_H_

void descriu_lectura_1 (char (*) (void));

void error_final_1 (char *s);
void comprovacio_caracter_1 (char esperat, char *missatge_error_general, int quina_funcio, char*missatge_concret);

char llegir_linia_1 (char *missatge_error_general, char *missatge_concret);
void llegir_inici_final_1 (char inici, char final, char *missatge_error_general, int quina_funcio, char*missatge_concret);

#endif // MAQUINA_ESTATS_V01_H_
