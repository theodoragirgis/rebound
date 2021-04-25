# Compilation 

If you look at the examples in one of the `examples/` subdirectories, you see one
`.c` file and one `Makefile`. All the REBOUND code itself is in the
`src/` directory. This setup keeps the directory in which you're
working in nice and clean. To compile one of the examples, go to the
example's directory and type `make`. Then the following tasks will get executed:

-   The `Makefile` in the example directory sets up various environment variables. These
    determine settings like the compiler optimization flags and which
    libraries are included (see below).
-   Next, it calls the `Makefile` in the `src/` directory and compiles
    the entire REBOUND code into a shared library.
-   It then creates a symbolic link from the current directory to the
    location of the shared library in the `src/` directory.
-   Finally it compiles your code, the `problem.c` file, into an
    executable file and links it to the REBOUND shared library.

You can execute your program with `./rebound`. After you edited a file, you
can simply type `make` again to recompile your program. If you change any of the
environment variables, clean the build directiory first, by executing
`make clean`.

The easiest way to start working on your own problem is to simply copy an example directory that is somewhat similar to what you want to do.

