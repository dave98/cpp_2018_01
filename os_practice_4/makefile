TARG1 = sh_writer
TARG2 = sh_reader
TARG3 = queue
CC = g++


all: $(TARG1) $(TARG2) $(TARG3)

$(TARG1): src/sh_writer_1.cpp
	$(CC) $< -o $@

$(TARG2): src/sh_reader_2.cpp
	$(CC) $< -o $@

$(TARG3): src/queue_3.cpp
	$(CC) $< -o $@
