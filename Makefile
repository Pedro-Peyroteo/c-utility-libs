CC=gcc
CFLAGS=-Iinclude -Wall -Wextra -std=c11

SRC=src/dlist.c src/dlist_priority.c
OBJDIR=build/obj
OBJ=$(SRC:src/%.c=$(OBJDIR)/%.o)

LIBDIR=build
LIB=$(LIBDIR)/libdlist.a

all: $(LIB)

# Build library
$(LIB): $(OBJ)
	@if not exist "$(LIBDIR)" ( mkdir "$(LIBDIR)" )
	ar rcs $(LIB) $(OBJ)

# Build object files into build/obj
$(OBJDIR)/%.o: src/%.c
	@if not exist "$(OBJDIR)" ( mkdir "$(OBJDIR)" )
	$(CC) $(CFLAGS) -c $< -o $@

# Windows-friendly clean command
clean:
	@if exist build ( rmdir /S /Q build )

test: all
	$(CC) tests/test_basic.c -Iinclude -Lbuild -ldlist -o build/test_basic
	./build/test_basic
