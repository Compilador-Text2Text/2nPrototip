FILE_SISTEM = 2-Funció-de-sistema
MK_SISTEM = $(FILE_SISTEM)

# General
SISTEM_C_	=			\
	$(SISTEM_FUNCION_C_)		\
	$(SISTEM_INIT_C_)		\

SISTEM_H_	=			\
	$(SISTEM_FUNCION_H_)		\
	$(SISTEM_INIT_H_)		\

SISTEM_O_	=			\
	$(SISTEM_FUNCION_O_)		\
	$(SISTEM_INIT_O_)		\

# Funcions
SISTEM_FUNCION_C_	= $(FILE_SISTEM)/funcions.c
SISTEM_FUNCION_O_	= $(OBJDIR)/funcions.o
SISTEM_FUNCION_H_	= 		\
	$(FILE_SISTEM)/funcions.h	\
	$(EXECUTOR_DESCRIPTOR_H_)	\

# Inicialitzador
SISTEM_INIT_C_		= $(FILE_SISTEM)/inicialitzador.c
SISTEM_INIT_O_		= $(OBJDIR)/system_init.o
SISTEM_INIT_H_		= $(FILE_SISTEM)/inicialitzador.h
