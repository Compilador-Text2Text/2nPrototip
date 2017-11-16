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

# Dependencies al tenir la llibreria.
EXECUTOR_DESCRIPTOR_H_	=			\
	$(FILE_EXECUTOR)/descriptor.h		\

# Executor
EXECUTOR_EXECUTOR_C_	= $(FILE_EXECUTOR)/executor.c
EXECUTOR_EXECUTOR_H_	=			\
	$(FILE_EXECUTOR)/executor.h		\
	$(EXECUTOR_DESCRIPTOR_H_)		\

EXECUTOR_EXECUTOR_O_	= $(OBJDIR)/executor.o
