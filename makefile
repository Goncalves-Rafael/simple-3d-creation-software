LIBS=-lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
INCLUDE=usr/local/include
SRC=src
BUILD=build
EXTENSION=

run: $(BUILD)/main$(EXTENSION)
	./$(BUILD)/main$(EXTENSION)

$(BUILD)/main$(EXTENSION): $(SRC)/main.cpp
	g++ -std=c++11 -o $(BUILD)/main$(EXTENSION) $(SRC)/main.cpp  $(SRC)/glad.c $(LIBS)

clean:
	rm -rf src/*$(EXTENSION) *~
	rm -rf build/*$(EXTENSION) *~

clean_run: clean run
