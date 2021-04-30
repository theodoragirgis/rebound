# Orbital elements

This section discusses orbital parameters.
We focus on the implementation and conventions in REBOUND.


The following image illustrated the most important angles used.
In REBOUND the reference direction is the positive x direction, the reference plane
is the xy plane.

![Orbital elements](img/orbit.png "Image from wikipedia. CC-BY-SA-3.")

## Orbit structure 

Variable name   | Description
--------------- | ------------
`d`             | radial distance from reference 
`v`             | velocity relative to central object's velocity
`h`             | specific angular momentum
`P`             | orbital period (negative if hyperbolic)
`n`             | mean motion    (negative if hyperbolic)
`a`             | semimajor axis
`e`             | eccentricity
`inc`           | inclination
`Omega`         | longitude of ascending node
`omega`         | argument of pericenter
`pomega`        | longitude of pericenter
`f`             | true anomaly
`M`             | mean anomaly
`E`             | Eccentric anomaly. Because this requires solving Kepler's equation it is only calculated when needed in python and never calculated in C. To get the eccentric anomaly in C, use the function `double reb_tools_M_to_E(double e, double M)`
`l`             | mean longitude = Omega + omega + M
`theta`         | true longitude = Omega + omega + f
`T`             | time of pericenter passage
`rhill`         | Hill radius, $r_{\rm hill} =a\sqrt[3]{\frac{m}{3M}}$

!!! Important
    All angles in REBOUND are in radians. 
    Variables which have length, time or velocity units use code units.
