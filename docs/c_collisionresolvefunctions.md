# Collision resolve functions

There are several built-in functions which resolve collisions in different ways.
Which function gets called after a collision has been detected is determined by the `collision_resolve` function pointer in `struct reb_simulation`. 
The following example shows how to set up a hardsphere collision resolve function and a direct collision detection routine.

```c
struct reb_simulation* r = reb_create_simulation();
r->collision = REB_COLLISION_DIRECT; // Direct collision search, O(N^2)
r->collision_resolve = reb_collision_resolve_hardsphere;
```

## Halt

This function resolves a collision by simply halting the integration and setting `r->status = REB_EXIT_COLLISION`. 
This is the default. 

```c
int reb_collision_resolve_halt(struct reb_simulation* const r, struct reb_collision c);
```

## Hardsphere

This assumes a hardsphere collision. 
This uses the `coefficient_of_restitution` parameter in `struct reb_simulation`. 
It conserves momentum and mass.
Depending on the coefficient of restitution, it also conserves energy.

```c
int reb_collision_resolve_hardsphere(struct reb_simulation* const r, struct reb_collision c);
```

## Merge
 
 This function merges the two colliding particles. 
 It conserves mass, momentum and volume.  
 The particle with the higher index will be removed. 

```c
int reb_collision_resolve_merge(struct reb_simulation* const r, struct reb_collision c);
```
