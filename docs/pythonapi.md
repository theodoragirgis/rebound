## Class `rebound.Simulation`
This is the REBOUND Simulation Class.
In encapsulated an entire REBOUND simulation and is an abstraction of the C struct reb_simulation.

### Examples

Most simulation parameters can be directly changed with the property syntax:

```python
 sim = rebound.Simulation()
 sim.G = 1.                  # Sets the graviational constant (default 1)
 sim.softening = 1.          # Sets the graviational softening parameter (default 0)
 sim.testparticle_type = 1   # Allows massive particles to feel influence from testparticles (default 0)
 sim.dt = 0.1                # Sets the timestep (will change for adaptive integrators such as IAS15).
 sim.t = 0.                  # Sets the current simulation time (default 0)
 print(sim.N)                # Gets the current number of particles
 print(sim.N_active)         # Gets the current number of active particles
```
   
By calling rebound.Simulation() as shown above, you create a new simulation object
The following example creates a simulation, saves it to a file and then creates
a copy of the simulation store in the binary file.

```python
 sim = rebound.Simulation()
 sim.add(m=1.)
 sim.add(m=1.e-3,x=1.,vy=1.)
 sim.save("simulation.bin")
 sim_copy = rebound.Simulation("simulation.bin")
```

Similarly, you can create a simulation, from a simulation archive
by specifying the snapshot you want to load. 

```python
 sim = rebound.Simulation("archive.bin", 34)
```

or 

```python
 sim = rebound.Simulation(filename="archive.bin", snapshot=34)
```
## Function `rebound.Simulation.copy`
Returns a deep copy of a REBOUND simulation. You need to reset 
any function pointers on the copy. 

Returns
------- 
A rebound.Simulation object.

