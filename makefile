
S_DIR   = src/
O_DIR   = obj/
E_DIR   = bin/

EXEC    = $(addprefix $(E_DIR), bin)
SRC     = $(wildcard $(S_DIR)*.cpp) $(wildcard $(S_DIR)*/*.cpp)
IFLAG   = $(addprefix -I, $(dir $(SRC)))
OBJ     = $(SRC:$(S_DIR)%.cpp=$(O_DIR)%.o)
CC      = g++
CFLAGS  = -c -Wall -std=c++11 $(IFLAG) -g #-D NDEBUG
LDFLAGS = -lpthread

all: $(EXEC)
	@echo -e '\e[1;32m'make: all done'\033[0m'

$(EXEC): $(OBJ)
	@echo -e '\e[1;33m'linking: $(notdir $^) to $(notdir $@)'\033[0m'
	@mkdir -p $(dir $@ )
	@$(CC) $^ -o $@ $(LDFLAGS)

$(O_DIR)%.o : $(S_DIR)%.cpp
	@echo -e '\e[1;34m'compiling: $(notdir $<)'\033[0m'
	@mkdir -p $(dir $@ )
	@$(CC) $(CFLAGS) $< -o $@

clear:
	@-rm -fr $(E_DIR) $(O_DIR)
	@echo -e '\e[1;35m'Cleared'\033[0m'
