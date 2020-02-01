COMPILE = g++
CFLAGS = -std=c++11
SRC_DIR = src
OBJ_DIR = build

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

branchism: $(OBJ_FILES)
	$(COMPILE) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(COMPILE) $(CFLAGS) -c -o $@ $<

clean: 
	rm build/*

