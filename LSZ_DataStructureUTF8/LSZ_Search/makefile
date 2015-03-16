#********************************************************************
 #author: Linshangze//林上泽
 #date: 2015-01-22
 #file name: makefile
#********************************************************************

#makefile for testLSZ_Search.c

#Define a macro name for compiler
CC = gcc
vpath %.c .
vpath %.h .

#macro
INCLUDE_PATH = .
SOURCES = testLSZ_Search.c \
		  LSZ_SearchStatic.c \
		  LSZ_SearchDynamicBST.c \
		  LSZ_SearchDynamicBSBT.c \
		  LSZ_SearchDynamicB_T.c \
		  LSZ_SearchUtility.c
EXE = a.out
CFLAGS = -I$(INCLUDE_PATH) -Wall
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

