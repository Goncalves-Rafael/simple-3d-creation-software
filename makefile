LIBS=-lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
INCLUDE=include/
SRC=src
BUILD=build
EXE=
BIN=bin
OBJ=.o

run: $(BUILD)/main$(EXE)
	./$(BUILD)/main$(EXE)

$(BUILD)/main$(EXTENSION): $(SRC)/main.cpp $(BIN)/program $(BIN)/glad
	g++ -std=c++11 -o $(BUILD)/main$(EXE) $(SRC)/main.cpp $(wildcard $(BIN)/*.o) -I $(INCLUDE) $(LIBS)

$(BIN)/program: $(SRC)/program.cpp $(BIN)/shader
	g++ -std=c++11 -c $(SRC)/program.cpp -I $(INCLUDE) -o $(BIN)/program$(OBJ)

$(BIN)/shader: $(SRC)/shader.cpp
	g++ -std=c++11 -c $(SRC)/shader.cpp -I $(INCLUDE) -o $(BIN)/shader$(OBJ)

$(BIN)/glad:
	g++ -std=c++11 -c $(SRC)/glad.c $(LIBS) -o $(BIN)/glad$(OBJ)

clean:
	rm -rf build/*$(EXE) *~
	rm -rf bin/*$(OBJ) *~

clean_run: clean run
