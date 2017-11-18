FILE_UTILS = 9-Util
MK_UTILS = $(FILE_UTILS)/GNU.mk

# General
UTILS_O_		=		\
	$(UTILS_VECTOR_O_)		\

# Vector.
UTILS_VECTOR_C_ = $(FILE_UTILS)/vector.c
UTILS_VECTOR_H_ = $(FILE_UTILS)/vector.h
UTILS_VECTOR_O_ = $(OBJDIR)/util_vector.o
