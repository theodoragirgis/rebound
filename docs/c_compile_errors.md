# Errors during compilation

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
