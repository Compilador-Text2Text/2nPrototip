#include "0-Inicialitzador/v00.h"

int main (int argc, char *argv[])
{
	int out;
	out = inicialitzador_lectura_objecte ("hola");
	finalitza_allibera_memoria ();
	return out;
}
