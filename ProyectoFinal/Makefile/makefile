CXX=g++
CXXFLAGS=-std=c++17-Wall-Iinclude

SRC_DIR=src
OBJ_DIR=build
BIN_DIR=.
DATA_DIR=data

SOURCES=$(wildcard $(SRC_DIR)/*.cpp)
OBJECTS=$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
TARGET=SistemaAcademico

all: directories $(BIN_DIR)/$(TARGET)

directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(DATA_DIR)

$(BIN_DIR)/$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)/$(TARGET)
	@rm -f $(DATA_DIR)/*.txt $(DATA_DIR)/*.dat
	@echo "Limpieza completada."

.PHONY: all clean directories