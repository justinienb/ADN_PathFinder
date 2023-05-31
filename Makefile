SRC = src/*.c
BIN = bin/pathfinder.exe
CFLAGS = -Wall -Wextra
INCLUDE = -Iinclude -Ilib/SDL2-2.0.22/x86_64-w64-mingw32/include
LDFLAGS = -Llib/SDL2-2.0.22/x86_64-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2

all :
	gcc $(SRC) -o $(BIN) $(CFLAGS) $(INCLUDE) $(LDFLAGS)

clean :
	rm bin/*.exe