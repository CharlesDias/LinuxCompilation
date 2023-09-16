TARGET = program

all: $(TARGET)

# Note: the -lm has to be after the source files
# otherwise it will not compile.
# -save-temps keep intermediate files
$(TARGET):
	gcc main.c -lm -save-temps -o $(TARGET)
	gcc main.c -lm -static -o $(TARGET)_static

info: $(TARGET)
	file $(TARGET)

clean:
	rm -f $(TARGET) $(TARGET)_static *.o *.a *.so *.i *.s
