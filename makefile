#--------------------------------#
#  Preys and Predators makefile  #
#--------------------------------#

PROJECT='Preys and Predators'
MAKEFILE_VERSION=1.0
PROJECT_VERSION=0.6
AUTHOR=Giulio Mistrangelo

#Variables used to customize the output of the makefile:
INPUT_FILES=main.cpp thread.cpp predator.cpp common.cpp prey.cpp
#Source directory, default: src/ or leave blank
S_DIR=src/ src/predator src/common src/thread src/prey
#Object directory, default: obj/ or leave blank
O_DIR=obj/
#Executable directory, default: exec/ or leave blank
E_DIR=exec/
#Name of the executable, default: project
TARGET=project

CC=g++
CFLAGS=-c -Wall #-D NDEBUG
LDFLAGS=-lpthread
SOURCE=$(addprefix src/, $(INPUT_FILES))
VPATH=$(S_DIR)
OBJ=$(addprefix $(O_DIR), $(INPUT_FILES:.cpp=.o))

all: $(TARGET)

$(TARGET): $(OBJ)
	@echo -e '\e[1;34m'linking: $(notdir $^) to $(notdir $@)'\033[0m'
	@mkdir -p exec
	@$(CC) -o $(E_DIR)$@ $^ $(LDFLAGS)
	@echo -e '\e[1;31m'make: all done'\033[0m'

$(O_DIR)%.o : %.cpp
	@echo -e '\e[1;34m'compiling: $(notdir $<)'\033[0m'
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

## Clean Rule
clean:
	@-rm -fr $(E_DIR) $(O_DIR)
	@echo -e '\e[1;34m'Cleared'\033[0m'

about:
	@echo -e '\e[1;34m'Project: $(PROJECT)'\033[0m'
	@echo -e '\e[1;34m'Version: $(PROJECT_VERSION)'\033[0m'
	@echo -e '\e[1;34m'Author: $(AUTHOR)'\033[0m'

