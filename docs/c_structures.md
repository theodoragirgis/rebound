# Structures

This page describes the data structures used in the REBOUND.

## `struct reb_particle`

This structure represents a single particle in REBOUND.

Member                      | Description
--------------------------- | --------------
`double x`                  | x-position of the particle. 
`double y`                  | y-position of the particle. 
`double z`                  | z-position of the particle. 
`double vx`                 | x-velocity of the particle. 
`double vy`                 | y-velocity of the particle. 
`double vz`                 | z-velocity of the particle. 
`double ax`                 | x-acceleration of the particle. 
`double ay`                 | y-acceleration of the particle. 
`double az`                 | z-acceleration of the particle. 
`double m`                  | Mass of the particle. 
`double r`                  | Radius of the particle. 
`double lastcollision`      | Last time the particle had a physical collision.
`struct reb_treecell* c`    | Pointer to the cell the particle is currently in.
`uint32_t hash`             | Hash, can be used to identify particle.
`void* ap`                  | This pointer allows REBOUNDx to add additional properties to the particle.
`struct reb_simulation* sim`| Pointer to the parent simulation.


## `struct reb_ghostbox`

This structure contains the relative position and velocity of a ghostbox. 
Ghostboxes are used for periodic or shear-periodic boundary conditions. 
This structure if often passed as a function argument to account for the shift of a ghostbox relative to the original box during gravity calculation or a collision search. 
If there are no ghostboxed used, then all elements of this structure will be zero.

Member                      | Description
--------------------------- | --------------
`double shiftx`             | Relative x position
`double shifty`             | Relative y position
`double shiftz`             | Relative z position
`double shiftvx`            | Relative x velocity
`double shiftvy`            | Relative y velocity
`double shiftvz`            | Relative z velocity


## `struct reb_simulation_integrator_ias15`

The `reb_simulation_integrator_ias15` structure contains the configuration and data structures used by the high order IAS15 integrator.


Member                      | Description
--------------------------- | --------------
`double epsilon`            | This parameter controls the accuracy of the integrator. The default value is $10^{-9}$. Changing this parameter will change the timestep. However, note that changing the timestep rarely makes sense because IAS15 is a very high (15th) order integrator. Increasing the timestep by only a factor of 10 will increase the error by a factor of $10^{15}$. In other words, a simulation that previously was converged to machine precision will now have an error of order unity. **Important:** Setting this parameter to 0 turns off adaptive timestepping and a constant timestep will is used. 
`doule min_dt`              | This sets the minimum allowed timestep. The default value is 0. Set this to a finite value if the adaptive timestep becomes excessively small, for example during close encounters or because of finite floating point precision . Use with caution and make sure the simulation results make physically sense.
`unsigned int epsilon_global` | This flag determines how the relative acceleration error is estimated. If set to 1, IAS15 estimates the fractional error via `max(acceleration_error)/max(acceleration)` where the maximum is taken over all particles. If set to 0, the fractional error is estimates via `max(acceleration_error/acceleration)`.

All other members of this structure are only for internal IAS15 use and should not be changed manually.

## `struct reb_simulation_integrator_mercurius`

The `reb_simulation_integrator_mercurius` structure contains the configuration and data structures used by the hybrid symplectic MERCURIUS integrator.

Member                      | Description
--------------------------- | --------------
`double (*L) (const struct reb_simulation* const r, double d, double dcrit)`  |  This is a function pointer to the force switching function. If NULL (the default), the MERCURY switching function will be used. The argument `d` is the distance between two particles. The argument `dcrit` is the maximum critical distances of the two particles. The return value is a scalar between 0 and 1. If this function always returns 1, then the integrator effectively becomes the standard Wisdom-Holman integrator.
`double hillfac`            |  The critical switchover radii of particles are calculated automatically based on multiple criteria. One criterion calculates the Hill radius of particles and then multiplies it with the `hillfac` parameter. The parameter is in units of the Hill radius. The default value is 3. 
`unsigned int recalculate_coordinates_this_timestep`  | Setting this flag to one will recalculate heliocentric coordinates from the particle structure at the beginning of the next timestep. After a single timestep, the flag gets set back to 0. If one changes a particles manually after a timestep, then one needs to set this flag to 1 before the next timestep.
`unsigned int recalculate_dcrit_this_timestep`        | Setting this flag to one will recalculate the critical switchover distances dcrit at the beginning of the next timestep. After one timestep, the flag gets set back to 0. If you want to recalculate dcrit at every timestep, you also need to set this flag to 1 before every timestep.
`unsigned int safe_mode`                              | If this flag is set to 1 (the default), the integrator will recalculate heliocentric coordinates and synchronize after every timestep to avoid problems with outputs or particle modifications between timesteps. Setting this flag to 0 will result in a speedup, but care must be taken to synchronize and recalculate coordinates manually if needed.

All other members of this structure are only for internal use and should not be changed manually.


## `struct reb_simulation_integrator_sei`

The `reb_simulation_integrator_sei` structure contains the configuration and data structures used by the Symplectic Epicycle Integrator (SEI).

Member                      | Description
--------------------------- | --------------
`double OMEGA`              | Epicyclic/orbital frequency.
`double OMEGAZ`             | Epicyclic frequency in vertical direction.

All other members of this structure are only for internal use and should not be changed manually.


## `struct reb_simulation_integrator_saba`

The `reb_simulation_integrator_saba` structure contains the configuration and data structures used by the SABA integrator family.

Member                              | Description
----------------------------------- | --------------
`unsigned int type`                 | This parameter specifies which SABA integrator type is used. See below for possible values.
`unsigned int safe_mode`            | The same mode flag has the same functionality as in WHFast. Default is 1. Setting this to 0 will provide a speedup but care must be taken with synchronizing integration steps and modifying particles.
`unsigned int keep_unsynchronized`  | This flag determines if the inertial coordinates generated are discarded in subsequent timesteps (cached Jacobi coordinates are used instead). The default is 0. Set this flag to 1 if you require outputs and bit-wise reproducibility 

### SABA types
The possible SABA integrator types are:

Numerical value     |  Constant name      | Description 
------------------- | ------------------- | ----------------------------------
0x0                 | `REB_SABA_1`        | WH
0x1                 | `REB_SABA_2`        | SABA2
0x2                 | `REB_SABA_3`        | SABA3
0x3                 | `REB_SABA_4`        | SABA4
0x100               | `REB_SABA_CM_1`     | SABACM1 (Modified kick corrector)
0x101               | `REB_SABA_CM_2`     | SABACM2 (Modified kick corrector)
0x102               | `REB_SABA_CM_3`     | SABACM3 (Modified kick corrector)
0x103               | `REB_SABA_CM_4`     | SABACM4 (Modified kick corrector)
0x200               | `REB_SABA_CL_1`     | SABACL1 (lazy corrector)
0x201               | `REB_SABA_CL_2`     | SABACL2 (lazy corrector)
0x202               | `REB_SABA_CL_3`     | SABACL3 (lazy corrector)
0x203               | `REB_SABA_CL_4`     | SABACL4 (lazy corrector)
0x4                 | `REB_SABA_10_4`     | SABA(10,4), 7 stages
0x5                 | `REB_SABA_8_6_4`    | SABA(8,6,4), 7 stages
0x6                 | `REB_SABA_10_6_4`   | SABA(10,6,4), 8 stages, default
0x7                 | `REB_SABA_H_8_4_4`  | SABAH(8,4,4), 6 stages
0x8                 | `REB_SABA_H_8_6_4`  | SABAH(8,6,4), 8 stages
0x9                 | `REB_SABA_H_10_6_4` | SABAH(10,6,4), 9 stages


## `struct reb_simulation_integrator_whfast`

The `reb_simulation_integrator_whfast` structure contains the configuration and data structures used by the WHFast integrator.

Member                              | Description
----------------------------------- | --------------
`unsigned int corrector`            | This variable turns on/off different first symplectic correctors for WHFast. By default first symplectic correctors are off (0). See below for possible values.
`unsigned int corrector2`           | This variable turns on/off second symplectic correctors for WHFast. By default second symplectic correctors are off (0). ee below for possible values. Set to 1 to use second symplectic correctors.
`unsigned int kernel`               | This variable determines the kernel of the WHFast integrator. By default it uses the standard WH kick step. See below for other options.
`unsigned int coordinates`          | Chooses the coordinate system for the WHFast algorithm. Default is Jacobi Coordinates. See below for other options.
`unsigned int recalculate_coordinates_this_timestep` | Setting this flag to one will recalculate Jacobi/heliocentric coordinates from the particle structure in the next timestep. After the timestep, the flag gets set back to 0. If you want to change particles after every timestep, you also need to set this flag to 1 before every timestep. Default is 0.
`unsigned int safe_mode`            | If this flag is set (the default), whfast will recalculate the internal coordinates (Jacobi/heliocentric/WHDS) and synchronize every timestep, to avoid problems with outputs or particle modifications between timesteps. Setting it to 0 will result in a speedup, but care must be taken to synchronize and recalculate the internal coordinates when needed. See the AdvWHFast.ipynb tutorial.
`unsigned int keep_unsynchronized`  | This flag determines if the inertial coordinates generated are discarded in subsequent timesteps (cached Jacobi/heliocentric/WHDS coordinates are used instead). The default is 0. Set this flag to 1 if you require outputs and bit-wise reproducibility

All other members of this structure are only for internal use and should not be changed manually.


### Symplectic correctors
First symplectic correctors (or just *symplectic correctors*) remove error terms up to $O(\epsilon \cdot dt^p)$, where $p$ is the order of the symplectic corrector, and $\epsilon$ is the mass ratio in the system.
First order correctors implemented in REBOUND are:

Order   | Description
------- | ----------------
0       | This turns of all first correctors (default)
3       | Third order (two-stage) first corrector 
5       | Fifth order (four-stage) first corrector 
7       | Seventh order (six-stage) first corrector 
11      | Eleventh order (ten-stage) first corrector 
17      | 17th order (16-stage) first corrector 


### Kernels
WHFast supports different kernels. The default kernal is a standard kick step. Kernels implemented in REBOUND are:

Numerical value | Constant name                     | Description
--------------- | --------------------------------- | ----------------
0               | `REB_WHFAST_KERNEL_DEFAULT`       | A standard WH kick step (default)
1               | `REB_WHFAST_KERNEL_MODIFIEDKICK`  | Exact modified kick. This works for Newtonian gravity only. Not additional forces. 
2               | `REB_WHFAST_KERNEL_COMPOSITION`   | Composition kernel
3               | `REB_WHFAST_KERNEL_LAZY`          | Lazy implementer's modified kick. This is often the best option.
     
### Coordinate systems
WHFast supports different coordinate systems:    

Numerical value | Constant name                                     | Description
--------------- | ------------------------------------------------- | ----------------
0               | `REB_WHFAST_COORDINATES_JACOBI`                   | Jacobi coordinates (default)
1               | `REB_WHFAST_COORDINATES_DEMOCRATICHELIOCENTRIC`   | Democratic Heliocentric coordinates
2               | `REB_WHFAST_COORDINATES_WHDS`                     | WHDS coordinates (Hernandez and Dehnen, 2017)




## `struct reb_simulation_integrator_eos`

The `reb_simulation_integrator_eos` structure contains the configuration and data structures used by the Embedded Operator Splitting integrator (EOS).

Member                              | Description
----------------------------------- | --------------
`unsigned int phi0`                 | Outer operator splitting scheme (see below for options)
`unsigned int phi1`                 | Inner operator splitting scheme (see below for options)
`unsigned int n`                    | Number of sub-timesteps. Default: 2. 
`unsigned int safe_mode`            | If set to 0, always combine drift steps at the beginning and end of `phi0`. If set to 1, `n` needs to be bigger than 1.

All other members of this structure are only for internal use and should not be changed manually.

### Operator Splitting methods

The following operator splitting methods for `phi0` and `phi1` are supported in the EOS integrator.

Numerical value | Constant name         | Description
--------------- | --------------------- | -------------------------------------------------
0x00            | `REB_EOS_LF`          | 2nd order, standard leap-frog
0x01            | `REB_EOS_LF4`         | 4th order, three function evaluations
0x02            | `REB_EOS_LF6`         | 6th order, nine function evaluations
0x03            | `REB_EOS_LF8`         | 8th order, seventeen funtion evaluations, see Blanes & Casa (2016), p91
0x04            | `REB_EOS_LF4_2`       | generalized order (4,2), two force evaluations, McLachlan 1995
0x05            | `REB_EOS_LF8_6_4`     | generalized order (8,6,4), seven force evaluations
0x06            | `REB_EOS_PLF7_6_4`    | generalized order (7,6,4), three force evaluations, pre- and post-processors
0x07            | `REB_EOS_PMLF4`       | 4th order, one modified force evaluation, pre- and post-processors, Blanes et al. (1999)
0x08            | `REB_EOS_PMLF6`       | 6th order, three modified force evaluations, pre- and post-processors, Blanes et al. (1999)
