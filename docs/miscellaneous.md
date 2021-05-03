# Miscellaneous tools

## Modulo two pi 
The following function takes the modulo of angle (in radians).
The result is in the range $[0, 2\pi]$.

=== "C"
    ```c
    double f = reb_tools_mod2pi(7.); // returns 0.7168 = 7 - 2*pi
    ```

=== "Python"
    ```python
    f = rebound.mod2pi(7.) // returns 0.7168 = 7 - 2*pi
    ```
