# Compiling the C version of REBOUND

This pages describe how to compile the C version of REBOUND.

## Examples

If you look at any of the examples in the `examples/` subdirectories, you'll see one
`problem.c` file and one `Makefile`. All the REBOUND code itself is in the
`src/` directory. This setup keeps the different projects nicely separated from the shared REBOUND code.
To compile one of the examples, go to the example's directory and type `make`. 
This triggers the following tasks:

1.  The Makefile in the example directory sets up various environment variables. These
    determine settings like compiler optimization flags and which
    libraries are included (see below).
2.  Next, the Makefile in the `src/` directory gets called. This compiles
    the entire REBOUND code into a shared library.
3.  It then creates a symbolic link from the current directory to the
    location of the shared library is located.
4.  Finally it compiles your own code, the `problem.c` file and links it to the REBOUND shared library.

You can execute your program with `./rebound`. After you edited either the `problem.c` file or any file in the `src/` directorty, you can simply type `make` again to recompile your program. 
If you change any of the environment variables, clean the build directiory first, by executing `make clean`.

## Your own project

The easiest way to start working on your own problem is to simply copy an example directory that is somewhat similar to what you want to do.
This way, all your project's source and data files will be in one directory, separate from the main REBOUND source files in `src/`. 

Alternatively, you can also install the shared REBOUND library in a global directory (e.g. `/usr/lib/`) and the header file in `/usr/include/`. 
Doing so will allow you (and any other users on your system) to use REBOUND from any directory.
However, doing so requires root access and some knowledge on how Unix systems work.
By simply replicating and modifying one of the examples, you'll avoid these complications.

## Errors during compilation

The way we've designed REBOUND should make the compilation process extremly easy.
You do not need to install any additional libraries (although you might want to, see below), and you do not need root access. 
You might nevertheless run into problems. Some of the most common issues are:

-   **Missing compilers.** Make sure you have a C compiler installed. If
    you are using a Mac, install the Xcode package which you can
    download for free on the AppStore. Make sure the command line tools 
    are installed.
-   **Missing glfw3 library.** You can compile REBOUND with support for
    real-time OpenGL visualizations. This requires the glfw3 library. If
    you are on a Mac, then the easiest way to install the glfw3 library
    is with homebrew:
    `brew tap homebrew/versions && brew install glfw3`. If you are on
    Linux, you can install it with your package manager, for example
    with `sudo apt-get install libglfw3-dev`. Alternatively, you can
    disable the OpenGL visualization in the Makefile by setting
    `OPENGL=0`. Then, execute `make clean` and try compiling the program
    again. Note that on some systems the `glfw` library is called
    `glfw3` instead. In that case, change `-lglfw` to `-lglfw3` 
    in the file `src/Makefile.defs`.
-   **Issue with march=native.** Some users have reported issues related
    to the compiler flag `-march=native` which tries to optimize the
    code for the native architecture. If you want to have the 
    most optimized code, add the `-march=native` or `-mtune=native` flag
    in the file `src/Makefile.defs`. If you use the python version, you
    can add compiler flags to `setup.py`. This might improve performance
    significantly.
