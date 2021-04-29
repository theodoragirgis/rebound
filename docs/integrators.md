# Integrators

Numerical integrators are the backbone of any N-body package. 
A numerical integrator evolves particles forward in time, one timestep at a time.
To do that, the integrator needs to know the current position and velocity coordinates of the particles, and the equations of motion which come in the form of a set of ordinary differential equations.

Because an exact solution to these differential equations is in general unknown, each integrator attempts to approximate the true solution numerically. 
Different integrators do this differently and each of them has some advantages and some disadvanatges. 
Each of the built-in integrators of REBOUND is described in this section.

## IAS15

IAS15 stands for **I**ntegrator with **A**daptive **S**tep-size control, **15**th order. It is a very high order, non-symplectic integrator which can handle arbitrary forces (inluding those who are velocity dependent). 
It is in most cases accurate down to machine precision (16 significant decimal digits). 
The IAS15 implementation in REBOUND can integrate variational equations. 
The algorithm is describe in detail in [Rein & Spiegel 2015](https://ui.adsabs.harvard.edu/abs/2015MNRAS.446.1424R/abstract) and also in the original paper by [Everhart 1985](https://ui.adsabs.harvard.edu/abs/1985ASSL..115..185E/abstract). 


IAS15 is the default integrator of REBOUND, so if you want to use it, you don't need to do anything. 
However, you can also set it explicitly:

=== "C"
    ```c
    struct reb_simulation* r = reb_create_simulation();
    r->integrator = REB_INTEGRATOR_IAS15;
    ```

=== "Python"
    ```python
    sim = rebound.Simulation()
    sim.integrator = "ias15"
    ```

The setting for IAS15 are stored in the `reb_simulation_integrator_ias15` stucture. 

`epsilon` (`double`)
:   IAS15 is an adaptive integrator. It chooses its timesteps automatically. This parameter controls the accuracy of the integrator. The default value is $10^{-9}$. Setting this parameter to 0 turns off adaptive timestepping and a constant timestep will is used. Turning off adaptive timestepping is rarely useful. 

    !!! Important
        It is tempting to change `epsilon` to achieve a speedup at the loss of some accuracy. However, that makes rarely sense. The reason is that IAS15 is a very high (15th!) order integrator. Suppose we increasing the timestep by a factor of 10. This will increase the error by a factor of $10^{15}$. In other words, a simulation that previously was converged to machine precision will now have an error of order unity. 

`min_dt` (`double`)
:   This sets the minimum allowed timestep. The default value is 0. Set this to a finite value if the adaptive timestep becomes excessively small, for example during close encounters or because of finite floating point precision. Use with caution and make sure the simulation results still make physically sense as you might be in danger of ignoring small timescales in the problem. 
    The following code sets the smallest timestep to $10^{-3}$ time units: 
    === "C"
        ```c
        struct reb_simulation* r = reb_create_simulation();
        r->ri_ias15.min_dt = 1e-3;
        ```

    === "Python"
        ```python
        sim = rebound.Simulation()
        sim.ri_ias.min_dt = 1e-3
        ```

`epsilon_global` `(unsigned int`)
:   This flag determines how the relative acceleration error is estimated. If set to 1, IAS15 estimates the fractional error via `max(acceleration_error)/max(acceleration)` where the maximum is taken over all particles. If set to 0, the fractional error is estimates via `max(acceleration_error/acceleration)`.

All other members of this structure are only for internal IAS15 use.


## WHFast
`REB_INTEGRATOR_WHFAST`

WHFast is the integrator described in Rein & Tamayo 2015 and Rein, Tamayo & Brown 2019. It is an implementation of the symplectic Wisdom-Holman integrator. It supports first and second symplectic correctors as well as the kernel method of Wisdom et al. 1996 with various different kernels. It is very fast and accurate, uses Gauss f and g functions to solve the Kepler motion and can integrate variational equations. The user can choose between Jacobi and Democratic Heliocentric coordinates. 

## SABA
`REB_INTEGRATOR_SABA`

SABA are symplectic integrators developed by Laskar & Robutel 2001 and Blanes et al. 2013. This implementation support SABA1, SABA2, SABA3, and SABA4 as well as the corrected versions SABAC1, SABAC2, SABAC3, and SABAC4. Different correctors can be selected. Also supported are SABA(8,4,4), SABA(8,6,4), SABA(10,6,4). See Rein, Tamayo & Brown 2019 for details. 

## JANUS
`REB_INTEGRATOR_JANUS`

Janus is a bit-wise time-reversible high-order symplectic integrator using a mix of floating point and integer arithmetic. This integrator is still in an experimental stage and will be discussed in an upcoming paper. 

## Embedded Operator Splitting Method (EOS)
`REB_INTEGRATOR_EOS`          

Embedded Operator Splitting (EOS) Methods. See Rein 2019 for details.

## Leapfrog
`REB_INTEGRATOR_LEAPFROG`     

Leap frog, second order, symplectic

## Symplectic Epicycle Integrator (SEI)
`REB_INTEGRATOR_SEI`          

Symplectic Epicycle Integrator (SEI), mixed variable symplectic integrator for the shearing sheet, second order, Rein & Tremaine 2011

## Mercurius
`REB_INTEGRATOR_MERCURIUS`    

A hybrid integrator very similar to the one found in MERCURY. It uses WHFast for long term integrations but switches over smoothly to IAS15 for close encounters.  


## NONE
`REB_INTEGRATOR_NONE`    

Sometimes it might make sense to simply not advance any particle positions or velocities. By selecting this integrator, one can still perform integration steps, but particles will not move.
