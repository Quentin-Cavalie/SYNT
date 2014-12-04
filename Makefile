SRC=src/*.cpp
EXE=particleEngine
INCS=-I "/home/quentin/EPITA/PROJETS/SYNT/inc"
LIBS=-lm -lSOIL -lGL -lGLU -lglut
LDIR=-L/usr/lib/nvidia-340
CFLAGS=-Wall -std=c++0x -g
CC=g++

all: $(EXE)

$(EXE): $(SRC)
	$(CC) ${CFLAGS} $(SRC) $(INCS) -o $(EXE) ${LDIR} ${LIBS}

clean:
	rm -f $(EXE)