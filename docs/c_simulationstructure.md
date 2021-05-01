# Simulation structure

This page describes the `reb_simulation` structure. 
It contains the configuration and the current state of one REBOUND simulation.

## Life cycle
The `reb_create_simulation()` function allocate memory for a `reb_simulation` structure and also initialize all variables to their default value.
If you want to avoid a memory leak, you need to free the simulation when you no longer need it.
```c
struct reb_simulation* r = reb_create_simulation();
// ... do work ... 
reb_free_simulation(r);
```
The call to `reb_free_simulation()` frees all data associated with the simulation such as particles.
It will also free the memory for the simulation structure itself.

## Binary files
You can use binary files to save simulations to a file and then later restore them from this file.
All the particle data and the current simulation states are saved. 
Below is an example on how to work with binary files.

=== "C"
    ```c
    struct reb_simulation* r = reb_create_simulation();
    // ... setup simulation ...
    reb_integate(r, 10); // integrate 
    reb_output_binary(r, "snapshot.bin");
    reb_free_simulation(r); 

    struct reb_simulation* r2 = reb_create_simulation_from_binary("snapshot.bin);
    reb_integate(r2, 20); // continue integration
    reb_free_simulation(r2); 
    ```

=== "Python"
    ```python
    sim = rebound.Simulation()
    // ... setup simulation ...
    sim.integate(10)
    sim.ave("snapshot.bin")
    sim = None # Remove reference, allow python to release memory

    sim2 = rebound.Simulation("snapshot.bin")
    sim2.integrate(2) # continue integration
    sim2 = None 
    ```


A SimulationArchive is a collection of binary snapshots stored in the same file. 
You can load a specific snapshots with the function 

```c
struct reb_simulation* reb_create_simulation_from_simulationarchive(struct reb_simulationarchive* sa, long snapshot);
```



## General members
The following table lists the important members of `struct reb_simulation`.
To keep this documentation concise, the members which are only intended for internal use are not documented here. 


Member                      | Description
--------------------------- | --------------
`double t`                  | Current simulation time. 
`double G`                  | Gravitational constant. Default: 1. 
`double softening`          | Gravitational softening parameter. Default: 0. 
`double dt`                 | Current timestep. 
`double dt_last_done`       | Last timestep used.
`unsigned long long steps_done` | Number of timesteps completed.
`int N`                     | Current number of particles on this node. 
`int N_var`                 | Total number of variational particles. Default: 0.
`int N_active`              | Number of massive particles included in force calculation. The default is -1 which means the number of active particles is equal to the number of particles, `N`. Particles with an index larger or equal than `N_active` are considered testparticles.
`int var_config_N`          | Number of variational particle configurations. Default: 0.
`int testparticle_type`     | Type of the particles with `index >= N_active`. 0 means particle does not influence any other particle (default), 1 means particles with `index < N_active` feel testparticles (similar to MERCURY's small particles). Testparticles never feel each other.
`struct reb_particle* particles` | This is the main particle array which contains all particles.  
`double opening_angle2`     | Square of the cell opening angle $ \theta $. This determines the accuracy of the tree based gravity routine. 
`enum REB_STATUS status`    | This variable indicates the current status of the simulation. See below for possible values. By setting this to 1, one can force a graceful exit at the end of the next timestep.    
`int exact_finish_time`     | Set to 1 to finish the integration exactly at the requested time. Set to 0 to finish after a full timestep. This might overshoot the integration by a fraction of `dt`. Default is 1. 
`unsigned int force_is_velocity_dependent` | Set to 1 if integrator needs to consider velocity dependent forces.  
`unsigned int gravity_ignore_terms`        | Ignore the gravity form the central object (1 for WHFast, 2 for WHFast with democratic heliocentirc coordinates, 0 otherwise). The integrators will in general set this automatically and nothing needs to be changed by the user.
`double exit_max_distance`  | The integration will stop if any particle is further away from origin than this value.
`double exit_min_distance`  | The integration will stop if any two particles come closer together than this value.
`double usleep`             | Sleep this number of microseconds after each timestep. This can be useful for slowing down the simulation, for example for rendering visualizations.  
`int track_energy_offset`   | Track energy change during collisions and ejections (default: 0).
`double energy_offset`      | Energy offset due to collisions and ejections (only calculated if `track_energy_offset=1`).
`double walltime`           | Walltime in seconds used by REBOUND for this simulation (counting the integration only, not visualization, heartbeat function, etc).
`int nghostx`               | Number of ghostboxes in x direction. 
`int nghosty`               | Number of ghostboxes in y direction. 
`int nghostz`               | Number of ghostboxes in z direction. 
`int collision_resolve_keep_sorted` | If set to one, then particles are kept sorted, even if `collision_resolve` removes particles during a collision. 
`double minimum_collision_velocity`  | When collisions are resolved with the hard sphere collision resolve function, then the post impact velocity between the two particles will be at least as large as this value. Default 0. Setting this to a value larger than zero might prevent particles sinking into each other. 
`double collisions_plog`    | This variable keeps track of momentum exchange. This can be used to calculate collisional viscosity in ring systems.
`long collisions_Nlog`      | Number of collisions that have occured. This can be used to calculate statistical quantities of collisional systems.
`unsigned int rand_seed`    | Seed for random number generators. This will be automatically initialized automatically to a random number based on the current time and the process id. However, it can also be set manually to make the simulation reproducible and always return the same sequence of random numbers.

## Module selection 

The following `struct reb_simulation` members determine the modules selected. Each of them is explained in detail on their own page. 

Member                      | Description
--------------------------- | --------------
`enum visualization`        | Determines the visualization used. 
`enum collision`            | Determines the method used for finding collisions between particles. 
`enum integrator`           | Determines the integrator used. 
`enum boundary`             | Determines the boundary method. 
`enum gravity`              | Determines the method used for calculating gravitational forces between particles. 

## Integrator configuration 

The following `struct reb_simulation` members contain the configuration for the individual integrators. They are described on their own [separate page](integrators.md). 

Member                                                     | Description
---------------------------------------------------------- | --------------
`struct reb_simulation_integrator_sei ri_sei`              | The SEI struct 
`struct reb_simulation_integrator_whfast ri_whfast`        | The WHFast struct 
`struct reb_simulation_integrator_saba ri_saba`            | The SABA struct 
`struct reb_simulation_integrator_ias15 ri_ias15`          | The IAS15 struct
`struct reb_simulation_integrator_mercurius ri_mercurius`  | The MERCURIUS struct
`struct reb_simulation_integrator_janus ri_janus`          | The JANUS struct 
`struct reb_simulation_integrator_eos ri_eos`              | The EOS struct 
```

## Callback functions

The following members are all function pointers to various callback functions. 

Member                                                     | Description
---------------------------------------------------------- | --------------
`void (*heartbeat) (struct reb_simulation* r)`             | This function is called at the beginning of the simulation and at the end of each timestep.
`void (*additional_forces) (struct reb_simulation* const r)` | This function allows the user to add additional (non-gravitational) forces.
 */
`void (*pre_timestep_modifications) (struct reb_simulation* const r)` | This function allows the user to make changes before each timestep.
 */
`void (*post_timestep_modifications) (struct reb_simulation* const r)` | This function allows the user to make changes after each timestep.
`double (*coefficient_of_restitution) (const struct reb_simulation* const r, double v)` | Return the coefficient of restitution. By default, it is NULL, assuming a coefficient of 1. The velocity of the collision is given to allow for velocity dependent coefficients of restitution.
`int (*collision_resolve) (struct reb_simulation* const r, struct reb_collision)` | Resolve collision within this function. By default, it is NULL, assuming hard sphere model. A return value of 0 indicates that both particles remain in the simulation. A return value of 1 (2) indicates that particle 1 (2) should be removed from the simulation. A return value of 3 indicates that both particles should be removed from the simulation. 
`void (*free_particle_ap) (struct reb_particle* p)` | Free particle's ap pointer.  Called in reb_remove function.

