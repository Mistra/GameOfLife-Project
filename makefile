SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin

TARGET   = bin

SOURCES  = $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/*/*.cpp)
IFLAG    = $(addprefix -I, $(dir $(SOURCES)))
OBJECTS  = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

CC       = g++
CFLAGS   = -c -Wall -std=c++11 $(IFLAG) -g #-D NDEBUG
LDFLAGS  = -lpthread

all: $(BINDIR)/$(TARGET)
	@echo -e '\e[1;32m'make: all done'\033[0m'

$(BINDIR)/$(TARGET): $(OBJECTS)
	@echo -e '\e[1;33m'linking: $(notdir $^) to $(notdir $@)'\033[0m'
	@mkdir -p $(dir $@ )
	@$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@echo -e '\e[1;34m'compiling: $(notdir $<)'\033[0m'
	@mkdir -p $(dir $@ )
	@$(CC) $(CFLAGS) $< -o $@

clear:
	@-rm -fr $(BINDIR) $(OBJDIR)
	@echo -e '\e[1;35m'Cleared'\033[0m'
