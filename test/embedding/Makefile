#programs
CC = gcc
AR = ar
RANLIB = ranlib

#finetune
WREN_INCLUDE = -I../../src/include
WREN_LIBRARY = -static -L../../lib/ -lwren -lm

CFLAGS = -Wall -Wextra 
LDFLAGS = 

#main target
all: main

#know-how
libdummy.o: dummy.c dummy.h
main.o: main.c dummy.h

#recipies
main: main.o libdummy.a
	@echo LD $@
	@$(CC) $(LDFLAGS) -o $@ $^ -L. $(WREN_LIBRARY) -Wno-unused-parameter

libdummy.a: dummy.o
	@echo AR $@
	@$(AR) cr  $@ $< && \
	$(RANLIB) $@

#generics
%.o: %.c
	@echo CC $@
	@$(CC) $(CFLAGS) -o $@ -c $< -I. $(WREN_INCLUDE)

.PHONY: clean

clean:
	@echo cleaning
	@rm -rf main.o libdummy.a main
