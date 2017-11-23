FILE_OBJECTE = $(FILE_LEXIC)/LecturaObjecte
MK_OBJECTE = $(FILE_OBJECTE)/GNU.mk

# General.
OBJECTE_O_		=		\
	$(LEXIC_V00_O_)			\
	$(LEXIC_V01_O_)			\
	$(LEXIC_ESTATS_O_)		\

# Versió 0.
LEXIC_V00_C_ = $(FILE_OBJECTE)/v00-lèxic.c
LEXIC_V00_H_ = $(FILE_OBJECTE)/v00-lèxic.h
LEXIC_V00_O_ = $(OBJDIR)/lexic_obj_v00.o

# Versió 1.
LEXIC_V01_C_ = $(FILE_OBJECTE)/v01-lèxic.c
LEXIC_V01_H_ = $(FILE_OBJECTE)/v01-lèxic.h
LEXIC_V01_O_ = $(OBJDIR)/lexic_obj_v01.o

# Maquina d'estats.
LEXIC_ESTATS_C_ = $(FILE_OBJECTE)/maquina_estats.c
LEXIC_ESTATS_H_ = $(FILE_OBJECTE)/maquina_estats.h
LEXIC_ESTATS_O_ = $(OBJDIR)/maquina_estats.o
