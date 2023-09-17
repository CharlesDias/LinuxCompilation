# Linux Compilation

**Index:**
- [1. Compilation process.](#1-compilation-process)
- [2. Types of linking.](#2-types-of-linking)
- [3. Object files.](#3-object-files)
- [4. GCC commands and options.](#4-gcc-gnu-compiler-collection-commands-and-options)
- [5. Using readelf.](#5-using-readelf)

## 1. Compilation process.

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

## 2. Types of linking

In Linux there are two main types of linking when it comes to libraries: static linking and dynamic linking.

### 2.1 Static Linking

In static linking, the library's code is integrated into the executable itself at compile time. As a result, the executable becomes self-contained and doesn't depend on external library files during runtime. This also means the binary will be larger since it contains all the required library code.

**Pros**
- No external dependencies at runtime. The executable can run on any system of the same architecture without needing the library installed.
- Potentially faster execution since there's no runtime overhead of loading or linking library code.

**Cons**
- Larger executable size.
- If the library gets an update (e.g., a bug fix or a security patch), the executable won't benefit from it unless recompiled with the updated library.
- Uses more disk space if multiple executables statically link the same library.

#### 2.1.1 Compile a static library

1. Considering the code inside the `ex03_static_library folder`. Access the subfolder `src`.

2. Before creating a library, compile each source file into its corresponding object file.

```bash
$ gcc -c math_ops_factorial.c math_ops_square.c 
```

That command will create the math_ops_factorial.o math_ops_square.o object files.

3. Run the file command, for example

```bash
$ file math_ops_factorial.o
math_ops_factorial.o: ELF 64-bit LSB relocatable, x86-64, version 1 (SYSV), not stripped
```
#### 2.1.2 Create a static library

1. Now, we can use the object files to create the static library.

```bash
$ ar rcs libmathops.a math_ops_square.o math_ops_factorial.o
```

After these commands, you will have a static library named `libmathops.a` which contains the functions for squaring and calculating the factorial of a number. Let's break down the `ar rcs` command:

- `ar`: This is the archive utility that allows you to create, modify, and extract from archives. In the context of C/C++ development, these archives are typically used as static libraries.

- `r`: Replace or insert the named files in the archive. If the archive does not exist, a new archive file is created.

- `c`: Create the archive if it does not exist.

- `s`: Write an object-file index into the archive, or update an existing one, even if no other change is made to the archive. An archive with an index speeds up linking to the library and allows routines in the library to call each other without regard to their placement in the archive.

2. Run the file command over the library.

```bash
$ file libmathops.a 
libmathops.a: current ar archive
```

And the ar t to see the content of the archive.

```bash
$ ar t libmathops.a 
math_ops_square.o
math_ops_factorial.o
```

3. After creation, move the library to the lib folder

```bash
$ mv libmathops.a ../lib
```
#### 2.1.3 Using the static library in another project

1. Compile the source code. AS the include is not in the standard or same directory, we need to specify their path with the `-I` option during compilation.

```bash
$ gcc -c main.c -Iinclude -o main.o
```

2. Link the object file with the static library to produce an executable. 

**Note:** Given that the library is named `libmathops.a`, we should use `-lmathops` without the `.a`. The linker will automatically prepend `lib` and look for `.a` (or `.so` for shared libraries) extensions.

```bash
$ gcc main.o -Llib/ -lmathops -o program
```

3. It is possible also to compile and link using just the command below.

```bash
$ gcc main.c -Llib/ -lmathops -Iinclude -o program
```

4. Run the `program`.

### 2.2 Dynamic linking

In dynamic linking, the library's code isn't part of the executable. Instead, the executable contains a reference to the library. The actual linking happens at runtime when both the executable and the library are loaded into memory. This is the most common method of linking on Linux.

**Pros**
- Smaller executable size.
- Multiple executables can share a single instance of the library in memory, saving RAM.
- Updating the library immediately benefits all dynamically linked executables, without recompilation. This is especially important for security patches.

**Cons**
- The executable requires the library to be present on the system at runtime. If the library is missing or an incompatible version is installed, the program won't run.
- Slight overhead during program startup due to the dynamic linking process.

**Usage**
Use the shared version of the library (typically has a .so extension, e.g., libfoo.so).

```bash
gcc program.c -L/path/to/library -lfoo -o program
```

**Note:** For dynamic libraries, there's also the concept of the runtime linker (or dynamic linker), which is responsible for loading and linking shared libraries at runtime.

**Which One to Choose?**

If portability (across machines without needing extra libraries) and possibly faster execution are crucial, consider static linking.

If saving disk space, memory, and benefiting from library updates without recompiling are more important, go with dynamic linking.

In practice, many systems rely heavily on dynamic linking due to the advantages of shared library updates and memory savings. Still, there are cases, especially in embedded systems or isolated environments, where static linking might be preferred.


## 3. Object files

An object file is the output generated when source code files are compiled. It contains machine code, but it's not yet a complete, runnable program or library. These files usually have a .o or .obj extension.

Contents of an Object File:
- Machine Code: This is the binary code the CPU will execute, but it might still have some placeholders for addresses or values that need to be filled in during the linking phase.
- Symbols: Symbols are names that represent various entities, such as functions or variables. Object files contain tables that list these symbols, and these tables help the linker in the final stages of creating an executable or library.
- Relocation Information: This information is vital for the linker. It tells the linker which parts of the machine code need to be adjusted or filled in with correct addresses once the final program layout is known.
- Debug Information: If the program was compiled with debug flags (e.g., -g with GCC), the object file might contain extra information that debuggers can use to map machine code back to the original source code.
- Other Metadata: This includes information about the architecture, sections of the object file, and more.

There are three types of object files:
- Relocatable Object Files: These are the intermediate files that are produced when source code files are compiled but not yet linked. They contain code and data sections that can be combined with other relocatable object files to produce a runnable program or shared object.
- Executable Object Files: These are runnable programs. They result from linking one or more relocatable object files. All addresses are fixed, and all symbols have been resolved.
- Shared Object Files: These are similar to executable files but are intended to be loaded by other programs at runtime. They are used to provide library functions and other capabilities to programs without having to include that code in every single program.

## 4. GCC (GNU Compiler Collection) commands and options

### Source and Output Files
| Option        | Description                                                          |
|---------------|----------------------------------------------------------------------|
| `-c`          | Compile source files, but don't link. Outputs object files.          |
| `-o filename` | Output to the given filename. Default is `a.out`.                    |

### Preprocessing Options
| Option          | Description                                                          |
|-----------------|----------------------------------------------------------------------|
| `-E`            | Only run the preprocessor.                                           |
| `-D name[=value]` | Define a preprocessor macro.                                       |
| `-U name`       | Undefine a preprocessor macro.                                       |
| `-I directory`  | Add directory to search path for header files.                       |

### Linking Options
| Option        | Description                                                          |
|---------------|----------------------------------------------------------------------|
| `-l library`  | Link with the library, e.g., `-lm` or `-lpthread`.                   |
| `-L directory`| Add directory to the library search path.                            |
| `-shared`     | Create a shared object.                                              |
| `-static`     | Perform static linking.                                              |

### Optimization Options
| Option    | Description                                                          |
|-----------|----------------------------------------------------------------------|
| `-Olevel` | Optimize code. Level can be `0`, `1`, `2`, `3`, or `s`.              |

### Debugging Options
| Option    | Description                                                          |
|-----------|----------------------------------------------------------------------|
| `-g`      | Produce debugging info in native format.                             |
| `-ggdb`   | Produce debugging info for GDB.                                      |
| `-pg`     | Generate profiling info for `gprof`.                                 |

### Warning Options
| Option    | Description                                                          |
|-----------|----------------------------------------------------------------------|
| `-Wall`   | Turn on most compiler warnings.                                      |
| `-Wextra` | Turn on additional warnings not in `-Wall`.                          |
| `-Werror` | Treat warnings as errors.                                            |

### Language Standards and Extensions
| Option        | Description                                                          |
|---------------|----------------------------------------------------------------------|
| `-ansi`       | Enforce ANSI standard.                                               |
| `-std=standard` | Specify the language standard (e.g., `-std=c99`, `-std=c++11`).    |
| `-pedantic`   | Issue warnings for strict standard compliance.                       |

### Machine-Dependent Options
| Option        | Description                                                          |
|---------------|----------------------------------------------------------------------|
| `-march=arch` | Optimize for specific architecture.                                  |
| `-mtune=arch` | Tune code for specific architecture but avoid exclusive instructions.|
| `-m32`/`-m64` | Generate code for a 32-bit or 64-bit environment.                    |

### Miscellaneous Options
| Option        | Description                                                          |
|---------------|----------------------------------------------------------------------|
| `-v`          | Display verbose output.                                              |
| `-p`          | Generate profile info for `prof`.                                    |
| `-fpic`/`-fPIC` | Generate position-independent code for shared libraries.           |
| `-save-temps` | Keep intermediate files: preprocessed source code and assembly files.|

## 5. Using readelf

Access the ex02_link_library sample code.

1. Run make to build the code.
```bash
$ make
gcc main.c -lm -o program
```
2. Run the `file program` command and see the information about the program file. We can see that the file is **ELF** format.
```bash
$ file program 
program: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=1bfdcb654fe08011988561dae71c36a6694f328f, for GNU/Linux 3.2.0, not stripped
```

3. After, running the `readelf -s program` to see only the symbol inside the binary or `readelf -a program` to see all information. 

4. Run the `readelf -a program | grep Shared` command to see just the shared libraries used by the binary.
```bash
$ readelf -a program | grep Shared
 0x0000000000000001 (NEEDED)             Shared library: [libm.so.6]
 0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
```

5. Run the `readelf -a program | grep interpreter` to see the runtime linker.

```bash
$ readelf -a program | grep interpreter
      [Requesting program interpreter: /lib64/ld-linux-x86-64.so.2]
```

6. Run readelf --help to see other options.
```bash
$ readelf --help
Usage: readelf <option(s)> elf-file(s)
 Display information about the contents of ELF format files
 Options are:
  -a --all               Equivalent to: -h -l -S -s -r -d -V -A -I
  -h --file-header       Display the ELF file header
  -l --program-headers   Display the program headers
     --segments          An alias for --program-headers
  -S --section-headers   Display the sections' header

. . . 
```