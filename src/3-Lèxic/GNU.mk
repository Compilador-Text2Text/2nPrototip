FILE_LEXIC = 3-Lèxic
include $(FILE_LEXIC)/LecturaObjecte/GNU.mk

MK_LEXIC	=			\
	$(FILE_LEXIC)/GNU.mk		\
	$(MK_LEXIC_LECTURA_OBJECTE)	\

# General.
LEXIC_O_	=			\
	$(OBJECTE_O_)			\
