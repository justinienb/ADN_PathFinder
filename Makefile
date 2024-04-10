SRC = src/*.c
BIN = bin/pathfinder.exe
CFLAGS = -g -Wall -Wextra -ffast-math
INCLUDE = -Iinclude -Ilib/SDL2-2.0.22/x86_64-w64-mingw32/include
LDFLAGS = -Llib/SDL2-2.0.22/x86_64-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

all :
	gcc $(SRC) -o $(BIN) $(CFLAGS) $(INCLUDE) $(LDFLAGS)

clean :
	rm bin/*.exe