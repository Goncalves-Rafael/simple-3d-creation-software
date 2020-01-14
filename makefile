LIBS=-lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
INCLUDE=include/
SRC=src
BUILD=build
EXE=
BIN=bin
OBJ=.o

run: $(BUILD)/main$(EXE)
	./$(BUILD)/main$(EXE)

$(BUILD)/main: $(SRC)/main.cpp $(BIN)/project$(OBJ) $(BIN)/glad$(OBJ)
	g++ -std=c++11 -o $(BUILD)/main$(EXE) $(SRC)/main.cpp $(wildcard $(BIN)/*.o) -I $(INCLUDE) $(LIBS)

$(BIN)/project$(OBJ): $(SRC)/project.cpp $(BIN)/object$(OBJ) $(BIN)/renderer$(OBJ) $(BIN)/texture$(OBJ) $(BIN)/camera$(OBJ)
	g++ -std=c++11 -c $(SRC)/project.cpp -I $(INCLUDE) -o $(BIN)/project$(OBJ)

$(BIN)/camera$(OBJ): $(SRC)/camera.cpp
	g++ -std=c++11 -c $(SRC)/camera.cpp -I $(INCLUDE) -o $(BIN)/camera$(OBJ)

$(BIN)/renderer$(OBJ): $(SRC)/renderer.cpp $(BIN)/program$(OBJ) $(BIN)/object$(OBJ)
	g++ -std=c++11 -c $(SRC)/renderer.cpp -I $(INCLUDE) -o $(BIN)/renderer$(OBJ)

$(BIN)/program$(OBJ): $(SRC)/program.cpp $(BIN)/shader$(OBJ) $(BIN)/texture$(OBJ)
	g++ -std=c++11 -c $(SRC)/program.cpp -I $(INCLUDE) -o $(BIN)/program$(OBJ)

$(BIN)/shader$(OBJ): $(SRC)/shader.cpp
	g++ -std=c++11 -c $(SRC)/shader.cpp -I $(INCLUDE) -o $(BIN)/shader$(OBJ)

$(BIN)/object$(OBJ): $(SRC)/object.cpp
	g++ -std=c++11 -c $(SRC)/object.cpp -I $(INCLUDE) -o $(BIN)/object$(OBJ)

$(BIN)/texture$(OBJ): $(SRC)/texture.cpp $(BIN)/stb_image$(OBJ)
	g++ -std=c++11 -c $(SRC)/texture.cpp -I $(INCLUDE) -o $(BIN)/texture$(OBJ)

$(BIN)/stb_image$(OBJ): $(SRC)/stb_image.cpp
	g++ -std=c++11 -c $(SRC)/stb_image.cpp -I $(INCLUDE) -o $(BIN)/stb_image$(OBJ)

$(BIN)/glad$(OBJ): $(SRC)/glad.c
	g++ -std=c++11 -c $(SRC)/glad.c $(LIBS) -o $(BIN)/glad$(OBJ)

clean:
	rm -rf build/*$(EXE) *~
	rm -rf bin/*$(OBJ) *~
