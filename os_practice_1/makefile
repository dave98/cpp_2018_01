#specify all source files here
SRCS = main.cpp h1.cpp
SRCS2 = sanpa.cpp

#name of executable
TARG = soft

#speficy compiler and flags
CC = g++
OPTS = -Wall -O
OPTS2 = -fPIC -shared
LIBS = -ldl

#translate .c files in source list of .os
OBJS = $(SRCS:.cpp=.o)
OBJS2 =$(SRCS2:.cpp=.dll)

#generate the target, not always nedeed
all: $(TARG)

#gtenerate the executable
$(TARG): $(OBJS) $(OBJS2)
	$(CC) -o $(TARG) $(OBJS) $(OBJS2) $(LIBS)

#generate .o files
%.o: %.c
	$(CC) $(OPTS)	-c $< -o $@

#generate a dynamic library
sanpa.dll: sanpa.cpp
	$(CC) $(OPTS2) $< -o $@

#clean line
clean:
	rm -f $(OBJS) $(OBJS2) $(TARG)
