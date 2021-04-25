# Quickstart guide

You can call REBOUND from either C or Python. Which programming language you want to use depends on your taste and your specific application. In short: If you want to setup a planetary system, visualize data with matplotlib or the built-in WebGL widget, and integrate your simulation with one of the built-in integrators then use the Python version. If you want to run large simulations with millions of particles, develop your own integrator, use OpenGL visualizations, or make use of the distributed tree code, then use the C version. 

All the computationally expensive parts of REBOUND are written in C. So even if you use the Python version, your simulation will run very efficiently.

## Python 
To install the Python version, the easiest way is to use pip. Simply type the following command into a terminal:

    pip install rebound

A simple python example to get you started is:

```python
# Import the rebound module
import rebound

# Create Simulation object
sim = rebound.Simulation()
# Add particle to rebound
sim.add( m=1. )
sim.add( m=1e-3, a=1., e=0.1 ) # Planet 1
sim.add( a=1.4, e=0.1 )        # Massless test particle

# Integrate the particles with the default IAS15 integrator
sim.integrate(100)

# Output orbits in Jacobi coordinates
for o in sim.calculate_orbits(): 
    print(o)

# Output cartesian coordinates
for p in sim.particles:
    print(p)
```

As a next step, have a look at the examples and tutorials in the `python_examples` and `ipython_examples` directories.

## C
To install the C version, clone the R repository. You can do that with the following command:
    
    git clone https://github.com/hannorein/rebound

Then compile and run one of the examples such as this one which simulates a patch of Saturn's rings:

    cd rebound/examples/shearing_sheet && make && ./rebound

To learn more about how to use REBOUND with C, have a look at the examples in the `examples/` directory. You might also want to have a look at the `rebound.h` file in the `src/` directory which contains the API specifications. Last but not least, REBOUND is open source. If you want to know how something works, you can just look at the source code. And of course, you are welcome to e-mail any of the contributors with questions. We'll do our best to answer them quickly.

*Note:*  If you want to run REBOUND on Windows, the best way is likely to install the Windows Subsystem for Linux. After installing the gcc compiler, e.g., sudo apt-get install gcc, you should be able to install REBOUND and any python libraries by following the Linux/Mac installation instructions in this documentation. Unfortunately we do not have Windows installations ourselves, so we cannot actively support installation problems. Thanks to Keto/Zhang for finding this workaround.

