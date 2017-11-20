FILE_EXECUTOR = 1-Executor
MK_EXECUTOR = $(FILE_EXECUTOR)/GNU.mk

# General.
EXECUTOR_C_	=			\
	$(EXECUTOR_EXECUTOR_C_)		\

EXECUTOR_H_	=			\
	$(EXECUTOR_EXECUTOR_H_)		\
	$(EXECUTOR_DESCRIPTOR_H_)	\

EXECUTOR_O_	=			\
	$(EXECUTOR_EXECUTOR_O_)		\
	$(EXECUTOR_INSTRUCIONS_O_)	\
	$(EXECUTOR_FUNCIO_O_)		\

# Dependencies al tenir la llibreria.
EXECUTOR_DESCRIPTOR_H_	=			\
	$(FILE_EXECUTOR)/descriptor.h		\

# Executor
EXECUTOR_EXECUTOR_C_	= $(FILE_EXECUTOR)/executor.c
EXECUTOR_EXECUTOR_H_	=			\
	$(FILE_EXECUTOR)/executor.h		\
	$(EXECUTOR_DESCRIPTOR_H_)		\

EXECUTOR_EXECUTOR_O_	= $(OBJDIR)/executor.o

# Instruccions
EXECUTOR_INSTRUCIONS_C_	= $(FILE_EXECUTOR)/instruccions.c
EXECUTOR_INSTRUCIONS_H_	= $(FILE_EXECUTOR)/instruccions.h
EXECUTOR_INSTRUCIONS_O_	= $(OBJDIR)/exec_instruccions.o

# Instruccions
EXECUTOR_FUNCIO_C_	= $(FILE_EXECUTOR)/punter-funció.c
EXECUTOR_FUNCIO_H_	= $(FILE_EXECUTOR)/punter-funció.h
EXECUTOR_FUNCIO_O_	= $(OBJDIR)/exec_funció.o
