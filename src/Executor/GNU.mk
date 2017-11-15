MK_EXECUTOR = Executor/GNU.mk

EXECUTOR_H_ =				\
	$(EXECUTOR_DESCRIPTOR_H_)	\
	$(EXECUTOR_EXECUTOR_H_)		\

# Dependencies al tenir la llibreria.
EXECUTOR_DESCRIPTOR_H_	=		\
	Executor/descriptor.h		\

EXECUTOR_EXECUTOR_H_	=		\
	Executor/executor.h		\
	$(EXECUTOR_DESCRIPTOR_H_)	\

EXECUTOR_EXECUTOR_O_	=		\
	Executor/executor.c		\
	$(EXECUTOR_EXECUTOR_H_)		\
