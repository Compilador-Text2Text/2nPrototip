include Executor/GNU.mk
include Lèxic/GNU.mk

CLEAN = clean
DEPURAR = dm h	# deprar manual
OBJDIR = ../Bin
ALL = $(OBJECT)
HEAD =				\

OBJECT =			\
	$(EXECUTOR_EXECUTOR_O_)	\

# Comprovar que els caps són correctes
#head: $(HEAD)
#	@echo Capçalera activada: $(HEAD)

# 4.3 Types of Prerequisites
# Fa que el directori sigui prioritari.
$(ALL): | $(OBJDIR)
$(EXECUTOR_H_): | $(MK_EXECUTOR)

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
# Executor
	@printf "\nEXECUTOR\nMK_EXECUTOR: %s\n" $(MK_EXECUTOR)
	@printf "EXECUTOR_H_: %s\n" $(EXECUTOR_H_)
	@printf "EXECUTOR_DESCRIPTOR_H_: %s\n" $(EXECUTOR_DESCRIPTOR_H_)
	@printf "EXECUTOR_EXECUTOR_H_: %s\n" $(EXECUTOR_EXECUTOR_H_)
	@printf "EXECUTOR_EXECUTOR_O_: %s\n" $(EXECUTOR_EXECUTOR_O_)
# Lèxic
	@printf "\nLÈXIC\n"
	@printf "MK_LEXIC: %s\n" $(MK_LEXIC)


####################     EXECUTOR     ####################

$(CLEAN):
	rm $(OBJDIR)/* -f

.PHONY: $(CLEAN) $(DEPURAR)
