all:
	g++ -I base -I src/include -L src/lib -o main main.cpp base/enemy/*.cpp base/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf
	./main.exe
