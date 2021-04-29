# Quickstart guide

You can call REBOUND from either C or Python. 
Which programming language you want to use depends on your taste and your specific application. In short: 

- If you want to setup a planetary system, visualize data with matplotlib or the built-in WebGL widget, and integrate your simulation with one of the built-in integrators then use the Python version. It's quick and easy to use. 
- If you want to run large simulations with millions of particles, develop your own integrator, use OpenGL visualizations, or make use of the distributed tree code, then use the C version. It gives you more direct access to all the internals.

!!! Note
    All the computationally expensive parts of REBOUND are written in C. So even if you use the Python version, your simulation will run very efficiently.
    If you want to extend REBOUND, for example to include an additional non-gravitational force, you can do that in both C or Python. For complicated force routines, a C implementation of your function would most likely be significantly faster.  


## Installation via pip
If you just want to try out REBOUND or don't plan to modify it in any way, then the easiest way to install the python version of REBOUND is [pip](https://pypi.org) (the Package Installer for Python). Simply type the following command into a terminal:

```bash
pip install rebound
```

If you have trouble installing a package with pip, consider using a [virtual environment](https://docs.python.org/3/tutorial/venv.html).


## Installation via git

REBOUND is using the version control system git. If you want to use the C version of REBOUND or plan to make any modifications to REBOUND, you should clone the repository to your computer. Make sure you have git installed, then type the following command in a terminal:

``` bash
git clone https://github.com/hannorein/rebound
```

This will create a new directory names `rebound/` which contains all the source code, examples, and documentation.
To use the python version of REBOUND, go to the `rebound/` directory, then install REBOUND with 
```bash
pip install -e .
```
You should now be able to import REBOUND from python. 

!!! Note 
    If you want to install REBOUND on Windows, the best way is likely to use the Windows Subsystem for Linux. After installing the gcc compiler, e.g., sudo apt-get install gcc, you should be able to install REBOUND and any python libraries by following the installation instructions in this documentation. Unfortunately we do not have Windows installations ourselves, so we cannot actively support installation problems. Thanks to Keto/Zhang for finding this workaround. If you have any additional information on how to use REBOUND on Windows, let us know!


## A simple python example 

Regardless of which installation method you have chosen, you should now be able to import rebound from python:

```python
import rebound
```

The run an N-body simulation, we first create a simulation object:

```python
sim = rebound.Simulation()
```

Then, we add particles to the simulation:

```python
sim.add(m=1.)                # Central object
sim.add(m=1e-3, a=1., e=0.1) # Jupiter mass planet 
sim.add(a=1.4, e=0.1)        # Massless test particle
```

Now we can integrate the particles forward in time using the default integrator (IAS15) for 100 time unit:

```python
sim.integrate(100.)
```

Finally, let us output the cartesian coordinates and the orbital parameters at the end of the simulation:

```
for p in sim.particles:
    print(p.x, p.y, p.z)
for o in sim.calculate_orbits(): 
    print(o)
```

As a next step, have a look at the examples and tutorials in the `python_examples` and `ipython_examples` directories.

## A simple C example

A very short example is provided in the `examples/simplest/` directory. 
Do to this directory with 

```bash
cd examples/simplest/
```

Then have a look at the source code in the `problem.c` file. First, we include the REBOUND header file which contains all the public function prototypes, and definitions for all the datatypes in REBOUND:

```c
#include "rebound.h"
```

In the main function, we first create a REBOUND simulation with 

```c
struct reb_simulation* r = reb_create_simulation();
```

This function has allocated memory for the simulation and has also initialized all the variables in the simulation to their default values. We can then add particles to the simulation:

```c
reb_add_fmt(r, "m", 1.);                // Central object
reb_add_fmt(r, "m a e", 1e-3, 1., 0.1); // Jupiter mass planet
reb_add_fmt(r, "a e", 1.4, 0.1);        // Massless test particle
```

We then integrate the simulation for 100 time units with the default integrator (IAS15):

```c
reb_integrate(r,100.);
```

After the integration is done, we can output the cartesian coordinates and the orbital parameters:

```c
for (int i=0; i<r->N; i++){
    struct reb_particle p = r->particles[i];
    printf("%f %f %f\n", p.x, p.y, p.z);
}
struct reb_particle primary = r->particles[0];
for (int i=1; i<r->N; i++){
    struct reb_particle p = r->particles[i];
    struct reb_orbit o = reb_tools_particle_to_orbit(r->G, p, primary);
    printf("%f %f %f\n", o.a, o.e, o.f);
}
```

To compile the example, simple type

```bash
make
```

into a terminal window while you're in the `examples/simplest/` directory. Then run the simulation with 
```bash
./rebound
```

## Where to go from here
To learn more about how to use REBOUND with C, have a look at the examples in the `examples/` directory. You might also want to have a look at the `rebound.h` file in the `src/` directory which contains the API specifications. Last but not least, REBOUND is open source. If you want to know how something works, you can just look at the source code. And of course, you are welcome to [open an issue](https://github.com/hannorein/rebound/issues) on Github or e-mail any of the [contributors](/#contributors) with questions. We'll do our best to answer them quickly.

