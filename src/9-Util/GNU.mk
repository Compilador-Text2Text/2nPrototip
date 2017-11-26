FILE_UTILS = 9-Util
MK_UTILS = $(FILE_UTILS)/GNU.mk

# General
UTILS_O_		=		\
	$(UTILS_PILA_O_)		\
	$(UTILS_MEMORIA_O_)		\

# Vector.
UTILS_PILA_C_ = $(FILE_UTILS)/pila.c
UTILS_PILA_H_ = $(FILE_UTILS)/pila.h
UTILS_PILA_O_ = $(OBJDIR)/util_pila.o

# Memòria.
UTILS_MEMORIA_C_ = $(FILE_UTILS)/memoria.c
UTILS_MEMORIA_H_ = $(FILE_UTILS)/memoria.h
UTILS_MEMORIA_O_ = $(OBJDIR)/util_memoria.o
