CPP 	= g++
LD 		= g++

CPPFLAGS= -Wall

OBJ = main.o carteira.o mercado.o moeda.o

BIN = main

all: $(BIN)

.cpp.o:
	$(CPP) $(CPPFLAGS) -c $<

$(BIN): $(OBJ)
	$(LD) -o $@ $(OBJ)

clean:
	del /Q /F $(OBJ) main.exe