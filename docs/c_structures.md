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

The `reb_simulation_integrator_ias15` structure contains the configuration and data structures used by the IAS15 integrator.


Member                      | Description
--------------------------- | --------------
`double epsilon`            | This parameter controls the accuracy of the integrator. The default value is $10^{-9}$. Changing this parameter will change the timestep. However, note that changing the timestep rarely makes sense because IAS15 is a very high (15th) order integrator. Increasing the timestep by only a factor of 10 will increase the error by a factor of $10^{15}$. In other words, a simulation that previously was converged to machine precision will now have an error of order unity. **Important:** Setting this parameter to 0 turns off adaptive timestepping and a constant timestep will is used. 
`doule min_dt`              | This sets the minimum allowed timestep. The default value is 0. Set this to a finite value if the adaptive timestep becomes excessively small, for example during close encounters or because of finite floating point precision . Use with caution and make sure the simulation results make physically sense.
`unsigned int epsilon_global` | This flag determines how the relative acceleration error is estimated. If set to 1, IAS15 estimates the fractional error via `max(acceleration_error)/max(acceleration)` where the maximum is taken over all particles. If set to 0, the fractional error is estimates via `max(acceleration_error/acceleration)`.

All other members of this structure are only for internal IAS15 use and should not be changed manually.
