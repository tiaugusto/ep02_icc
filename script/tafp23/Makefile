# PROGRAMA
PROG    = resolveEDO
OBJS    = resolveEDO.o edo.o utils.o

# Usa a variável de ambiente LIKWID_HOME (definida no bashrc)
# para localizar include e lib do LIKWID
LIKWID_HOME     ?= /home/soft/likwid
LIKWID_INCLUDE  = $(LIKWID_HOME)/include
LIKWID_LIB      = $(LIKWID_HOME)/lib

# Compilador
CC      = gcc

# Flags de compilação e linkagem
CFLAGS  = -O0 -DLIKWID_PERFMON -I$(LIKWID_INCLUDE)
LFLAGS  = -lm -L$(LIKWID_LIB) -llikwid

DISTFILES = *.c *.h LEIAME* Makefile edos.dat
DISTDIR   = ${USER}

.PHONY: clean purge dist all

%.o: %.c %.h utils.h
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

clean:
	@echo "Limpando sujeira ..."
	@rm -f *~ *.bak

purge: clean
	@echo "Limpando tudo ..."
	@rm -f $(PROG) $(OBJS) core a.out $(DISTDIR) $(DISTDIR).tgz

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tgz) ..."
	@ln -s . $(DISTDIR)
	@tar -chvzf $(DISTDIR).tgz $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)
