#specify routes for two executable

#name of executable
TARG = test

#specify compiler and flags
CC = g++
GEN_OPTS = -Wall
GEN_OPTS2  = -c
GEN_OPTS3 = -fpic
LIBS = -lsanpa
LIBS_E = -Lbin/static
LIBS_S = -Lbin/shared

#creating the target, not always needed
#static: bin/static/libsampa.a bin/static/class1.o
#	ar rcs bin/static/libsampa.a bin/static/class1.o

all: $(TARG)

$(TARG): src/main.o bin/static/libsanpa.a bin/shared/libunsa.dll
	$(CC) $< -Lbin/static -lsanpa  -Lbin/shared -lunsa -o $(TARG)

src/main.o: src/main.cpp
	$(CC) $(GEN_OPTS) -Werror $(GEN_OPTS2) $< -o $@

bin/static/libsanpa.a: bin/static/sanpa.o
	ar rcs $@ $<

bin/shared/libunsa.dll: bin/shared/unsa.o
	$(CC) -shared $< -o $@

bin/shared/unsa.o: src/unsa/unsa.cpp
	$(CC) $(GEN_OPTS2) $(GEN_OPTS) -Werror $(GEN_OPTS3) $< -o $@

bin/static/sanpa.o: src/sanpa/class1.cpp
	$(CC) $(GEN_OPTS2) $< -o $@

clean:
	rm -f $(TARG) src/main.o bin/shared/libunsa.dll bin/shared/unsa.o bin/static/libsanpa.a bin/static/sanpa.o
