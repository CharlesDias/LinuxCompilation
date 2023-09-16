# Variables
CC = gcc
CFLAGS = -Wall -O0 -g -std=c18 
# -O0: no optimization, -g: debug info -sdt=c18: C18 standard

ASSEMBLER = $(CC) -S
LINKER = $(CC) -o
PREPROCESSOR = $(CC) -E
OUTPUT = program

# Targets

all: $(OUTPUT)

# 1. Preprocessing
preprocess: main.c pre_and_macros.h
	$(PREPROCESSOR) main.c > main.i

# 2. Compilation
compile: preprocess
	$(ASSEMBLER) main.i

# 3. Assembly
assemble: compile
	$(CC) -c main.s

# 4. Linking
$(OUTPUT): assemble
	$(LINKER) $(OUTPUT) main.o

# Disassembling the ELF binary
disassemble: $(OUTPUT)
	objdump -d $(OUTPUT) > $(OUTPUT).asm

# Dumping detailed information about the ELF binary
dumpinfo: $(OUTPUT)
	objdump -x $(OUTPUT) > $(OUTPUT).info

clean:
	rm -f $(OUTPUT) $(OUTPUT).* main.o main.i main.s

.PHONY: all preprocess compile assemble clean
