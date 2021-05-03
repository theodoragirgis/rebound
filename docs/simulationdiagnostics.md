# Diagnostics 

## Energy
You can calculate the total energy (kinetic plus potential energy) of a simulation using the following function:

=== "C"
    ```c
    struct reb_simulation* r = reb_create_simulation();
    double energy = reb_calculate_energy(r);
    ```
=== "Python"
    ```python
    sim = rebound.Simulation()
    energy = sim.calculate_energy()
    ```

## Angular momentum
You can calculate the angular momentum of a simulation using the following function:

=== "C"
    ```c
    struct reb_simulation* r = reb_create_simulation();
    double energy = reb_calculate_angular_momentum(r);
    ```
=== "Python"
    ```python
    sim = rebound.Simulation()
    Lx, Ly, Lz = sim.calculate_angular_momentum()
    ```

## Center-of-mass
You can calculate the center-of-mass of a simulation using the following function:

=== "C"
    ```c
    struct reb_simulation* r = reb_create_simulation();
    struct reb_particle com = reb_get_com(r);
    ```
=== "Python"
    ```python
    sim = rebound.Simulation()
    com = sim.calculate_com()
    ```
The function returns a particle object with mass, position, and velocity reflecting those of the center-of-mass.

