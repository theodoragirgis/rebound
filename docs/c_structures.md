# Main structures

This page describes the main data structures used in REBOUND.
The data structures related to integrators can be found on a [separate page](c_integratorstructures.md).

## `reb_particle`

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

## `reb_collision`

This structure describes a single collision. It is used to save a collision during collision search and passed as an argument to the function resolving the collisions. 

Member                      | Description
--------------------------- | --------------
`int p1`                    | Index corresponding to one of the colliding particles
`int p2`                    | Index corresponding to one of the colliding particles
`struct reb_ghostbox gb`    | Shift of particle p1 due to a collision across periodic and shearing sheet boundaries. All entries are zero if a normal collision occurs.
`int ri`                    | Index of the rootcell (only used for MPI)

## `reb_ghostbox`

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


