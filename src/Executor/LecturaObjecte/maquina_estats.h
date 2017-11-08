#ifndef MAQUINA_ESTATS_H_
#define MAQUINA_ESTATS_H_

void descriu_lectura (char (*) (void));

char llegir_linia (void);
int llegir_inici_final (char i, char f);
int llegir_digit_final ( char f );
int llegir_digit_final_comenzat (char c, char f);

#endif // MAQUINA_ESTATS_H_
