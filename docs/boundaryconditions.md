# Boundary conditions

## None
`REB_BOUNDARY_NONE`

This is the default. Particles are not affected by boundary conditions.

## Open
`REB_BOUNDARY_OPEN`      
 Particles are removed from the simulation if they leave the box.

## Periodic
`REB_BOUNDARY_PERIODIC`     

Periodic boundary conditions. Particles are reinserted on the other side if they cross the box boundaries. You can use an arbitrary number of ghost-boxes with this module.

## Shear
`REB_BOUNDARY_SHEAR`        

Shear periodic boundary conditions. Similar to periodic boundary conditions, but ghost-boxes are moving with constant speed, set by the shear.

