# A detailed look at a simple example

REBOUND can be used as a shared library. However, installing a
system-wide shared library can sometimes be an obstacle for new users,
especially if you want to change the code frequently or don't have root
access. For that reason, all the examples can be compiled by simply
typing `make` in any of the example directories.

Let's look at how to setup a simple REBOUND simulation (see also the example in the `examples/simplest/` directory):

``` {.c}
#include "rebound.h"

int main(int argc, char* argv[]) {
        struct reb_simulation* r = reb_create_simulation();
        r->dt = 0.1;
        r->integrator = REB_INTEGRATOR_WHFAST;

        struct reb_particle p1 = {0};
        p1.m = 1.;
        reb_add(r, p1);

        struct reb_particle p2 = {0};
        p2.x = 1;
        p2.vy = 1;
        p2.m = 0.;
        reb_add(r, p2);

        reb_move_to_com(r);    
        reb_integrate(r,100.);
}
```

In the first line we include the REBOUND header file. This file contains
all the declarations of the structures and functions that we will be
using.

Next, we declare the only function in our file. It is the standard C
`main()` function. Within that, we first create a `reb_simulation`
structure. This is the main structure that contains all the variables,
pointers, and particles of a REBOUND simulation. You can create multiple
`reb_simulation` structures at the same time. REBOUND is thread-safe.

We can then set flags and variables in the `reb_simulation` structure.
Note that the `r` variable is a pointer to the structure, so
we use the arrow syntax `r->` to set variables contained within the structure. 
The next line chooses the integrator module. Here, we use the WHFast symplectic integrator.

We then create two particles, both of which are represented by a
`reb_particle` structure. The `= {0}` syntax ensures that our structs
are initialized with zeros. We set the initial conditions (the ones we
don't want to be zero) and then add the particle to the simulation
using the `reb_add()` function. Note that this function takes two
arguments, the first one is the simulation to which you want to add the
particle, and the second is the particle that you want to add.

Finally, we call the REBOUND function `reb_move_to_com()`. It moves the
particles to a centre of mass reference frame (this prevents particles
from drifting away from the origin). We then start the integration.
Here, we integrate for 100 time units. By default REBOUND used units in
which $G=1$, thus a particle around an $m=1$ mass central object at a
semi-major axis of $a=1$ needs $2\pi$ time units for one orbit.

Note that all REBOUND functions start with the three character prefix
`reb_`.

Next, let's add a call-back function to the above example. This
function will be called after every timestep and we can use it to output
simulation data. The relevant function pointer is called `heartbeat` in
the `reb_simulation` structure. We first declare and implement the
function and then set the pointer in the main routine:

``` {.c}
void heartbeat(struct reb_simulation* r){
       printf("%f\n",r->t);
}
int main(int argc, char* argv[]) {
       ...
       r->heartbeat = heartbeat;
       ...
}
```

As you can probably guess, this will make the program print out the
current time after every timestep. Since the heartbeat function receives
the `reb_simulation` structure, you have access to all the variables and
particles within the simulation. You don't need any global variables
for that. For example, if we wanted to print out the `x`
coordinate of the 2nd particle (the index starts at 0, so the second
particle has index 1), we could use this heartbeat function.

``` {.c}
void heartbeat(struct reb_simulation* r){
       double x = r->particles[1].x;
       printf("%f\n",x);
}
```

REBOUND comes with various built-in output functions that make your life
easier. It can for example calculate the orbital elements for you or
output a snapshot to a binary file. The examples are the best way to
get to know these functions. You can also look at the `rebound.h` file
in the `src/` directory to get an glimpse of the available functions.

