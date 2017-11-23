#ifndef EXECUTOR_DEPURADOR_H_
#define EXECUTOR_DEPURADOR_H_

#include "../9-Util/pila.h"

void inicialitzar_depurador (void);
void finalitzar_depurador (void); // free

// Amb inicialització.
void mostra_localitzacions (void);
void mostra_tipus (void);
void mostra_sistema (void);

// Quan executa.
void mostra_memoria_execucio (struct pila *p);

#endif // EXECUTOR_DEPURADOR_H_
