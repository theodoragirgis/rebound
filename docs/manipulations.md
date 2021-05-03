# Manipulations

## Adding, subtracting, multiplying particles
REBOUND allows you to multiply particles with scalars.
The particle's three position, its three velocity coordinates, and its mass are all multiplied by the constant.

=== "C"
    ```c
    struct reb_simulation* r = reb_create_simulation();
    reb_add_fmt(r, "m x vx", 1., 1., 1.);
    reb_particle_imul(&(r->particles[0]), 2.);
    ```
=== "Python"
    ```python
    sim = rebound.Simulation()
    sim.add(m=1., x=1., vx=1.)
    sim.particles[0] *= 2.
    ```
You can also add or subtract particles from each other. 
This will add or subtract the particles' position, velocity and mass from each other.

=== "C"
    ```c
    struct reb_particle p1 = {.m=1., .x=1, .vx=1};
    struct reb_particle p2 = {.m=2., .x=2, .vx=2};
    reb_particle_iadd(&p1, &p2); // p1.m, p1.x, p1.vx will now all be 3. p2 remains unchanged.
    reb_particle_isub(&p1, &p2); // p1.m, p1.x, p1.vx will be 1.
    ```
=== "Python"
    ```python
    p1 = rebound.Particle(m=0., x=1., vx=1.)
    p2 = rebound.Particle(m=0., x=1., vx=1.)
    p1 += p2 # p1.m, p1.x, p1.vx will now all be 3. p2 remains unchanged.
    p1 -= p2 # p1.m, p1.x, p1.vx will be 1.
    ```

In all the C functions, the first particle gets modified in place. 
In python, one can also use the multiply, add, and subtract operations to create new particles.
The following operations do not affect the original particles `p1` and `p2`.

```python
p1 = rebound.Particle(m=0., x=1., vx=1.)
p2 = rebound.Particle(m=0., x=1., vx=1.)
p3 = p1 + p2  # p3 is a new particle
p4 = p1 + p2  # p4 is a new particle
p5 = 2.*p1    # p5 is a new particle
```

!!! Tip
    These particle operations can be very helpful when initializing particles.
    For example, you can create initialize two particles using orbital parameters and then easily create another particle exactly in between these two particles.
    ```python
    sim = rebound.Simulation()
    sim.add(m=1)        # star
    sim.add(a=1)        # planet 1
    sim.add(a=2, f=0.1) # planet 2
    p_middle = (p1+p2)/2. # exactly in between the two planets
    ```

The distance between two particles in 3D space is often required in various calculations.
REBOUND has a convenience function for that:

=== "C"
    ```c
    struct reb_particle p1 = {.m=1., .x=1, .vx=1};
    struct reb_particle p2 = {.m=2., .x=2, .vx=2};
    double distance = reb_particle_distance(&p1, &p2); 
    ```
=== "Python"
    In python this is implemented using the power operator (`**`):
    ```python
    p1 = rebound.Particle(m=0., x=1., vx=1.)
    p2 = rebound.Particle(m=0., x=1., vx=1.)
    distance = p1 ** p2
    ```

## Adding, subtracting, multiplying simulations
REBOUND also allows you to manipulate entire simulations with arithmetic operations.
For example:

=== "C"
    ```c
    struct reb_simulation* r1 = reb_create_simulation();
    struct reb_simulation* r2 = reb_create_simulation();
    // ... setup simulations ...
    reb_simulation_isub(r1, r2);
    reb_simulation_iadd(r1, r2);
    ```
=== "Python"
    ```python
    r1 = rebound.Simulation()
    r2 = rebound.Simulation()
    # ... setup simulations ...
    r1 -= r2
    r1 += r2
    ```

In the above example, each particle in `r2` is subtracted from the corresponding particle in `r1`, in the sense described above (element-wise position, velocity and mass), then the operation is reversed in the next line when the simulation are added together.  
This feature can come in very handy when you want to compare two different simulations. 
For example, you can run two simulations with different timesteps and then subtract the simulation from each other after the integration to how much of a difference the timestep makes.
These operations will fail if the number of particles are not the same in `r1` and `r2`.

You can also multiple a simulation with two scalars, one for the position and one for the velocity coordinates.
This can come in handy when rescaling a simulation

=== "C"
    ```c
    struct reb_simulation* r = reb_create_simulation();
    // ... setup simulation ...
    reb_simulation_imul(r, 2., 3.,);
    ```
=== "Python"
    ```python
    r = rebound.Simulation()
    # ... setup simulation ...
    r.multiply(2., 3.)
    ```
In the above the position coordinates of all particles are multiplied by 2, all velocity coordinates are multiplied by 3.

## Moving reference frames
Compared to other N-body codes, REBOUND does not use a predifined coordinate system. 
It works in any intertial frame.
This makes setting up simulations and interpreting outputs more intuitive. 

However, one often wants to move to a specific coordinate system.
REBOUND has several built-in functions to do that.

Here is how you can move the simulation to the heliocentric frame.
=== "C"
    ```c
    struct reb_simulation* r = reb_create_simulation();
    // ... setup simulation ...
    reb_move_to_hel(r);
    ```
=== "Python"
    ```python
    r = rebound.Simulation()
    # ... setup simulation ...
    r.move_to_hel()
    ```
This moves all particles in the simulation by the same amount so that afterwards, the particle with index 0 is located at the origin. 
Note that as the integration progresses, it is not guaranteed that the particle with index 0 remains at the origin. 
Most likely, it will drift away from the origin. 
Therefore, if you require outputs in the heliocentric frame, call `move_to_hel` before you create an output. 
Variational equations are not affected by this operation.

You can also move a simulation to the center-of-mass frame, the inertial frame where the center-of-mass is at the origin. 
=== "C"
    ```c
    struct reb_simulation* r = reb_create_simulation();
    // ... setup simulation ...
    reb_move_to_com(r);
    ```
=== "Python"
    ```python
    r = rebound.Simulation()
    # ... setup simulation ...
    r.move_to_com()
    ```
!!! Important
    If you are not in the center-of-mass frame, the center-of-mass will and all the particles will slowly drift away from the origin. 
    This has important consequences for long-term intergrations. 
    If the particles are far away from the origin, you might increase the numerical errors due to finite floating point precision. 
    By moving to the center-of-mass frame after setting up all the particles, you avoid these issues.

