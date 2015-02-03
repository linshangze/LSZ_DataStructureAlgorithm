#********************************************************************
 #author: Linshangze//林上泽
 #date: 2013-05-16
 #file name: makefile
#********************************************************************

#makefile for testLSZ_LinearListCL.c

#Define a macro name for compiler
CC = gcc
vpath %.c ../../LSZ_DataType
vpath %.h ../../LSZ_DataType

#macro
INCLUDE_PATH = ../../LSZ_DataType
SOURCES =  testLSZ_LinearListCL.c LSZ_DataType.c \
		   LSZ_LinearListCL.c
EXE = a.out
CFLAGS = -I$(INCLUDE_PATH) -Wall
OBJECTS =  $(patsubst %.c, %.o, $(SOURCES))
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

