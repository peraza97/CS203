COMPILE = g++
CFLAGS = -std=c++11
SRC_DIR = src
OBJ_DIR = build
RM = rm 

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: $(OBJ_DIR)/branchism

$(OBJ_DIR)/branchism: $(OBJ_FILES)
	$(COMPILE) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(COMPILE) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR) 

clean: 
	$(RM) build/*

