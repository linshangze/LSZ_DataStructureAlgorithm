#********************************************************************
 #author: Linshangze//林上泽
 #data: 2013-05-24
 #file name: makefile
#********************************************************************

#makefile for testLSZ_TreeLBinary.c

#Define a macro name for compiler
CC = gcc
vpath %.c ../../LSZ_DataType:../../LSZ_Stack:../../LSZ_Queue
vpath %.h ../../LSZ_DataType:../../LSZ_Stack:../../LSZ_Queue

#macro
INCLUDE_PATH = .
SOURCES = testLSZ_TreeLBinary.c LSZ_TreeLBinary.c \
	LSZ_DataType.c LSZ_Stack.c LSZ_Queue.c
EXE = a.out
CFLAGS = -g -I$(INCLUDE_PATH) -Wall
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))
LOOK = ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#.SILENT:
.PHONY: finish
finish: $(EXE)
#	make clean;
	@echo $(LOOK);
	@./$(EXE) |less;
#	-rm $(EXE)
%.d: %.c
	set -e; rm -f $@; \
	$(CC) -MM $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@: ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$
sinclude $(SOURCES:.c=.d)
$(EXE): $(OBJECTS)
	$(CC) $(OBJECTS)
.PHONY: clean
clean:
	-rm -f $(OBJECTS)
	-rm -f $(SOURCES:.c=.d)

