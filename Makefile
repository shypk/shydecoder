CPP := g++
CFLAGS := -O2 -Wall -Wextra -fPIC

ifdef SKIP_CTRL_CHAR
CFLAGS += -DSKIP_CTRL_CHAR
endif

LUAFLAGS := -I/usr/include/luajit-2.1 -L/usr/local/lib -lluajit-5.1
LUA52FLAGS := -I/usr/include/lua5.2 -L/usr/lib/x86_64-linux-gnu/ -llua5.2

INCLUDEDIR := include
SRCDIR := src
OBJDIR := obj
BINDIR := bin

SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

.PHONY: all clean test lua luajit lua52
all: test lua

test: $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CPP) $(CFLAGS) -I$(INCLUDEDIR) $^ test/test.c -o $(BINDIR)/$@ 
	./$(BINDIR)/$@		

lua: $(OBJECTS)
	@mkdir -p $(OBJDIR)
	$(CPP) $(CFLAGS) $(LUAFLAGS) -I$(INCLUDEDIR) lua/shydecoder.c $(OBJECTS) -shared -o $(OBJDIR)/shydecoder.so

luajit: $(OBJECTS)
	@mkdir -p $(OBJDIR)
	$(CPP) $(CFLAGS) $(LUAFLAGS) -I$(INCLUDEDIR) lua52/shydecoder.c $(OBJECTS) -shared -o $(OBJDIR)/shydecoder.so

lua52: $(OBJECTS)
	@mkdir -p $(OBJDIR)
	$(CPP) $(CFLAGS) $(LUA52FLAGS) -I$(INCLUDEDIR) lua52/shydecoder.c $(OBJECTS) -shared -o $(OBJDIR)/shydecoder.so

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CPP) $(CFLAGS)  -I$(INCLUDEDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

