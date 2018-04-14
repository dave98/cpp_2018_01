#specify routes for two executable

#name of executable
TARG = static_test
TARG2 = dynamic_test

#specify compiler and flags
CC = g++
GEN_OPTS = -Wall
GEN_OPTS2  = -c
LIBS = -lsanpa
LIBS_E = -Lbin/static
LIBS_S = -Lbin/shared

#creating the target, not always needed
#static: bin/static/libsampa.a bin/static/class1.o
#	ar rcs bin/static/libsampa.a bin/static/class1.o

all: main1 main2

main1:
	$(CC) bin/main.o $(LIBS_E) $(LIBS) -o $(TARG)

main2:
	$(CC) bin/main.o $(LIBS_S) $(LIBS) -o $(TARG2)

clean:
	rm -f $(TARG) $(TARG2)
