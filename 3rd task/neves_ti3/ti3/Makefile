# Compilation flags
CFLAGS=-c  -DDEBUG_CACHE -Iinclude -I. -g

# .c files
CAOSS_SOURCES=$(wildcard src/caoss/*.c)
CAAS_SOURCES=$(wildcard src/caas/*.c) src/caoss/utils.c

# .h files
HEADERS=$(wildcard include/*.h)

# Object files
CAOSS_OBJS=$(CAOSS_SOURCES:.c=.o)
CAAS_OBJS=$(CAAS_SOURCES:.c=.o)

all: caoss

caas_parser.c caas_parser.h: src/caas/caas.y
	bison -t -v -d -o caas_parser.c  src/caas/caas.y

caas_lexer.c: src/caas/caas.l caas_parser.h
	flex src/caas/caas.l

caas: caas_parser.o caas_lexer.o $(CAAS_OBJS)
	cc -o $@ $^
#	make clean_caas

caoss: $(CAOSS_OBJS)
	cc -o $@ $^

%.o: %.c %.h
	cc -o $@ $< $(CFLAGS)

cleanall: clean
	rm -f caas caoss

clean:
	rm -f *.output caas_lexer.* caas_parser.* $(CAOSS_OBJS) $(CAAS_OBJS)

.PHONY: all clean
