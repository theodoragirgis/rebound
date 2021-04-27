# MERCURIUS switching functions
These are force switching function for the MERCURIUS integrator. 
Below is an example on how to use them:

```c
struct reb_simulation* r = reb_create_simulation();
r->ri_mercurius.L = reb_integrator_mercurius_L_infinite; 
```

## Mercury

This is the same polynomial switching function as used in MERCURY. 

```c
double reb_integrator_mercurius_L_mercury(const struct reb_simulation* const r, double d, double dcrit);           
```
## Infinite

This is an infinitely differentiable switching function. 

```c
double reb_integrator_mercurius_L_infinite(const struct reb_simulation* const r, double d, double dcrit);           
```
