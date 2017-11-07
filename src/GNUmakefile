include Executor/GNU.mk

CLEAN = clean
FORCE_COMPILE = force
OBJDIR = Bin
ALL = $(HEAD) $(CLEAN)
HEAD =			\
       $(HEAD_EXECUTOR)	\

# Comprovar que els caps són correctes
#head: $(HEAD)
#	@echo Capçalera activada: $(HEAD)

# 4.3 Types of Prerequisites
# Fa que el directori sigui prioritari.
$(ALL): | $(OBJDIR)

$(FORCE_COMPILE): $(CLEAN) $(ALL)

$(OBJDIR):
	mkdir $(OBJDIR)

####################     EXECUTOR     ####################
$(OBJDIR)/descriptor.h.gch: Executor/descriptor.h $(MK_EXECUTOR)
	gcc Executor/descriptor.h -o $(OBJDIR)/descriptor.h.gch

$(CLEAN):
	rm $(OBJDIR)/* -f

.PHONY: head $(CLEAN)
