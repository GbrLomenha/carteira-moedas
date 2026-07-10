##para linux usar no clean #rm -f $(OBJ) $(BIN)
CPP = g++
LD = g++
CPPFLAGS = -Wall #talvez colocar -std=c++11
OBJ = main.o carteira.o mercado.o moeda.o 
BIN = programa
all: $(BIN)
.cpp.o:
	$(CPP) $(CPPFLAGS) -c $<
$(BIN): $(OBJ)
	$(LD) -o $@ $(OBJ)
clean:
	del *.o
	del $(BIN).exe