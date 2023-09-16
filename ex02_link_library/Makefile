TARGET = program

all: $(TARGET)

# Note: the -lm has to be after the source files
# otherwise it will not compile.
# -save-temps keep intermediate files
$(TARGET):
	gcc main.c -lm -save-temps -o $(TARGET)

info: $(TARGET)
	file $(TARGET)

clean:
	rm -f $(TARGET) *.o *.a *.so *.i *.s
