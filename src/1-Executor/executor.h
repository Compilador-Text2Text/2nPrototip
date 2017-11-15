#ifndef EXECUTOR_H_
#define EXECUTOR_H_

#include "descriptor.h"

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
} funcions_sistema;

#endif // EXECUTOR_H_
