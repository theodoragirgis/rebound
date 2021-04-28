# Integrators

## IAS15
`REB_INTEGRATOR_IAS15`

IAS15 stands for Integrator with Adaptive Step-size control, 15th order. It is a very high order, non-symplectic integrator which can handle arbitrary (velocity dependent) forces and is in most cases accurate down to machine precision. IAS15 can integrate variational equations. Rein & Spiegel 2015, Everhart 1985. This is the default integrator of REBOUND.

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
