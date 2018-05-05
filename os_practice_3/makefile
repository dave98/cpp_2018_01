TARG1 = signal.exe
TARG2 = reader.exe
TARG3 = writer.exe
TARG4 = sh_reader.exe
TARG5 = queue.exe

CC = g++


all: $(TARG1) $(TARG2) $(TARG3) $(TARG4) $(TARG5)

$(TARG1): send_signal/src/main.cpp
	$(CC) $< -o $@

$(TARG2): signal/src/reader.cpp
	$(CC) $< -o $@

$(TARG3): signal/src/writer.cpp
	$(CC) $< -o $@

$(TARG4): sh_reader/src/main.cpp
	$(CC) $< -o $@

$(TARG5): queue/src/main.cpp
	$(CC) $< -o $@


clean:
	rm -f $(TARG1) $(TARG2) $(TARG3) $(TARG4) $(TARG5)
