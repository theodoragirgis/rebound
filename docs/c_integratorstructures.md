# Integrator structures

This page describes the data structures used by integrators in REBOUND.
Here is an example which shows how to modify the structure which contains the settings for IAS15:

```c
struct reb_simulation* r = reb_create_simulation();
struct reb_simulation_integrator_ias15* r->ri_ias15 = r->ri_ias15;
ri_ias15->expsilon = 0; // Make IAS15 non-adaptive
```

or, more compactly:

```c
struct reb_simulation* r = reb_create_simulation();
r->ri_ias15->expsilon = 0; // Make IAS15 non-adaptive
```




## `reb_simulation_integrator_mercurius`

The `reb_simulation_integrator_mercurius` structure contains the configuration and data structures used by the hybrid symplectic MERCURIUS integrator.

Member                      | Description
--------------------------- | --------------
`double (*L) (const struct reb_simulation* const r, double d, double dcrit)`  |  This is a function pointer to the force switching function. If NULL (the default), the MERCURY switching function will be used. The argument `d` is the distance between two particles. The argument `dcrit` is the maximum critical distances of the two particles. The return value is a scalar between 0 and 1. If this function always returns 1, then the integrator effectively becomes the standard Wisdom-Holman integrator.
`double hillfac`            |  The critical switchover radii of particles are calculated automatically based on multiple criteria. One criterion calculates the Hill radius of particles and then multiplies it with the `hillfac` parameter. The parameter is in units of the Hill radius. The default value is 3. 
`unsigned int recalculate_coordinates_this_timestep`  | Setting this flag to one will recalculate heliocentric coordinates from the particle structure at the beginning of the next timestep. After a single timestep, the flag gets set back to 0. If one changes a particles manually after a timestep, then one needs to set this flag to 1 before the next timestep.
`unsigned int recalculate_dcrit_this_timestep`        | Setting this flag to one will recalculate the critical switchover distances dcrit at the beginning of the next timestep. After one timestep, the flag gets set back to 0. If you want to recalculate dcrit at every timestep, you also need to set this flag to 1 before every timestep.
`unsigned int safe_mode`                              | If this flag is set to 1 (the default), the integrator will recalculate heliocentric coordinates and synchronize after every timestep to avoid problems with outputs or particle modifications between timesteps. Setting this flag to 0 will result in a speedup, but care must be taken to synchronize and recalculate coordinates manually if needed.

All other members of this structure are only for internal use and should not be changed manually.


## `reb_simulation_integrator_sei`

The `reb_simulation_integrator_sei` structure contains the configuration and data structures used by the Symplectic Epicycle Integrator (SEI).

Member                      | Description
--------------------------- | --------------
`double OMEGA`              | Epicyclic/orbital frequency.
`double OMEGAZ`             | Epicyclic frequency in vertical direction.

All other members of this structure are only for internal use and should not be changed manually.


## `reb_simulation_integrator_saba`

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




## `reb_simulation_integrator_eos`

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


## `reb_simulation_integrator_janus`

The `reb_simulation_integrator_janus` structure contains the configuration and data structures used by the bib-wise reversible JANUS integrator.

Member                              | Description
----------------------------------- | --------------
`double scale_pos`                  | Scale of the problem. Positions get divided by this number before the conversion to an integer. Default: $10^{-16}$.
`double scale_vel`                  | Scale of the problem. Velocities get divided by this number before the conversion to an integer. Default: $10^{-16}$. 
`unsigned int order`                | The order of the scheme. Default is 6.
`unsigned int recalculate_integer_coordinates_this_timestep` | If this flag is set, then JANUS will recalculate the integer coordinates from floating point coordinates at the next timestep.

All other members of this structure are only for internal use and should not be changed manually.
