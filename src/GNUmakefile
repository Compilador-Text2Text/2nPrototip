include 0-Inicialitzador/GNU.mk
include 1-Executor/GNU.mk
include 2-Funció-de-sistema/GNU.mk
include 3-Lèxic/GNU.mk
include 6-Depurador/GNU.mk
include 9-Util/GNU.mk

CLEAN	= clean
DEPURAR	= dm h	# deprar manual
OBJDIR	= ../Bin
LIBS	= -g -Wall
GLIBS	= -c $(LIBS)
MK_INTERPRET = GNUmakefile

all: $(CLEAN) $(OBJDIR)/interpret

ALL	=			\
	$(OBJECT) $(MK)		\
	$(MK_ALL)		\

HEAD	=			\
	$(INICIALITZADOR_H_)	\

# Tots els *.o
OBJECT =			\
	$(OBJDIR)/main.o	\
	$(INICIALITZADOR_O_)	\
	$(EXECUTOR_O_)		\
	$(SISTEM_O_)		\
	$(LEXIC_O_)		\
	$(DEPURADOR_O_)		\
	$(UTILS_O_)		\

MK_ALL =			\
	$(MK_INTERPRET)		\
	$(MK_INICIALITZADOR)	\


# Comprovar que els caps són correctes
#head: $(HEAD)
#	@echo Capçalera activada: $(HEAD)

# 4.3 Types of Prerequisites
# Fa que el directori sigui prioritari.
$(ALL): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(DEPURAR):
# General
	@printf "CLEAN: %s\n" $(CLEAN)
	@printf "DEPURAR: %s\n" $(DEPURAR)
	@printf "OBJDIR: %s\n" $(OBJDIR)
	@printf "ALL: %s\n" $(ALL)
	@printf "OBJECT: %s\n" $(OBJECT)
	@printf "HEAD: %s\n" $(HEAD)
# Inicialitzador
	@printf "\nINICIALITZADOR\n"
	@printf "Init: %s\n" $(FILE_INICIALITZADOR)
# Executor
	@printf "\nEXECUTOR\nMK_EXECUTOR: %s\n" $(MK_EXECUTOR)
	@printf "EXECUTOR_H_: %s\n" $(EXECUTOR_H_)
	@printf "EXECUTOR_DESCRIPTOR_H_: %s\n" $(EXECUTOR_DESCRIPTOR_H_)
	@printf "EXECUTOR_EXECUTOR_H_: %s\n" $(EXECUTOR_EXECUTOR_H_)
	@printf "EXECUTOR_EXECUTOR_O_: %s\n" $(EXECUTOR_EXECUTOR_O_)
# Sistema
	@printf "\nSISTEMA\n"
	@printf "SISTEM_INIT_C_: %s\n" $(SISTEM_INIT_C_)
	@printf "SISTEM_INIT_H_: %s\n" $(SISTEM_INIT_H_)
	@printf "SISTEM_INIT_O_: %s\n" $(SISTEM_INIT_O_)
# Lèxic
	@printf "\nLÈXIC\n"
	@printf "MK_LEXIC: %s\n" $(MK_LEXIC)
# Objecte
	@printf "\nObjecte\n"
	@printf "MK_OBJECTE: %s\n" $(MK_OBJECTE)
	echo $(MK_OBJECTE)


####################     Inicialitzador     ####################
$(INICIALIRZADOR_O_V00): $(INICIALIRZADOR_C_V00) $(SISTEM_INIT_H_) $(DEPURADOR_DEPURADOR_H_) $(LEXIC_V00_H_)# $(MK_INICIALITZADOR) $(MK_INTERPRET)
	gcc $(INICIALIRZADOR_C_V00) $(GLIBS) -o $(INICIALIRZADOR_O_V00)

$(INICIALITZADOR_ALLIBERAR_O_): $(INICIALITZADOR_ALLIBERAR_C_)
	gcc $(INICIALITZADOR_ALLIBERAR_C_) $(GLIBS) -o $(INICIALITZADOR_ALLIBERAR_O_)

####################     Executor     ####################
$(EXECUTOR_EXECUTOR_O_): $(EXECUTOR_EXECUTOR_C_) $(EXECUTOR_EXECUTOR_H_) # $(MK_INICIALITZADOR) $(MK_INTERPRET)
	gcc $(EXECUTOR_EXECUTOR_C_) $(GLIBS) -o $(EXECUTOR_EXECUTOR_O_)

$(EXECUTOR_INSTRUCIONS_O_): $(EXECUTOR_INSTRUCIONS_C_)
	gcc $(EXECUTOR_INSTRUCIONS_C_) $(GLIBS) -o $(EXECUTOR_INSTRUCIONS_O_)

$(EXECUTOR_FUNCIO_O_): $(EXECUTOR_FUNCIO_C_)
	gcc $(EXECUTOR_FUNCIO_C_) $(GLIBS) -o $(EXECUTOR_FUNCIO_O_)

####################     Sistem     ####################
$(SISTEM_FUNCION_O_): $(SISTEM_FUNCION_C_) $(SISTEM_FUNCION_H_)
	gcc $(SISTEM_FUNCION_C_) $(GLIBS) -o $(SISTEM_FUNCION_O_)

$(SISTEM_INIT_O_): $(SISTEM_INIT_C_) $(SISTEM_FUNCION_H_) $(EXECUTOR_EXECUTOR_H_)
	gcc $(SISTEM_INIT_C_) $(GLIBS) -o $(SISTEM_INIT_O_)

####################     Lèxic     ####################
$(LEXIC_V00_O_): $(LEXIC_V00_C_) $(EXECUTOR_EXECUTOR_H_)
	gcc $(LEXIC_V00_C_) $(GLIBS) -o $(LEXIC_V00_O_)

$(LEXIC_ESTATS_O_): $(LEXIC_ESTATS_C_) $(UTILS_PILA_H_)
	gcc $(LEXIC_ESTATS_C_) $(GLIBS) -o $(LEXIC_ESTATS_O_)

####################     Interpret     ####################
$(OBJDIR)/main.o: main.c # $(MK_INTERPRET)
	gcc main.c $(GLIBS) -o $(OBJDIR)/main.o

$(OBJDIR)/interpret: $(OBJECT) # $(MK_ALL)
	gcc $(OBJECT) $(LIBS) -o $(OBJDIR)/interpret

####################     Depurador     ####################
$(DEPURADOR_DEPURADOR_O_): $(DEPURADOR_DEPURADOR_C_) $(EXECUTOR_EXECUTOR_H_)
	gcc $(DEPURADOR_DEPURADOR_C_) $(GLIBS) -o $(DEPURADOR_DEPURADOR_O_)

####################     Útils     ####################
$(UTILS_PILA_O_): $(UTILS_PILA_C_)
	gcc $(UTILS_PILA_C_) $(GLIBS) -o $(UTILS_PILA_O_)

$(CLEAN):
	rm $(OBJDIR)/* -f

.PHONY: $(CLEAN) $(DEPURAR) all
