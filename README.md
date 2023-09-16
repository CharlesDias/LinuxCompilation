# Linux Compilation

## Compilation process.

The compilation process transforms human-readable source code into machine-executable binary code.

1. Preprocessing:
    - Before actual compilation begins, the source code goes through a preprocessing stage.
    - This stage handles directives of preprocessing, like `#ifdef`, expand macros and add include files in source code.
    - Use the cpp command to generate the file with all macros and code expanded. Example,
    ```console
    $ gcc -E main.c > main.i
    ```

2. Compilation:
    - Expanded source code is compiled into assembly language code specific to the target architecture.
    - This step checks the syntax of the program. If there are any syntax errors, the compiler will stop and report them.
    - The command `gcc -S` generates the `.s` output file that contains architecture-specific assembly code.
    ```console
    $ gcc -S main.i
    ```

3. Assembly:
    - The assembler translates the assembly code into machine code in the form of object files (with a .o or .obj extension).
    - This step generates the actual binary code but hasn't linked it yet.
    ```console
    $ gcc -c main.i
    ```

4. Linking:
    - The linker takes one or more object files and links them together to produce a single executable file or a library.
    - If your program references external libraries or functions across multiple source files, the linker resolves these references and ensures that everything points to the right place.
    ```console
    $ gcc -o main.o
    ```

### Code example

See the `ex01_compilation_process` code to reproduce the compilation process.